#pragma warning(disable:4996)

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>
#include <fstream>
#include <sstream>
#include <document.h>
#include "Skeleton.h"
#include "Animation.h"
#include "SkeletalMeshComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "MainCameraObject.h"
#include "HDRRenderer.h"

Renderer* Renderer::renderer = nullptr;

void Renderer::SetParticleVertex()
{
	particleVertex->SetActive();
}

Renderer::Renderer()
	: hdrRenderer(nullptr)
	, spriteShader(nullptr)
	, spriteVerts(nullptr)
	, particleShader(nullptr)
	, particleVertex(nullptr)
	, depthMapShader(nullptr)
	, switchShader(nullptr)
	, shadowMapShader(nullptr)
	, mSkinnedDepthMapShader(nullptr)
	, mSkinnedShadowMapShader(nullptr)
	, view(Matrix4::Identity)
	, projection(Matrix4::Identity)
	, screenWidth(0)
	, screenHeight(0)
	, ambientLight(Vector3::Zero)
	, SHADOW_WIDTH (8192)
	, SHADOW_HEIGHT(8192)
{
}

Renderer::~Renderer()
{
}

/*
@brief  �C���X�^���X���쐬����
*/
void Renderer::CreateInstance()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer();
	}
}

/*
@brief  �C���X�^���X���폜����
*/
void Renderer::DeleteInstance()
{
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
}

/*
@brief  ����������
@return true : ���� , false : ���s
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight, bool _fullScreen)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;

	// OpenGL�̊e������ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGL�̎g�p�o�[�W������3.3�Ɏw��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// �n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//�E�B���h�E�̍쐬

	window = SDL_CreateWindow("OpenGL Game", 1, 1,
		static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);

	if (_fullScreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL);
	}

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdlRenderer)
	{
		printf("SDLRenderer�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}

	// OpenGL�̃R���e�L�X�g���쐬
	context = SDL_GL_CreateContext(window);

	// GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
	glGetError();

	// �V�F�[�_�[�̃��[�h
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}


	//�X�v���C�g�p�̒��_�z����쐬
	CreateSpriteVerts();

	CreateParticleVerts();

	// SDL_ttf�̏�����
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}


	undefineTexID = GetTexture("Assets/noneTexture.png")->GetTextureID();

	//�@HDRrenderer�̐���
	hdrRenderer = new HDRRenderer(screenWidth, screenHeight,4);

	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	CreateTimeFontTexture(151,72);

	return true;
}

/*
@brief  �I������
*/
void Renderer::Shutdown()
{
	//shader��vertex�̌�Еt��
	delete particleVertex;
	particleShader->Unload();
	delete particleShader;

	delete spriteVerts;

	spriteShader->Unload();
	delete spriteShader;

	switchShader->Unload();
	delete switchShader;

	depthMapShader->Unload();
	delete depthMapShader;

	shadowMapShader->Unload();
	delete shadowMapShader;

	mSkinnedDepthMapShader->Unload();
	delete mSkinnedDepthMapShader;

	mSkinnedShadowMapShader->Unload();
	delete mSkinnedShadowMapShader;

	//�R���e�L�X�g��window�̌�Еt��
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
@brief  ���[�h�����f�[�^�̉��
*/
void Renderer::UnloadData()
{
	// ���ׂẴe�N�X�`���̃f�[�^�����
	for (auto i : textures)
	{
		i.second->Unload();
		delete i.second;
	}
	textures.clear();

	// ���ׂẴ��b�V���̃f�[�^�����
	for (auto i : meshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// Unload skeletons
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	// Unload animations
	for (auto a : mAnims)
	{
		delete a.second;
	}

	meshes.clear();
	mSkeletons.clear();
	mAnims.clear();
}

/*
@brief  �`�揈��
*/
void Renderer::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �f�v�X�}�b�v�����_�����O
	DepthRendering();

	//�V���h�E�}�b�v�`��
	DrawShadow();

	// particle�`��
	DrawParticle();

	// UI�n�X�v���C�g�R���|�[�l���g�̕`��
	// �A���t�@�u�����f�B���O��L���ɂ���
	glEnable(GL_BLEND);
	// �f�v�X�o�b�t�@�@�𖳌��ɂ���
	glDisable(GL_DEPTH_TEST);


	// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	spriteShader->SetActive();
	spriteVerts->SetActive();
	// ���ׂẴX�v���C�g�̕`��
	for (auto sprite : sprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	// �o�b�t�@������
	SDL_GL_SwapWindow(window);
}


/*
@brief  �X�v���C�g�̒ǉ�
@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
*/
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// ������X�v���C�g����}������ꏊ�̌���
	// (DrawOrder�����������Ԃɕ`�悷�邽��)

	bool isBackGround = _spriteComponent->GetIsBackGround();
	int myDrawOrder = _spriteComponent->GetDrawOrder();
	if (isBackGround == false)
	{
		auto iter = sprites.begin();
		for (;
			iter != sprites.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// ���������ꏊ��iter�̏ꏊ�ɑ}��
		sprites.insert(iter, _spriteComponent);
	}

	if (isBackGround == true)
	{
		auto iter = backGroundSprites.begin();
		for (;
			iter != backGroundSprites.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// ���������ꏊ��iter�̏ꏊ�ɑ}��
		backGroundSprites.insert(iter, _spriteComponent);
	}
}

/*
@brief �X�v���C�g�̍폜
@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	bool isBackGround = _spriteComponent->GetIsBackGround();
	if (isBackGround == false)
	{
		auto iter = std::find(sprites.begin(), sprites.end(), _spriteComponent);
		sprites.erase(iter);
	}

	if (isBackGround == true)
	{
		auto iter = std::find(backGroundSprites.begin(), backGroundSprites.end(), _spriteComponent);
		backGroundSprites.erase(iter);
	}

}


/*
@brief  �p�[�e�B�N���̒ǉ�
@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
*/
void Renderer::AddParticle(ParticleComponent * _particleComponent)
{
	int myDrawOrder = _particleComponent->GetDrawOrder();
	auto iter = particles.begin();
	for (;
		iter != particles.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	particles.insert(iter, _particleComponent);
}

/*
@brief  �X�v���C�g�̍폜
@param	�폜����ParticleObject�N���X�̃|�C���^
*/
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	auto iter = std::find(particles.begin(), particles.end(), _particleComponent);
	particles.erase(iter);
}

/*
@brief  ���b�V���R���|�[�l���g�̒ǉ�
@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
*/
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	//���b�V���f�[�^�ɃX�P���g���f�[�^�������
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		mSkeletalMeshes.emplace_back(sk);
	}
	else if(_meshComponent->GetIsColorChange() == true)
	{
		colorChangeMeshComponents.emplace_back(_meshComponent);
	}
	else
	{
		meshComponents.emplace_back(_meshComponent);
	}
}


/*
@brief  ���b�V���R���|�[�l���g�̍폜
@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
*/
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else if (_meshComponent->GetIsColorChange())
	{
		auto iter = std::find(colorChangeMeshComponents.begin(), colorChangeMeshComponents.end(), _meshComponent);
		colorChangeMeshComponents.erase(iter);
	}
	else
	{
		auto iter = std::find(meshComponents.begin(), meshComponents.end(), _meshComponent);
		meshComponents.erase(iter);
	}
}


/*
@param _fileName ���f���ւ̃A�h���X
@return �X�P���g�����f���̎擾
*/
const Skeleton * Renderer::GetSkeleton(const char * fileName)
{
	std::string file(fileName);
	auto iter = mSkeletons.find(file);
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(file))
		{
			mSkeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

/*
@param _fileName �A�j���[�V�����ւ̃A�h���X
@return �X�P���g���A�j���[�V�����̎擾
*/
const Animation * Renderer::GetAnimation(const char * fileName, bool _loop)
{
	auto iter = mAnims.find(fileName);
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->Load(fileName,_loop))
		{
			mAnims.emplace(fileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/*
@brief  �e�N�X�`���̎擾
@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
@return Texture�N���X�̃|�C���^
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = textures.find(_fileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			textures.emplace(_fileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

Font* Renderer::GetFont(const std::string& _fileName)
{
	Font* font = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = fonts.find(_fileName);
	if (itr != fonts.end())
	{
		font = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		font = new Font();
		if (font->Load(_fileName))
		{
			fonts.emplace(_fileName, font);
		}
		else
		{
			delete font;
			font = nullptr;
		}
	}

	return font;
}

/*
@brief  ���b�V���̎擾
@param	_fileName �擾���������b�V���̃t�@�C����
@return Mesh�N���X�̃|�C���^
*/
Mesh* Renderer::GetMesh(const std::string &_fileName)
{
	Mesh* m = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto iter = meshes.find(_fileName);
	if (iter != meshes.end())
	{
		m = iter->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, this))
		{
			meshes.emplace(_fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/*
@brief  �V�F�[�_�[�̓ǂݍ���
@return true : ���� , false : ���s
*/
bool Renderer::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[�̍쐬
	spriteShader = new Shader();
	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	spriteShader->SetActive();
	// sprite�p�r���[�s��̐ݒ�
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);


	// 3D���f���p�r���[�s��̐ݒ�
	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		screenWidth, screenHeight, 25.0f, 7000.0f);

	// switch�p�V�F�[�_�[�̍쐬(�F�ύX�\�V�F�[�_�[)
	switchShader = new Shader();
	if (!switchShader->Load("Shaders/shadowmap.vert", "Shaders/switch.frag"))
	{
		return false;
	}
	switchShader->SetActive();
	switchShader->SetMatrixUniform("uViewProj", view * projection);


	//particle�V�F�[�_�[
	particleShader = new Shader();
	if (!particleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �V���h�E�p�t���[���o�b�t�@�I�u�W�F�N�g���쐬�E�f�v�X�}�b�v�𐶐����A�V���h�E�o�b�t�@�ɃA�^�b�`
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// depthMapFBO�Ƀf�v�X�e�N�X�`�����A�^�b�`����
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// �f�v�X�}�b�v�Ă��p�V�F�[�_(�A�j���[�V�����Ȃ�)
	depthMapShader = new Shader();
	if (!depthMapShader->Load("Shaders/depthmap.vert", "Shaders/depthmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}
	// �V���h�E��K�p�����`��p�V�F�[�_�쐬(�A�j���[�V�����Ȃ�)
	shadowMapShader = new Shader();
	if (!shadowMapShader->Load("Shaders/shadowmap.vert", "Shaders/shadowmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �f�v�X�}�b�v�Ă��p�V�F�[�_ (�A�j���[�V��������)
	mSkinnedDepthMapShader = new Shader();
	if (!mSkinnedDepthMapShader->Load("Shaders/SkinnedDepth.vert", "Shaders/depthmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��sdepth\n");
	}
	// �V���h�E��K�p�����`��p�V�F�[�_�쐬 (�A�j���[�V��������)
	mSkinnedShadowMapShader = new Shader();
	if (!mSkinnedShadowMapShader->Load("Shaders/SkinnedShadow.vert", "Shaders/SkinnedShadow.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��sshadow\n");
	}

	return true;
}

/*
@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // ����
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // �E��
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // �E��
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // ����
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices, 4, indices, 6);
}

// �p�[�e�B�N�����_�쐬
void Renderer::CreateParticleVerts()
{
	float vertices[] = {
		-0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		 0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		 0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 2, 1,
		2, 0, 3
	};
	particleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::CreateTimeFontTexture(int _value, int _fontSize)
{
	Font* font = GetFont("Assets/Config/Fonts/impact.ttf");
	timeFontTextures.resize(_value);
	timeBlackFontTextures.resize(_value);
	timeRedFontTextures.resize(_value);

	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeFontTextures[i] = font->RenderText(str,Color::White, _fontSize);
	}
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeBlackFontTextures[i] = font->RenderText(str, Color::Black, _fontSize);
	}
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeRedFontTextures[i] = font->RenderText(str, Color::Red, _fontSize);
	}


}

Texture* Renderer::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

Texture* Renderer::GetTimeBlackTexture(int _time)
{
	return timeBlackFontTextures[_time + 1];
}

Texture* Renderer::GetTimeRedTexture(int _time)
{
	return timeRedFontTextures[_time + 1];
}

void Renderer::DrawShadow()
{


	/* HDR�ƃV���h�E�}�b�v�̏����J�n */
	hdrRenderer->HdrRecordBegin();

	// �w�i�`��
	DrawBackGround();

	//�V���h�E�}�b�vshader���A�N�e�B�u
	shadowMapShader->SetActive();
	// ���C�g�̃J�������
	shadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	shadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	shadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	shadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	shadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	shadowMapShader->SetMatrixUniform("view", view);
	shadowMapShader->SetMatrixUniform("projection", projection);

	// �f�v�X�}�b�v���Z�b�g�i���b�V���p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	shadowMapShader->SetIntUniform("depthMap", 4);

	shadowMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
	// ���ׂẴ��b�V���̕`��
	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(shadowMapShader);
		}
	}

	//�V���h�E�}�b�vshader���A�N�e�B�u(skinnend)
	mSkinnedShadowMapShader->SetActive();
	// ���C�g�̃J�������
	mSkinnedShadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	mSkinnedShadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	mSkinnedShadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	mSkinnedShadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	mSkinnedShadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	mSkinnedShadowMapShader->SetMatrixUniform("uViewProj", view * projection);
	// �f�v�X�}�b�v���Z�b�g�i�X�L�j���O�p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	mSkinnedShadowMapShader->SetIntUniform("depthMap", 4);
	mSkinnedShadowMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedShadowMapShader);
		}
	}
	/*  �V���h�E�}�b�v�`��I�� */

	switchShader->SetActive();
	switchShader->SetMatrixUniform("uViewProj", view* projection);
	// ���C�g�̃J�������
	switchShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	switchShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	switchShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	switchShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	switchShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	switchShader->SetMatrixUniform("view", view);
	switchShader->SetMatrixUniform("projection", projection);

	for (auto mc : colorChangeMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(switchShader);
		}
	}


	hdrRenderer->HdrRecordEnd();

	/* HDR Bloom �̍쐬�ƍ��� */
	// �K�E�X�ڂ����̐���
	hdrRenderer->HiBrightBlurCreate();
	// �K�E�X�ڂ��������摜��HDR���ŏI����
	hdrRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBuffer�Ƀ����_�����O�����Ƃ���Depth�����X�N���[���ɃR�s�[
	hdrRenderer->CopyDepthToScreen();

}

void Renderer::DepthRendering()
{
	/* ��������f�v�X�}�b�v�J�n */


	//���C�g���
	LightPos = Vector3(playerPos.x, playerPos.y, playerPos.z + 1000.0f);
	LightDir = dirLight.direction;
	LightDir.Normalize();
	lightProjection = Matrix4::CreateOrtho(3000.0f, 3000.0f, 1.0f, 5000.0f);
	lightView = Matrix4::CreateLookAt(LightPos, playerPos, Vector3::UnitX);
	lightSpeceMatrix = lightView * lightProjection;

	// �r���[�|�[�g��[�x�}�b�v�T�C�Y�ɐݒ肷��
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	// �V���h�E�t���[���o�b�t�@���o�C���h
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	glClear(GL_DEPTH_BUFFER_BIT);

	// �f�v�X�}�b�v�Ă��p�V�F�[�_��L�������A�K�v�Ȓl���V�F�[�_�ɃZ�b�g�E�V���h�E���������I�u�W�F�N�g��`�悷��
	depthMapShader->SetActive();
	depthMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(depthMapShader);
		}
	}

	mSkinnedDepthMapShader->SetActive();
	mSkinnedDepthMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);
	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedDepthMapShader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/* �����Ńf�v�X�}�b�v�I�� */

}

void Renderer::DrawBackGround()
{
	// �A���t�@�u�����f�B���O��L���ɂ���
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �X�v���C�g�R���|�[�l���g�̕`��(�w�i)
	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	spriteShader->SetActive();
	spriteVerts->SetActive();
	glActiveTexture(GL_TEXTURE0);
	spriteShader->SetIntUniform("uTexture", 0);
	// ���ׂẴX�v���C�g�̕`��
	for (auto sprite : backGroundSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}

void Renderer::DrawParticle()
{
	
	std::sort(particles.begin(), particles.end(), std::greater<ParticleComponent*>());

	if (particles.size() == 0)
	{
		return;
	}
	// �u�����h���[�h������Ԏ擾
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = particles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// �e�N�X�`��ID������Ԏ擾
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// �r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMat;
	viewProjectionMat = view * projection;

	// �V�F�[�_�[ON
	particleShader->SetActive();
	particleShader->SetMatrixUniform("uViewProj", viewProjectionMat);
	// �S�Ẵp�[�e�B�N���̃r���{�[�h�s����Z�b�g
	(*itr)->SetBillboardMat(GetBillboardMatrix());


	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// ���ׂẴp�[�e�B�N����`��
	glActiveTexture(GL_TEXTURE0);
	particleShader->SetIntUniform("uTexture", 0);
	ChangeBlendMode(blendType);
	
	ChangeTexture(nowTexture);

	for (auto particle : particles)
	{
		if (particle->GetVisible())
		{
			//�u�����h���[�h�ύX���K�v�Ȃ�ύX����
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();
			if (blendType != prevType)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeBlendMode(blendType);
			}
			// �e�N�X�`���ύX���K�v�Ȃ�ύX����
			nowTexture = particle->GetTextureID();
			if (nowTexture != prevTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeTexture(nowTexture);
			}

			// �p�[�e�B�N���`��
			particle->Draw(particleShader);

			// �O��`���ԂƂ��ĕۑ�
			prevType = blendType;
			prevTexture = nowTexture;
		}
	}

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4 & view, const Matrix4 & proj, float viewPortScale, bool lit)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(screenWidth * viewPortScale),
		static_cast<int>(screenHeight * viewPortScale)
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw mesh components
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// Set the mesh shader active
	//meshShader->SetActive();
	//// Update view-projection matrix
	//meshShader->SetMatrixUniform("uViewProj", view * proj);
	//// Update lighting uniforms
	//if (lit)
	//{
	//	SetLightUniforms(meshShader, view);
	//}
	//for (auto mc : meshComponents)
	//{
	//	if (mc->GetVisible())
	//	{
	//		mc->Draw(meshShader);
	//	}
	//}

}

/*
@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
@param _shader �Z�b�g����Shader�N���X�̃|�C���^
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// �r���[�s����t�s��ɂ���
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// �����̐ݒ�
	_shader->SetVectorUniform("uAmbientLight", ambientLight);
	// ���s�����̐ݒ�
	_shader->SetVectorUniform("uDirLight.mDirection",
		dirLight.direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		dirLight.diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		dirLight.specColor);
}

void Renderer::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType)
{
	switch (blendType)
	{
	case ParticleComponent::PARTICLE_BLEND_ENUM_ADD:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //���Z����
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //��Z����
		break;
	default:
		break;
	}
}

void Renderer::ChangeTexture(int changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

Vector3 Renderer::CalcCameraPos()
{
	// �r���[�s���胏�[���h�ł̃J�����ʒu�Z�o
	Matrix4 transMat = view;

	// �r���[�s��̈ړ������������
	Vector3 v;
	v.x = -1.0f * view.mat[3][0];
	v.y = -1.0f * view.mat[3][1];
	v.z = -1.0f * view.mat[3][2];

	//�ړ���������菜�������Ɠ]�u���āA��]�����̋t�ϊ������
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}


// ��ʑS�̂𕢂����_��`
void Renderer::screenVAOSetting(unsigned int& vao)
{
	unsigned int vbo;
	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}