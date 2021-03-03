#pragma once
#include "GameObject.h"
#include "ParticleComponent.h"
#include <string>

enum ParticleState
{
	PARTICLE_ACTIVE,
	PARTICLE_DISABLE,
};


/*
@file ParticleEffectBase.h
@brief ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
*/
class ParticleEffectBase :
	public GameObject
{
public:
	/*
	@param _pos �I�u�W�F�N�g�̐����ꏊ
	@param _velocity �I�u�W�F�N�g�̈ړ���
	@param _lifeCount �I�u�W�F�N�g�̐�������
	@param _spriteFileName �摜�ւ̃A�h���X
	@param _scale �摜�̊g��T�C�Y
	*/
	ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, const float& _scale = 10);
	~ParticleEffectBase();

	/*
	@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	/*
	@fn �h���N���X���ƂɌ��肷��X�V�֐�
	*/
	virtual void UpdateParticleObject(float _deltaTime);
protected:
	/*
	@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
	*/
	void LifeCountDown();
	//�摜�̕`��N���X
	ParticleComponent* particleComponent;
	//��������
	int lifeCount;

	ParticleState particleState;
public:
	void SetReverve(float _flag);
};
