#pragma once
#include <vector>
#include <unordered_map>
#include "Math.h"

class HDRRenderer
{
public:
	HDRRenderer(int fboWidth,int fboHeight,int bloomLevel);
	~HDRRenderer();

	void HdrRecordBegin();
	void HdrRecordEnd();
	void HiBrightBlurCreate();
	void HdrTonemapAndBrightBlurCombine();
	void CopyDepthToScreen();

	unsigned int GetColorTexID() { return hdrColorBuffers[0]; }
	unsigned int GetHDRTexID() { return hdrColorBuffers[1]; }

private:

	void  InitHDRBuffers();
	void  InitBlurBuffers();
	void  InitScreenQuadVAO();
	float GaussianDistribution(const Vector2& pos, float rho);
	void  CalcGaussBlurParam(int w, int h, Vector2 dir, float deviation);

	class Shader* gaussianBlurShader;
	class Shader* downSamplingShader;
	class Shader* hdrToneAndBlurBlendShader;
	unsigned int quadScreenVAO;
	unsigned int quadScreenVBO;

	unsigned int bufferWidth;
	unsigned int bufferHeight;
	unsigned int bloomBufferLevel;
	unsigned int bloomBufferNum;

	unsigned int hdrFBO;              // ���������_FBO
	unsigned int hdrRBO;
	unsigned int hdrColorBuffers[2];

	std::vector<unsigned int> blurFBOs;            // �u���[�p�̃t���[���o�b�t�@�I�u�W�F�N�g
	std::vector<unsigned int> blurBufferTexs;      // �u���[���ʂ̃e�N�X�`��ID

	const int sampleCount = 15;    // �K�E�X�ڂ����̃T���v�����O�_
	Vector3 offset[15];          // �T���v�����O�_�̍��W(u,v) & w:�d��

};

