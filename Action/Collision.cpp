#include "Collision.h"
#include <algorithm>
#include <array>

/*
@param	�����̊J�n�n�_�̃|�W�V����
@param	�����̏I���n�_�̃|�W�V����
*/
LineSegment::LineSegment(const Vector3 & _start, const Vector3 & _end)
	:start(_start)
	, end(_end)
{
}

/*
@brief	������̓_��Ԃ�
@param	���͒l t�iL(t) = Start + (End - Start)t�j
@return ������̓_�̃|�W�V����
*/
Vector3 LineSegment::PointOnSegment(float _t) const
{
	return start + (end - start) * _t;
}

/*
@brief	�_�Ɛ����̊Ԃ̍ŒZ������Ԃ�
@param	�C�ӂ̓_�̃|�W�V����
@return �ŒZ����
*/
float LineSegment::MinDistanceSquared(const Vector3 & _point) const
{
	Vector3 ab = end - start;
	Vector3 ba = -1.0f * ab;
	Vector3 ac = _point - start;
	Vector3 bc = _point - end;

	if (Vector3::Dot(ab, ac) < 0.0f)
	{
		return ac.LengthSq();
	}
	else if (Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSq();
	}
	else
	{
		float scalar = Vector3::Dot(ac, ab) / Vector3::Dot(ab, ab);
		Vector3 p = scalar * ab;
		return (ac - p).LengthSq();
	}
}

/*
@brief	�����Ɛ����̊Ԃ̍ŒZ������Ԃ�
@param	���肷������̍\���̂P
@param	���肷������̍\���̂Q
@return �ŒZ����
*/
float LineSegment::MinDistanceSquared(const LineSegment & _line1, const LineSegment & _line2)
{
	Vector3 u = _line1.end - _line1.start;
	Vector3 v = _line2.end - _line2.start;
	Vector3 w = _line1.start - _line2.start;
	float   a = Vector3::Dot(u, u);
	float   b = Vector3::Dot(u, v);
	float   c = Vector3::Dot(v, v);
	float   d = Vector3::Dot(u, w);
	float   e = Vector3::Dot(v, w);
	float   D = a * c - b * b;
	float   sc, sN, sD = D;
	float   tc, tN, tD = D;

	if (Math::NearZero(D))
	{
		sN = 0.0f;
		sD = 1.0f;
		tN = e;
		tD = c;
	}
	else
	{
		sN = (b*e - c * d);
		tN = (a*e - b * d);
		if (sN < 0.0)
		{
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD)
		{
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
}

/*
@param	���ʂ̖@���x�N�g��
@param	���ʂƌ��_�̕������ŒZ����
*/
Plane::Plane(const Vector3 & _normal, float _distance)
	:normal(_normal)
	, distance(_distance)
{
}

/*
@param	���ʏ�̓_1
@param	���ʏ�̓_2
@param	���ʏ�̓_3
*/
Plane::Plane(const Vector3 & _vec1, const Vector3 & _vec2, const Vector3 & _vec3)
{
	Vector3 ab = _vec2 - _vec1;
	Vector3 ac = _vec3 - _vec1;

	normal = Vector3::Cross(ab, ac);
	normal.Normalize();

	distance = -Vector3::Dot(_vec1, normal);

}

/*
@brief	�_�ƕ��ʂ̍ŒZ������Ԃ�
@param	�C�ӂ̓_�̃|�W�V����
@return �������ŒZ����
*/
float Plane::SignedDistance(const Vector3& _point)
{
	return Vector3::Dot(_point, normal) - distance;
}

/*
@param	���̂̒��S���W
@param	���̂̔��a
*/
Sphere::Sphere(const Vector3 & _center, const float _radius)
	:center(_center)
	, radius(_radius)
{
}

/*
@brief	���̂ɓ_���܂܂�Ă��邩�ǂ���
@param	�C�ӂ̓_
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Sphere::Contains(const Vector3 & _point) const
{
	float distansSquared = (center - _point).LengthSq();
	return distansSquared <= (radius * radius);
}

/*
@param	�ŏ���x,y,z�̒l�̃|�W�V����
@param	�ő��x,y,z�̒l�̃|�W�V����
*/
AABB::AABB(const Vector3 & _min, const Vector3 & _max)
	: min(_min),
	  max(_max)
{
}

/*
@brief	�ŏ��l�ƍő�l���e�������ƂɍX�V����
@param	�C�ӂ̓_�̃|�W�V����
*/
void AABB::UpdateMinMax(const Vector3 & _point)
{
	min.x = Math::Min(min.x, _point.x);
	min.y = Math::Min(min.y, _point.y);
	min.z = Math::Min(min.z, _point.z);

	max.x = Math::Max(max.x, _point.x);
	max.y = Math::Max(max.y, _point.y);
	max.z = Math::Max(max.z, _point.z);
}

/*
@brief	�����蔻��{�b�N�X�̉�]
@param	��]���Ɖ�]�\���l�iQuaternion�j
*/
void AABB::Rotate(const Quaternion & _quaternion)
{
	std::array<Vector3, 8> points;

	points[0] = min;

	points[1] = Vector3(max.x, min.y, min.z);
	points[2] = Vector3(min.x, max.y, min.z);
	points[3] = Vector3(min.x, min.y, max.z);

	points[4] = Vector3(min.x, max.y, max.z);
	points[5] = Vector3(max.x, min.y, max.z);
	points[6] = Vector3(max.x, max.y, min.z);

	points[7] = Vector3(max);

	Vector3 p = Vector3::Transform(points[0], _quaternion);

	min = p;
	max = p;

	for (std::size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], _quaternion);
		UpdateMinMax(p);
	}
}

/*
@brief	�{�b�N�X�ɓ_���܂܂�Ă��邩�ǂ���
@param	�C�ӂ̓_
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool AABB::Contains(const Vector3 & _point) const
{
	bool outside =
        _point.x < min.x ||
        _point.y < min.y ||
        _point.z < min.x ||
        _point.x > max.x ||
        _point.y > max.y ||
        _point.z > max.z;
	//�ǂ���^�łȂ���΃{�b�N�X�̒��ɓ_������
	return !outside;
}

/*
@brief	�_�ƃ{�b�N�X�̍ŒZ������Ԃ�
@param	�C�ӂ̓_
@return �ŒZ����
*/
float AABB::MinDistanceSquared(const Vector3 & _point) const
{
	float dx = Math::Max(min.x - _point.x, 0.0f);
	dx = Math::Max(dx, _point.x - max.x);
	float dy = Math::Max(min.y - _point.y, 0.0f);
	dy = Math::Max(dy, _point.y - max.y);
	float dz = Math::Max(min.z - _point.z, 0.0f);
	dz = Math::Max(dz, _point.z - max.z);

	return dx * dx + dy * dy + dz * dz;
}

/*
@param	�n�_�ƂȂ�_�̍��W
@param	�I�_�ƂȂ�_�̍��W
@param	�J�v�Z���̔��a
*/
Capsule::Capsule(const Vector3 & _start, const Vector3 & _end, float _radius)
	:segment(_start, _end)
	, radius(_radius)
{
}

/*
@brief	�J�v�Z���̎n�_�ƏI�_�̐�����̓_��Ԃ�
@param	���͒l t�iL(t) = Start + (End - Start)t�j
@return ������̓_�̃|�W�V����
*/
Vector3 Capsule::PointOnSegment(float _t) const
{
	return segment.PointOnSegment(_t);
}

/*
@brief	�J�v�Z���ɓ_���܂܂�Ă��邩�ǂ���
@param	�C�ӂ̓_
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Capsule::Contains(const Vector3 & _point) const
{
	float distanceSquared = segment.MinDistanceSquared(_point);
	return distanceSquared <= (radius * radius);
}

/*
@brief	�Q�����̃|���S���ɓ_���܂܂�Ă��邩�ǂ���
@param	�C�ӂ̓_
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool ConvexPolygon::Contains(const Vector2 & _point) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (std::size_t i = 0; i < vertices.size() - 1; i++)
	{
		a = vertices[i] - _point;
		a.Normalize();

		b = vertices[i + 1] - _point;
		b.Normalize();

		sum += Math::Acos(Vector2::Dot(a, b));
	}

	a = vertices.back() - _point;
	a.Normalize();
	b = vertices.front() - _point;
	b.Normalize();
	sum += Math::Acos(Vector2::Dot(a, b));

	return Math::NearZero(sum - Math::TwoPi);
}

/*
@brief	���Ƌ��̓����蔻��
@param	���̍\���̂P
@param	���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Sphere & _sphere1, const Sphere & _sphere2)
{
	float distanceSquared = (_sphere1.center - _sphere2.center).LengthSq();
	float sumRadius = _sphere1.radius + _sphere2.radius;
	return distanceSquared <= (sumRadius * sumRadius);
}

/*
@brief	�{�b�N�X�ƃ{�b�N�X�̓����蔻��
@param	�{�b�N�X�̍\���̂P
@param	�{�b�N�X�̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const AABB & _AABB1, const AABB & _AABB2)
{
	bool no =
        _AABB1.max.x < _AABB2.min.x ||
        _AABB1.max.y < _AABB2.min.y ||
        _AABB1.max.z < _AABB2.min.z ||
        _AABB2.max.x < _AABB1.min.x ||
        _AABB2.max.y < _AABB1.min.y ||
        _AABB2.max.z < _AABB1.min.z;
	//�����̂ǂ���^�łȂ���΁A�������Ă���
	return !no;
}

/*
@brief	�J�v�Z���ƃJ�v�Z���̓����蔻��
@param	�J�v�Z���̍\���̂P
@param	�J�v�Z���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Capsule & _capsule1, const Capsule & _capsule2)
{
	float distanceSquared = LineSegment::MinDistanceSquared(_capsule1.segment,
        _capsule2.segment);
	float sumRadius = _capsule1.radius + _capsule2.radius;
	return distanceSquared <= (sumRadius * sumRadius);
}

/*
@brief	���ƃ{�b�N�X�̓����蔻��
@param	���̍\����
@param	�{�b�N�X�̍\����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Sphere & _sphere, const AABB & _AABB)
{
	bool hit = _AABB.Contains(_sphere.center);
	if (hit)
	{
		//printf("%f,%f\n",_sphere.center,_sphere.radius);
		//printf("%f,%f\n", _AABB.min, _AABB.max);
		return true;
	}
	float distanceSquared = _AABB.MinDistanceSquared(_sphere.center);
	return distanceSquared <= (_sphere.radius * _sphere.radius);
}

/*
@brief	�����Ƌ��̓����蔻��
@param	�����̍\����
@param	���̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment & _line, const Sphere & _sphere, float & _outT)
{
	Vector3 X = _line.start - _sphere.center;
    Vector3 Y = _line.end - _line.start;
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float c = Vector3::Dot(X, X) - _sphere.radius * _sphere.radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		discriminant = Math::Sqrt(discriminant);

		float tMin = (-b - discriminant) / (2.0f * a);
		float tMax = (-b + discriminant) / (2.0f * a);

		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			_outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			_outT = tMax;
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
@brief	�����ƕ��ʂ̓����蔻��
@param	�����̍\����
@param	���ʂ̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment & _line, const Plane & _plane, float & _outT)
{
	float denom = Vector3::Dot(_line.end - _line.start,
		_plane.normal);
	if (Math::NearZero(denom))
	{
		if (Math::NearZero(Vector3::Dot(_line.start, _plane.normal) - _plane.distance))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::Dot(_line.start, _plane.normal) - _plane.distance;
		_outT = numer / denom;
		if (_outT >= 0.0f && _outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
@brief	�e���ł̖ʂƐ����̓����蔻��
@param	�����̎n�_
@param	�����̏I�_
@param	���ʏ�̓_�̒l
@param	���ʂ̖@���x�N�g��
@param	�������������i�[����ϒ��R���e�i
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool TestSidePlane(float _start, float _end, float _negd, const Vector3& _norm,
	std::vector<std::pair<float, Vector3>>& _out)
{
	float denom = _end - _start;
	if (Math::NearZero(denom))
	{
		return false;
	}
	else
	{
		float numer = -_start + _negd;
		float t = numer / denom;
		// Test that t is within bounds
		if (t >= 0.0f && t <= 1.0f)
		{
			_out.emplace_back(t, _norm);
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
@brief	�����ƃ{�b�N�X�̓����蔻��
@param	�����̍\����
@param	�{�b�N�X�̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@param	�����̎n�_����ڐG�����ʂ̖@���x�N�g�����i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment & _line, const AABB & _AABB, float & _outT, Vector3 & _outNorm)
{
	std::vector<std::pair<float, Vector3>> values;

	TestSidePlane(_line.start.x, _line.end.x, _AABB.min.x, Vector3::NegUnitX, values);
	TestSidePlane(_line.start.x, _line.end.x, _AABB.max.x, Vector3::UnitX, values);
	TestSidePlane(_line.start.y, _line.end.y, _AABB.min.y, Vector3::NegUnitY, values);
	TestSidePlane(_line.start.y, _line.end.y, _AABB.max.y, Vector3::UnitY, values);
	TestSidePlane(_line.start.z, _line.end.z, _AABB.min.z, Vector3::NegUnitZ, values);
	TestSidePlane(_line.start.z, _line.end.z, _AABB.max.z, Vector3::UnitZ, values);

	std::sort(values.begin(), values.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b) {
			return a.first < b.first;
		});
	Vector3 point;
	for (auto& t : values)
	{
		point = _line.PointOnSegment(t.first);
		if (_AABB.Contains(point))
		{
            _outT = t.first;
            _outNorm = t.second;
			return true;
		}
	}
	return false;
}


/*
@fn	���X�C�[�v�̓����蔻��
@param	�P�t���[���O�̋��P�̍\����
@param	���݂̃t���[���̋��P�̍\����
@param	�P�t���[���O�̋��Q�̍\����
@param	���݂̃t���[���̋��Q�̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool SweptSphere(const Sphere & _sphere1, const Sphere & _sphere2, const Sphere & _sphere3, const Sphere & _sphere4, float & _outT)
{
	Vector3 X = _sphere1.center - _sphere3.center;
	Vector3 Y = _sphere2.center - _sphere1.center - (_sphere4.center - _sphere3.center);
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float sumRadius = _sphere1.radius + _sphere3.radius;
	float c = Vector3::Dot(X, X) - sumRadius * sumRadius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		discriminant = Math::Sqrt(discriminant);

        _outT = (-b - discriminant) / (2.0f * a);
		if (_outT >= 0.0f && _outT <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
