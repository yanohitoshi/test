#pragma once
#include "GameObject.h"
#include "CameraObjectBase.h"
#include "PlayerObject.h"

/*
@file MainCameraObject.h
@brief ���C���J���� �Q�[�����̃I�u�W�F�N�g���f��
*/

class LineSegmentCollider;
class SphereCollider;
class BoxCollider;

class MainCameraObject :
	public CameraObjectBase
{
public:
	/*
	@brief	�R���X�g���N�^
	@param	�|�W�V����
	*/
	MainCameraObject(const Vector3 _pos);
	~MainCameraObject();

	//���̃N���X�̓|�[�Y���ɕʃN���X����X�V�֐����Ă΂�邱�Ƃ�����
	void UpdateGameObject(float _deltaTime = 1.0f)override;
	void GameObjectInput(const InputState& _keyState)override;
	/*
	@param _offset�@���������W�Ƃ̍�
	@param _parentPos�@������W
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);
	void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

	void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }
	Vector3 GetCameraVec() { return forwardVec; }
	void ReSetYaw() { yaw = Math::ToRadians(180); }

private:


	//�e�I�u�W�F�N�g�Ƃ̍�
	Vector3 offsetPos;
	//�Ǐ]��̃I�u�W�F�N�g���W
	Vector3 lerpObjectPos;
	//�Ǐ]��̃I�u�W�F�N�g���������Ă��邩
	bool hasParentObject;
	Vector3 cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 direction;
	Vector3 vel;
	//�J�����̍���
	float height;
	//�J������]�v�Z�p�̃��[�ƃs�b�`
	float yaw;
	float pitch;
	//�J�����̈ړ����x
	static const float yawSpeed;
	static const float pitchSpeed;

	//�J������]�̔��a
	float r;

	//�ړ���position
	Vector3 tmpMovePos;
	Vector3 tmpPosition;
	//�O���x�N�g��
	//Vector3 forwardVec;
	void OnCollision(const GameObject& _hitObject)override;
	LineSegmentCollider* lineSegmentCollider;
	SphereCollider* sphereCollider;
	BoxCollider* boxcollider;

	Matrix4 view;

	int cameraTutorialCount;
	bool tutorialCameraFlag;

	bool input;
};

