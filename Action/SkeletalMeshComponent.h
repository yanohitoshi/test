#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

/*
@file SkeletalMeshComponent.h
@brief �X�P���g���f�[�^�̕`��ƃA�j���[�V����
*/
class SkeletalMeshComponent : public MeshComponent
{
public:

	SkeletalMeshComponent(class GameObject* owner);

	void Update(float deltaTime) override;

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* shader) override;

   	/*
	@fn �A�j���[�V�����̍Đ�
	@param _anim �A�j���[�V�����f�[�^�N���X
	@param _playRate �A�j���[�V�����̍Đ����x
	@return �A�j���[�V�����̎c�莞��
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);
protected:
	/*
	@fn �s��p���b�g�̌v�Z
	*/
	void ComputeMatrixPalette();                                       
	// �s��p���b�g
	MatrixPalette palette;                                    
	// �X�P���g���f�[�^
	const class Skeleton* skeleton;                                       
	// �A�j���[�V�����f�[�^
	const class Animation* animation;                                     
	// �A�j���[�V�����̍Đ����x
	float animPlayRate;                                                  
	// �A�j���[�V��������
	float animTime;                                                       
	//�X�P���g���f�[�^�ɏ�Z����F
	Vector3 color;
	//texture�Z�b�g�p�֐�
	void SetTextureToShader(Shader* shader);

public://�Q�b�^�[�Z�b�^�[
	/*
	@param _skeleton �X�P���g���f�[�^
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { skeleton = _skeleton; }
	/*
	@param _color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { color = _color; }

	//�Đ������ǂ���
	bool IsPlaying();


};
