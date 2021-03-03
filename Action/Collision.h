#pragma once
#include "Math.h"
#include <vector>
#include <map>

/*
@file Collision.h
@brief �����`����A�O�p�`���̃I�u�W�F�N�g�錾
*/

//����
struct LineSegment
{
	/*
	@param	�����̊J�n�n�_�̃|�W�V����
	@param	�����̏I���n�_�̃|�W�V����
	*/
    LineSegment(const Vector3& _start, const Vector3& _end);
	
	/*
	@fn	������̓_��Ԃ�
	@param	���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����
	*/
	Vector3 PointOnSegment(float _t) const;

	/*
	@fn	�_�Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	�C�ӂ̓_�̃|�W�V����
	@return �ŒZ����
	*/
    float MinDistanceSquared(const Vector3& _point)const;

	/*
	@fn	�����Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	���肷������̍\���̂P
	@param	���肷������̍\���̂Q
	@return �ŒZ����
	*/
    static float MinDistanceSquared(const LineSegment& _line1,const LineSegment& _line2);

	//�����̊J�n�n�_
    Vector3 start;
	//�����̏I���n�_
    Vector3 end;
};

//����
struct Plane
{
	/*
	@param	���ʂ̖@���x�N�g��
	@param	���ʂƌ��_�̕������ŒZ����
	*/
    Plane(const Vector3& _normal, float _distance);

	/*
	@param	���ʏ�̓_1
	@param	���ʏ�̓_2
	@param	���ʏ�̓_3
	*/
    Plane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3);

	/*
	@fn	�_�ƕ��ʂ̍ŒZ������Ԃ�
	@param	�C�ӂ̓_�̃|�W�V����
	@return �������ŒZ����
	*/
    float SignedDistance(const Vector3& _point);

	//���ʂ̖@���x�N�g��
    Vector3 normal;
	//���ʂƌ��_�̕������ŒZ����
    float distance;
};

//��
struct Sphere
{
	/*
	@param	���̂̒��S���W
	@param	���̂̔��a
	*/
    Sphere(const Vector3& _center, const float _radius);
    
	/*
	@fn	���̂ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
	bool Contains(const Vector3& _point)const;

	//���̂̒��S���W
    Vector3 center;
	//���̂̔��a
    float radius;
};

//�����s�o�E���f�B���O�{�b�N�X(Axis-Aligned Bounding Box)
struct AABB
{
	/*
	@param	�ŏ���x,y,z�̒l�̃|�W�V����
	@param	�ő��x,y,z�̒l�̃|�W�V����
	*/
    AABB(const Vector3& _min,const Vector3& _max);

	/*
	@fn	�ŏ��l�ƍő�l���e�������ƂɍX�V����
	@param	�C�ӂ̓_�̃|�W�V����
	*/
    void UpdateMinMax(const Vector3& _point);

	/*
	@fn	�����蔻��{�b�N�X�̉�]
	@param	��]���Ɖ�]�\���l�iQuaternion�j
	*/
    void Rotate(const Quaternion& _quaternion);
    
	/*
	@fn	�{�b�N�X�ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
	bool Contains(const Vector3& _point)const;
    
	/*
	@fn	�_�ƃ{�b�N�X�̍ŒZ������Ԃ�
	@param	�C�ӂ̓_
	@return �ŒZ����
	*/
	float MinDistanceSquared(const Vector3& _point)const;

	void InitMinMax(const Vector3& _point) { min = max = _point; };

    Vector3 min;
    Vector3 max;
};

//�L���o�E���f�B���O�{�b�N�X�iOriented Bounding Box�j
//������
struct OBB
{
	//���S�̍��W
    Vector3 center;
	//��]�N�H�[�^�j�I��
    Quaternion rotation;
	//�{�b�N�X�̍L����i���A�����A���s���j
    Vector3 extents;
};

//�J�v�Z��
struct Capsule
{
	/*
	@param	�n�_�ƂȂ�_�̍��W
	@param	�I�_�ƂȂ�_�̍��W
	@param	�J�v�Z���̔��a
	*/
    Capsule(const Vector3& _start,const Vector3& _end,float _radius);

	/*
	@fn	�J�v�Z���̎n�_�ƏI�_�̐�����̓_��Ԃ�
	@param	���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����
	*/
    Vector3 PointOnSegment(float _t)const;

	/*
	@fn	�J�v�Z���ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
    bool Contains(const Vector3& _point)const;

	//�J�v�Z�����\���������
    LineSegment segment;
	//�J�v�Z���̔��a
    float radius;
};

//�ʃ|���S��
struct ConvexPolygon
{
	/*
	@fn	�Q�����̃|���S���ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
    bool Contains(const Vector2& _point)const;

	//���_�̉ϒ��R���e�i
    std::vector<Vector2> vertices;
};

/*
@fn	���Ƌ��̓����蔻��
@param	���̍\���̂P
@param	���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Sphere& _sphere1,const Sphere& _sphere2);

/*
@fn	�{�b�N�X�ƃ{�b�N�X�̓����蔻��
@param	�{�b�N�X�̍\���̂P
@param	�{�b�N�X�̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const AABB& _AABB1, const AABB& _AABB2);

/*
@fn	�J�v�Z���ƃJ�v�Z���̓����蔻��
@param	�J�v�Z���̍\���̂P
@param	�J�v�Z���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Capsule& _capsule1, const Capsule& _capsule2);

/*
@fn	���ƃ{�b�N�X�̓����蔻��
@param	���̍\����
@param	�{�b�N�X�̍\����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Sphere& _sphere, const AABB& _AABB);

/*
@fn	�����Ƌ��̓����蔻��
@param	�����̍\����
@param	���̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment& _line, const Sphere& _sphere, float& _outT);

/*
@fn	�����ƕ��ʂ̓����蔻��
@param	�����̍\����
@param	���ʂ̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment& _line, const Plane& _plane, float& _outT);

/*
@fn	�����ƃ{�b�N�X�̓����蔻��
@param	�����̍\����
@param	�{�b�N�X�̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@param	�����̎n�_����ڐG�����ʂ̖@���x�N�g�����i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment& _line, const AABB& _AABB, float& _outT,
    Vector3& outNorm);

///*
//@fn	�����ƃ{�b�N�X�̓����蔻��
//@param	�����̍\����
//@param	�{�b�N�X�̍\����
//@return true : �������Ă��� , false : �������Ă��Ȃ�
//*/
//bool Intersect(const LineSegment& _line, const AABB& _AABB);

/*
@fn	���X�C�[�v�̓����蔻��
@param	�P�t���[���O�̋��P�̍\����
@param	���݂̃t���[���̋��P�̍\����
@param	�P�t���[���O�̋��Q�̍\����
@param	���݂̃t���[���̋��Q�̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool SweptSphere(const Sphere& _sphere1, const Sphere& _sphere2,
    const Sphere& _sphere3, const Sphere& _sphere4, float& _outT);
