#pragma once

#include "PhysicsWorld.h"
#include "ColliderComponent.h"



/*
 @file LineSegmentCollider.h
 @brief �����̓����蔻��N���X�i�������j
*/

class LineSegmentCollider : public ColliderComponent
{
public:
	/**
	@brief	�R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	���̃I�u�W�F�N�g�Ɠ����������ɌĂ΂��֐��|�C���^(GetOnCollisionFunc���Ă�)
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	@param	�����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
	*/
	LineSegmentCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag,onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/**
	@brief	�f�X�g���N�^
	*/
	virtual ~LineSegmentCollider();

	/**
	@brief	Transform�̃��[���h�ϊ�
	*/
	void OnUpdateWorldTransform() override;

	/**
	@brief	�����蔻��Ɏg�������̐ݒ�
	@param	�I�u�W�F�N�g�̑傫���ɍ��킹�������̍\����
	*/
	void SetObjectLineSegment(const LineSegment& _lineSegment) { objectLineSegment = _lineSegment; }
	void Setvalue(const float& _value) { value = _value; }
	void SetforwardVector(const Vector3& _forward) { forwardVec = _forward; }

	/**
	@brief	�����蔻�莞�Ɏg�����[���h��Ԃł̐���Vector���擾����
	@return ���S�����[���h���W�ɍ��킹������Vector
	*/
	LineSegment GetWorldLineSegment() const { return worldLineSegment; }
	float GetContactPoint(){ return contactPoint; }
	float contactPoint;
private:
	//===================== private�̃����o�ϐ� ======================//

	LineSegment objectLineSegment;
	LineSegment worldLineSegment;
	float value;
	Vector3 forwardVec;

};

