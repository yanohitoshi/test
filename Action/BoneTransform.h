#pragma once
#include "Math.h"

/*
 @file BoneTransform.h
 @fn ���f���̃{�[���ϊ�
*/
class BoneTransform
{
public:
	//��]
	Quaternion mRotation;                     
	// �ړ�
	Vector3 mTranslation;                      
	/*
	@fn �s����o��
	@return ��]�ƕ��s�ړ�����A�s���Ԃ�
	*/
	Matrix4 ToMatrix() const;                  
	
	/*
	@fn �{�[�����
	*/
	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f); 
};
