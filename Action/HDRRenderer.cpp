#include "HDRRenderer.h"
#include "Renderer.h"
#include "Shader.h"

HDRRenderer::HDRRenderer(int fboWidth, int fboHeight, int bloomLevel)
	: gaussianBlurShader(nullptr)
	, downSamplingShader(nullptr)
	, hdrToneAndBlurBlendShader(nullptr)
	, quadScreenVAO(0)
	, quadScreenVBO(0)
	, hdrFBO(0)
	, hdrRBO(0)
	, bufferWidth(fboWidth)
	, bufferHeight(fboHeight)
	, bloomBufferLevel(bloomLevel)
{
	// HDR �o�b�t�@��Blur�p�o�b�t�@���쐬
	InitHDRBuffers();
	InitBlurBuffers();
	// �X�N���[���o�b�t�@�`��p���_�쐬
	InitScreenQuadVAO();

	// �K�E�V���O�V�F�[�_�[����
	gaussianBlurShader = new Shader;
	if (!gaussianBlurShader->Load("shaders/framebufferScreen.vert", "shaders/gaussianblur.frag"))
	{
		printf("GaussianBlurShader Load Failed.\n");
	}
	// �_�E���T���v�����O�V�F�[�_�[����
	downSamplingShader = new Shader;
	if (!downSamplingShader->Load("shaders/framebufferScreen.vert", "shaders/downsampling.frag"))
	{
		printf("DownSamplingShader Load Failed.\n");
	}
	// �g�[��shader����
	hdrToneAndBlurBlendShader = new Shader;
	if (!hdrToneAndBlurBlendShader->Load("shaders/framebufferScreen.vert", "shaders/hdrBlurBlend.frag"))
	{
		printf("HdrToneAndBlurBlendShader Load Failed\n");
	}
}

HDRRenderer::~HDRRenderer()
{
	// �㏈��
	delete gaussianBlurShader;
	delete downSamplingShader;
	delete hdrToneAndBlurBlendShader;
	for (auto item : blurFBOs)
	{
		glDeleteFramebuffers(1, &item);
	}
	for (auto item : blurBufferTexs)
	{
		glDeleteTextures(1, &item);
	}
	glDeleteBuffers(1, &quadScreenVBO);
	glDeleteVertexArrays(1, &this->quadScreenVAO);

}

void HDRRenderer::HdrRecordBegin()
{
	// �`��Ώۂ�mHdrFBO�ɕύX( HDRcolor + HDRHighBright�̂Q���֏o��)
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	glEnable(GL_DEPTH_TEST);

	// �J���[�o�b�t�@�̃N���A
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void HDRRenderer::HdrRecordEnd()
{
	// �`��Ώۂ��X�N���[���֖߂�
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRRenderer::HiBrightBlurCreate()
{
	glDisable(GL_DEPTH_TEST);
	unsigned int renderSource = hdrColorBuffers[1];

	// �k���o�b�t�@1,3,5,7,9�ɃR�s�[
	int reducex = bufferWidth;
	int reducey = bufferHeight;

	// �_�E���T���v�����O 1, 3, 5 ...�Ɗ�ԂɃ_�E���T���v�����O���ʏo��
	for (unsigned int i = 0; i < bloomBufferLevel; i++)
	{
		reducex /= 2;
		reducey /= 2;
		glBindFramebuffer(GL_FRAMEBUFFER, blurFBOs[i * 2 + 1]);
		{
			glViewport(0, 0, reducex, reducey);
			//�J���[�o�b�t�@�̃N���A
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, renderSource);
			downSamplingShader->SetActive();
			downSamplingShader->SetIntUniform("screenTexture", 0);

			glBindVertexArray(quadScreenVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		renderSource = blurBufferTexs[i * 2 + 1];
	}

	// �K�E�X�ڂ���
	reducex = bufferWidth;
	reducey = bufferHeight;
	float deviation = 5.0f;
	renderSource = blurBufferTexs[1];

	// �K�E�X���x������
	for (unsigned int i = 0; i < bloomBufferLevel; i++)
	{
		reducex /= 2;
		reducey /= 2;
		bool h = false;
		// horizontal 0 : ���� 1: �������� �ɃK�E�X�ڂ���������
		for (int horizontal = 0; horizontal < 2; horizontal++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, blurFBOs[i * 2 + horizontal]);
			{
				glViewport(0, 0, reducex, reducey);
				Vector2 dir;
				if (horizontal)
				{
					dir = Vector2(0, 1);
				}
				else
				{
					dir = Vector2(1, 0);
				}
				CalcGaussBlurParam(reducex, reducey, dir, deviation);

				// �J���[�o�b�t�@�̃N���A
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, renderSource);
				gaussianBlurShader->SetActive();
				gaussianBlurShader->SetIntUniform("blursource", 0);
				gaussianBlurShader->SetIntUniform("param.SampleCount", sampleCount);

				for (int i = 0; i < sampleCount; i++)
				{
					std::string s = "param.Offset[" + std::to_string(i) + "]";
					gaussianBlurShader->SetVectorUniform(s.c_str(), offset[i]);
				}

				glBindVertexArray(quadScreenVAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				renderSource = blurBufferTexs[i * 2 + horizontal];
			}
		}
		// �񐔂��Ƃɕ΍����グ��
		deviation *= 2.0f;
	}
	glEnable(GL_DEPTH_TEST);

}

void HDRRenderer::HdrTonemapAndBrightBlurCombine()
{
	// ���摜�ƃK�E�X�ڂ����摜�����ׂč�������
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_FRONT);
	{
		glViewport(0, 0, bufferWidth, bufferHeight);

		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, hdrColorBuffers[0]);

		for (unsigned int i = 0; i < bloomBufferLevel; i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);
			glBindTexture(GL_TEXTURE_2D, blurBufferTexs[i * 2 + 1]);
		}

		hdrToneAndBlurBlendShader->SetActive();
		hdrToneAndBlurBlendShader->SetIntUniform("scene", 0);
		hdrToneAndBlurBlendShader->SetIntUniform("bloom1", 1);
		hdrToneAndBlurBlendShader->SetIntUniform("bloom2", 2);
		hdrToneAndBlurBlendShader->SetIntUniform("bloom3", 3);
		hdrToneAndBlurBlendShader->SetIntUniform("bloom4", 4);
		hdrToneAndBlurBlendShader->SetIntUniform("bloom5", 5);

		const float exposure = 0.8f;

		hdrToneAndBlurBlendShader->SetFloatUniform("exposure", exposure);

		glBindVertexArray(quadScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	// Active�e�N�X�`����set�������e�����F�e�N�X�`���Ŗ����ɂ���
	unsigned int texNone = RENDERER->GetUndefineTexID();
	for (unsigned int i = 0; i < bloomBufferLevel; i++)
	{
		glActiveTexture(GL_TEXTURE1 + i);
		glBindTexture(GL_TEXTURE_2D, texNone);
	}

}

void HDRRenderer::CopyDepthToScreen()
{
	// gBuffer�̐[�x���f�t�H���g�̐[�x�o�b�t�@�ɃR�s�[����
	glBindFramebuffer(GL_READ_FRAMEBUFFER, hdrFBO);  // �ǂݍ��݃o�b�t�@��gBuffer�Ɏw��
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);        // �������݃o�b�t�@���X�N���[���Ɏw��
	// �[�x�����X�N���[���̐[�x�o�b�t�@�ɃR�s�[
	glBlitFramebuffer(
		0, 0, bufferWidth, bufferHeight, 0, 0, bufferWidth, bufferHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST
	);
	// �ʏ�̃X�N���[���ւ̕`��ɖ߂�
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);

}

void HDRRenderer::InitHDRBuffers()
{
	/////////////////////////////////////////////////
	// ���������_�t���[���o�b�t�@�i�J���[�o�b�t�@�Q�j�̍쐬
	/////////////////////////////////////////////////
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	{
		glGenTextures(2, hdrColorBuffers);
		for (unsigned int i = 0; i < 2; i++)
		{
			glBindTexture(GL_TEXTURE_2D, hdrColorBuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, bufferWidth, bufferHeight, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// attach texture to framebuffer
			glFramebufferTexture2D(				GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, hdrColorBuffers[i], 0);
		}
		// �����_�[�o�b�t�@�[�̍쐬
		glGenRenderbuffers(1, &hdrRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, hdrRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bufferWidth, bufferHeight);
		// FBO�Ƀ����_�[�o�b�t�@�[���A�^�b�`����
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, hdrRBO);

		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("HDRRenderer ERROR::FRAMEBUFFER:: Framebuffer is not complete! \n");
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // �f�t�H���g�ɖ߂�

}

void HDRRenderer::InitBlurBuffers()
{
	int w = bufferWidth;
	int h = bufferHeight;

	float borderColor[4] = { 0.0f };
	blurFBOs.resize(bloomBufferLevel * 2);
	blurBufferTexs.resize(bloomBufferLevel * 2);

	// �������E�c�����u���[�쐬�@mBloomBufferLevel�̂Q�{���̖����쐬
	for (unsigned int i = 0; i < bloomBufferLevel; i++)
	{
		// �k���o�b�t�@���E����
		w /= 2;
		h /= 2;
		// j : 0 ������ 1 : �c����
		for (int j = 0; j < 2; j++)
		{
			glGenFramebuffers(1, &blurFBOs[i * 2 + j]);
			glGenTextures(1, &blurBufferTexs[i * 2 + j]);
			{
				glBindFramebuffer(GL_FRAMEBUFFER, blurFBOs[i * 2 + j]);
				glBindTexture(GL_TEXTURE_2D, blurBufferTexs[i * 2 + j]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glFramebufferTexture2D(
					GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurBufferTexs[i * 2 + j], 0
				);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}

void HDRRenderer::InitScreenQuadVAO()
{
	// ��ʑS�̏����p��VAO�쐬
	// �X�N���[���S�̂�`���l�p�`�p���_�z��
	float quadVertices[] = {
		// �|�W�V����   // �e�N�X�`�����W
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// �X�N���[���S�̂�`���l�p�`�p VAO
	glGenVertexArrays(1, &quadScreenVAO);
	glGenBuffers(1, &quadScreenVBO);
	glBindVertexArray(quadScreenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadScreenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

float HDRRenderer::GaussianDistribution(const Vector2& pos, float rho)
{
	return exp(-(pos.x * pos.x + pos.y * pos.y) / (2.0f * rho * rho));
}

void HDRRenderer::CalcGaussBlurParam(int w, int h, Vector2 dir, float deviation)
{
	auto tu = 1.0f / float(w);
	auto tv = 1.0f / float(h);

	offset[0].z = GaussianDistribution(Vector2(0.0f, 0.0f), deviation);
	auto total_weight = offset[0].z;

	offset[0].x = 0.0f;
	offset[0].y = 0.0f;

	for (auto i = 1; i < 8; ++i)
	{
		int nextpos = (i - 1) * 2 + 1;
		offset[i].x = dir.x * tu * nextpos;
		offset[i].y = dir.y * tv * nextpos;
		offset[i].z = GaussianDistribution(dir * float(nextpos), deviation);
		total_weight += offset[i].z * 2.0f;
	}
	for (auto i = 0; i < 8; ++i)
	{
		offset[i].z /= total_weight;
	}
	for (auto i = 8; i < 15; ++i)
	{
		offset[i].x = -offset[i - 7].x;
		offset[i].y = -offset[i - 7].y;
		offset[i].z = offset[i - 7].z;
	}
}
