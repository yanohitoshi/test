#pragma once

#include "PhysicsWorld.h"
#include "ColliderComponent.h"


/*
 @file PlaneCollider.h
 @brief ���ʂ̓����蔻��N���X�i�������j
*/

class PlaneCollider : public ColliderComponent
{
public:
	/**
	@brief	�R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	���̃I�u�W�F�N�g�Ɠ����������ɌĂ΂��֐��|�C���^(GetOnCollisionFunc���Ă�)
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	@param	�����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
	*/
	PlaneCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/**
	@brief	�f�X�g���N�^
	*/
	virtual ~PlaneCollider();

	/**
	@brief	Transform�̃��[���h�ϊ�
	*/
	void OnUpdateWorldTransform() override;

	/**
	@brief	�����蔻��Ɏg�������̐ݒ�
	@param	�I�u�W�F�N�g�̑傫���ɍ��킹�������̍\����
	*/
	void SetObjectPlane(const Plane& _plane) { objectPlane = _plane; }

	/**
	@brief	�����蔻�莞�Ɏg�����[���h��Ԃł�Plane���擾����
	@return ���S�����[���h���W�ɍ��킹��Plane
	*/

	Plane GetWorldPlane() const { return worldPlane; }


private:
	//===================== private�̃����o�ϐ� ======================//

	Plane objectPlane;
	Plane worldPlane;

};

