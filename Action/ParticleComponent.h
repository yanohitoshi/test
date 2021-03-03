#pragma once
#include "Component.h"
#include "Math.h"

/*
 @file ParticleComponent.h
 @brief �摜���Ǘ��������3D��ԏ�ɕ`�悷��N���X�B
*/
class ParticleComponent :
	public Component
{
public:
	//�p�[�e�B�N���ɑ΂���u�����h�̎��
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;

	/*
	 @param _offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
	 @param _scale �摜�̕`��T�C�Y
	*/
	ParticleComponent(GameObject* _owner, const Vector3& _offset = Vector3(1, 1, 1), float _scale = 1.0f, int _updateOrder = 100);
	~ParticleComponent();

	virtual void Update(float _deltaTime) override {};

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* _shader);

	// �J���������ł̃\�[�g�p
	bool operator < (const ParticleComponent& rhs) const;
	bool operator > (const ParticleComponent& rhs) const;
private:
	//�e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
	Vector3 offset;
	//�摜�ɏ�Z����F
	Vector3 color;
	//�T�C�Y
	float scale;
	//�����x
	float alpha; 
	//�e�N�X�`��ID
	int textureID; 
	//�u�����h�^�C�v
	PARTICLE_ENUM blendType;
	//�`����s����
	bool visible;
	// �r���{�[�h�s��
	static Matrix4 staticBillboardMat; 
	// �J�����̃��[���h���W
	static Vector3 staticCameraWorldPos;
	//�`�揇(���������Ȃ����̂���`�悳���)
	int drawOrder;
	//���]���s����
	bool reverce;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@return �e�N�X�`��ID
	*/
	int GetTextureID() { return textureID; }
	/*
	@param _texId �e�N�X�`��ID
	*/
	void SetTextureID(int _texId) { textureID = _texId; }
	/*
	@return �u�����h�^�C�v
	*/
	PARTICLE_ENUM GetBlendType() { return blendType; }
	/*
	@param _color �摜�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { color = _color; }
	/*
	@param _alfa �����x0~1
	*/
	void SetAlpha(float _alpha) { alpha = _alpha; }
	/*
	@param �T�C�Y
	*/
	void SetScale(float _scale) { scale = _scale; }
	/*
	@param _mat �r���{�[�h�s��
	*/
	void SetBillboardMat(const Matrix4& _mat) {	staticBillboardMat = _mat;	}
	/*
	@param _brendType �J�����̃��[���h���W
	*/
	void SetBlendMode(PARTICLE_ENUM _blendType){blendType = _blendType;	}
	/*
	@brief�@�`������邩�ǂ�����ݒ�
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief�@�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	bool GetVisible() const { return visible; }

	/*
	@param _drawOrder �`�揇
	*/
	void SetDrawOrder(int _drawOrder) { drawOrder = _drawOrder; }

	/*
	@return �`�揇
	*/
	int GetDrawOrder() { return drawOrder; }

	/*
	@param _offset �e�I�u�W�F�N�g�̍��W�ƕ`��ʒu�̍�
	*/
	void SetOffSet(Vector3 _offset) { offset = _offset; };

	/*
	@param _flag ���]���s����
	*/
	void SetReverce(bool _flag) { reverce = _flag; }
};

Matrix4 GetBillboardMatrix();
