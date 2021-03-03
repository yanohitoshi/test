#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float _degrees)
	{
		return _degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float _radians)
	{
		return _radians * 180.0f / Pi;
	}

	inline bool NearZero(float _val, float _epsilon = 0.001f)
	{
		if (fabs(_val) <= _epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& _a, const T& _b)
	{
		return (_a < _b ? _b : _a);
	}

	template <typename T>
	T Min(const T& _a, const T& _b)
	{
		return (_a < _b ? _a : _b);
	}

	template <typename T>
	T Clamp(const T& _value, const T& _lower, const T& _upper)
	{
		return Min(_upper, Max(_lower, _value));
	}

	inline float Abs(float _value)
	{
		return fabs(_value);
	}

	inline float Cos(float _angle)
	{
		return cosf(_angle);
	}

	inline float Sin(float _angle)
	{
		return sinf(_angle);
	}

	inline float Tan(float _angle)
	{
		return tanf(_angle);
	}

	inline float Acos(float _value)
	{
		return acosf(_value);
	}

	inline float Atan2(float _y, float _x)
	{
		return atan2f(_y, _x);
	}

	inline float Cot(float _angle)
	{
		return 1.0f / Tan(_angle);
	}

	inline float Lerp(float _a, float _b, float _f)
	{
		return _a + _f * (_b - _a);
	}

	inline float Sqrt(float _value)
	{
		return sqrtf(_value);
	}

	inline float Fmod(float _numer, float _denom)
	{
		return fmod(_numer, _denom);
	}

	float ease_in(float t, float b, float c, float d);

	float ease_out(float t, float b, float c, float d);

	float ease_in_out(float t, float b, float c, float d);
	
}

// 2D Vector
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{}

	explicit Vector2(float _inX, float _inY)
		:x(_inX)
		, y(_inY)
	{}

	// Set both components in one line
	void Set(float _inX, float _inY)
	{
		x = _inX;
		y = _inY;
	}

	// Vector addition (a + b)
	friend Vector2 operator+(const Vector2& _a, const Vector2& _b)
	{
		return Vector2(_a.x + _b.x, _a.y + _b.y);
	}

	// Vector subtraction (a - b)
	friend Vector2 operator-(const Vector2& _a, const Vector2& _b)
	{
		return Vector2(_a.x - _b.x, _a.y - _b.y);
	}

	// Component-wise multiplication
	// (a.x * b.x, ...)
	friend Vector2 operator*(const Vector2& _a, const Vector2& _b)
	{
		return Vector2(_a.x * _b.x, _a.y * _b.y);
	}

	// Scalar multiplication
	friend Vector2 operator*(const Vector2& _vec, float _scalar)
	{
		return Vector2(_vec.x * _scalar, _vec.y * _scalar);
	}

	// Scalar multiplication
	friend Vector2 operator*(float _scalar, const Vector2& _vec)
	{
		return Vector2(_vec.x * _scalar, _vec.y * _scalar);
	}

	// Scalar *=
	Vector2& operator*=(float _scalar)
	{
		x *= _scalar;
		y *= _scalar;
		return *this;
	}

	// Vector +=
	Vector2& operator+=(const Vector2& _right)
	{
		x += _right.x;
		y += _right.y;
		return *this;
	}

	// Vector -=
	Vector2& operator-=(const Vector2& _right)
	{
		x -= _right.x;
		y -= _right.y;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	// Normalize the provided vector
	static Vector2 Normalize(const Vector2& _vec)
	{
		Vector2 temp = _vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector2& _a, const Vector2& _b)
	{
		return (_a.x * _b.x + _a.y * _b.y);
	}

	// Lerp from A to B by f
	static Vector2 Lerp(const Vector2& _a, const Vector2& _b, float _f)
	{
		return Vector2(_a + _f * (_b - _a));
	}

	// Reflect V about (normalized) N
	static Vector2 Reflect(const Vector2& _v, const Vector2& _n)
	{
		return _v - 2.0f * Vector2::Dot(_v, _n) * _n;
	}

	// Transform vector by matrix
	static Vector2 Transform(const Vector2& _vec, const class Matrix3& _mat, float _w = 1.0f);

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};

// 3D Vector
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}

	explicit Vector3(float _inX, float _inY, float _inZ)
		:x(_inX)
		, y(_inY)
		, z(_inZ)
	{}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Set all three components in one line
	void Set(float _inX, float _inY, float _inZ)
	{
		x = _inX;
		y = _inY;
		z = _inZ;
	}

	// Vector addition (a + b)
	friend Vector3 operator+(const Vector3& _a, const Vector3& _b)
	{
		return Vector3(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z);
	}

	// Vector subtraction (a - b)
	friend Vector3 operator-(const Vector3& _a, const Vector3& _b)
	{
		return Vector3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
	}

	// Component-wise multiplication
	friend Vector3 operator*(const Vector3& _left, const Vector3& _right)
	{
		return Vector3(_left.x * _right.x, _left.y * _right.y, _left.z * _right.z);
	}

	// Scalar multiplication
	friend Vector3 operator*(const Vector3& _vec, float _scalar)
	{
		return Vector3(_vec.x * _scalar, _vec.y * _scalar, _vec.z * _scalar);
	}

	// Scalar multiplication
	friend Vector3 operator*(float _scalar, const Vector3& _vec)
	{
		return Vector3(_vec.x * _scalar, _vec.y * _scalar, _vec.z * _scalar);
	}

	friend Vector3 operator/(const Vector3& _vec, float _scalar)
	{
		return Vector3(_vec.x / _scalar, _vec.y / _scalar, _vec.z / _scalar);
	}

	friend bool operator!=(const Vector3& _vec1, const Vector3& _vec2)
	{
		bool clear = false;
		if (_vec1.x != _vec2.x)
		{
			clear = true;
		}
		if (_vec1.y != _vec2.y)
		{
			clear = true;

		}
		if (_vec1.z != _vec2.z)
		{
			clear = true;
		}
		return clear;
	}

	friend bool operator==(const Vector3& _vec1, const Vector3& _vec2)
	{
		bool clear = true;
		if (_vec1.x != _vec2.x)
		{
			clear = false;
		}
		if (_vec1.y != _vec2.y)
		{
			clear = false;

		}
		if (_vec1.z != _vec2.z)
		{
			clear = false;
		}
		return clear;
	}

	// Scalar *=
	Vector3& operator*=(float _scalar)
	{
		x *= _scalar;
		y *= _scalar;
		z *= _scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& _right)
	{
		x += _right.x;
		y += _right.y;
		z += _right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& _right)
	{
		x -= _right.x;
		y -= _right.y;
		z -= _right.z;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x * x + y * y + z * z);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	//vectorの正規化
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	// Normalize the provided vector
	//正規化の提供
	static Vector3 Normalize(const Vector3& _vec)
	{
		Vector3 temp = _vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	//スカラー積
	static float Dot(const Vector3& _a, const Vector3& _b)
	{
		return (_a.x * _b.x + _a.y * _b.y + _a.z * _b.z);
	}

	// Cross product between two vectors (a cross b)
	//2つのベクトルの外積
	static Vector3 Cross(const Vector3& _a, const Vector3& _b)
	{
		Vector3 temp;
		temp.x = _a.y * _b.z - _a.z * _b.y;
		temp.y = _a.z * _b.x - _a.x * _b.z;
		temp.z = _a.x * _b.y - _a.y * _b.x;
		return temp;
	}

	// Lerp from A to B by f(線形補間)
	static Vector3 Lerp(const Vector3& _a, const Vector3& _b, float _f)
	{
		return Vector3(_a + _f * (_b - _a));
	}

	// Reflect V about (normalized) N
	static Vector3 Reflect(const Vector3& _v, const Vector3& _n)
	{
		return _v - 2.0f * Vector3::Dot(_v, _n) * _n;
	}

	static Vector3 Transform(const Vector3& _vec, const class Matrix4& _mat, float _w = 1.0f);
	// This will transform the vector and renormalize the w component
	static Vector3 TransformWithPerspDiv(const Vector3& _vec, const class Matrix4& _mat, float _w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vector3 Transform(const Vector3& _v, const class Quaternion& _q);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 NegUnitX;
	static const Vector3 NegUnitY;
	static const Vector3 NegUnitZ;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;
};

// 3x3 Matrix
class Matrix3
{
public:
	float mat[3][3];

	Matrix3()
	{
		*this = Matrix3::Identity;
	}

	explicit Matrix3(float _inMat[3][3])
	{
		memcpy(mat, _inMat, 9 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication
	friend Matrix3 operator*(const Matrix3& _left, const Matrix3& _right)
	{
		Matrix3 retVal;
		// row 0
		retVal.mat[0][0] =
			_left.mat[0][0] * _right.mat[0][0] +
			_left.mat[0][1] * _right.mat[1][0] +
			_left.mat[0][2] * _right.mat[2][0];

		retVal.mat[0][1] =
			_left.mat[0][0] * _right.mat[0][1] +
			_left.mat[0][1] * _right.mat[1][1] +
			_left.mat[0][2] * _right.mat[2][1];

		retVal.mat[0][2] =
			_left.mat[0][0] * _right.mat[0][2] +
			_left.mat[0][1] * _right.mat[1][2] +
			_left.mat[0][2] * _right.mat[2][2];

		// row 1
		retVal.mat[1][0] =
			_left.mat[1][0] * _right.mat[0][0] +
			_left.mat[1][1] * _right.mat[1][0] +
			_left.mat[1][2] * _right.mat[2][0];

		retVal.mat[1][1] =
			_left.mat[1][0] * _right.mat[0][1] +
			_left.mat[1][1] * _right.mat[1][1] +
			_left.mat[1][2] * _right.mat[2][1];

		retVal.mat[1][2] =
			_left.mat[1][0] * _right.mat[0][2] +
			_left.mat[1][1] * _right.mat[1][2] +
			_left.mat[1][2] * _right.mat[2][2];

		// row 2
		retVal.mat[2][0] =
			_left.mat[2][0] * _right.mat[0][0] +
			_left.mat[2][1] * _right.mat[1][0] +
			_left.mat[2][2] * _right.mat[2][0];

		retVal.mat[2][1] =
			_left.mat[2][0] * _right.mat[0][1] +
			_left.mat[2][1] * _right.mat[1][1] +
			_left.mat[2][2] * _right.mat[2][1];

		retVal.mat[2][2] =
			_left.mat[2][0] * _right.mat[0][2] +
			_left.mat[2][1] * _right.mat[1][2] +
			_left.mat[2][2] * _right.mat[2][2];

		return retVal;
	}

	Matrix3& operator*=(const Matrix3& _right)
	{
		*this = *this * _right;
		return *this;
	}

	// Create a scale matrix with x and y scales
	static Matrix3 CreateScale(float _xScale, float _yScale)
	{
		float temp[3][3] =
		{
			{ _xScale, 0.0f, 0.0f },
		{ 0.0f, _yScale, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	static Matrix3 CreateScale(const Vector2& _scaleVector)
	{
		return CreateScale(_scaleVector.x, _scaleVector.y);
	}

	// Create a scale matrix with a uniform factor
	static Matrix3 CreateScale(float _scale)
	{
		return CreateScale(_scale, _scale);
	}

	// Create a rotation matrix about the Z axis
	// theta is in radians
	static Matrix3 CreateRotation(float _theta)
	{
		float temp[3][3] =
		{
			{ Math::Cos(_theta), Math::Sin(_theta), 0.0f },
		{ -Math::Sin(_theta), Math::Cos(_theta), 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	// Create a translation matrix (on the xy-plane)
	static Matrix3 CreateTranslation(const Vector2& _trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ _trans.x, _trans.y, 1.0f },
		};
		return Matrix3(temp);
	}

	static const Matrix3 Identity;
};

// 4x4 Matrix
class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(float _inMat[4][4])
	{
		memcpy(mat, _inMat, 16 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(const Matrix4& _a, const Matrix4& _b)
	{
		Matrix4 retVal;
		// row 0
		retVal.mat[0][0] =
			_a.mat[0][0] * _b.mat[0][0] +
			_a.mat[0][1] * _b.mat[1][0] +
			_a.mat[0][2] * _b.mat[2][0] +
			_a.mat[0][3] * _b.mat[3][0];

		retVal.mat[0][1] =
			_a.mat[0][0] * _b.mat[0][1] +
			_a.mat[0][1] * _b.mat[1][1] +
			_a.mat[0][2] * _b.mat[2][1] +
			_a.mat[0][3] * _b.mat[3][1];

		retVal.mat[0][2] =
			_a.mat[0][0] * _b.mat[0][2] +
			_a.mat[0][1] * _b.mat[1][2] +
			_a.mat[0][2] * _b.mat[2][2] +
			_a.mat[0][3] * _b.mat[3][2];

		retVal.mat[0][3] =
			_a.mat[0][0] * _b.mat[0][3] +
			_a.mat[0][1] * _b.mat[1][3] +
			_a.mat[0][2] * _b.mat[2][3] +
			_a.mat[0][3] * _b.mat[3][3];

		// row 1
		retVal.mat[1][0] =
			_a.mat[1][0] * _b.mat[0][0] +
			_a.mat[1][1] * _b.mat[1][0] +
			_a.mat[1][2] * _b.mat[2][0] +
			_a.mat[1][3] * _b.mat[3][0];

		retVal.mat[1][1] =
			_a.mat[1][0] * _b.mat[0][1] +
			_a.mat[1][1] * _b.mat[1][1] +
			_a.mat[1][2] * _b.mat[2][1] +
			_a.mat[1][3] * _b.mat[3][1];

		retVal.mat[1][2] =
			_a.mat[1][0] * _b.mat[0][2] +
			_a.mat[1][1] * _b.mat[1][2] +
			_a.mat[1][2] * _b.mat[2][2] +
			_a.mat[1][3] * _b.mat[3][2];

		retVal.mat[1][3] =
			_a.mat[1][0] * _b.mat[0][3] +
			_a.mat[1][1] * _b.mat[1][3] +
			_a.mat[1][2] * _b.mat[2][3] +
			_a.mat[1][3] * _b.mat[3][3];

		// row 2
		retVal.mat[2][0] =
			_a.mat[2][0] * _b.mat[0][0] +
			_a.mat[2][1] * _b.mat[1][0] +
			_a.mat[2][2] * _b.mat[2][0] +
			_a.mat[2][3] * _b.mat[3][0];

		retVal.mat[2][1] =
			_a.mat[2][0] * _b.mat[0][1] +
			_a.mat[2][1] * _b.mat[1][1] +
			_a.mat[2][2] * _b.mat[2][1] +
			_a.mat[2][3] * _b.mat[3][1];

		retVal.mat[2][2] =
			_a.mat[2][0] * _b.mat[0][2] +
			_a.mat[2][1] * _b.mat[1][2] +
			_a.mat[2][2] * _b.mat[2][2] +
			_a.mat[2][3] * _b.mat[3][2];

		retVal.mat[2][3] =
			_a.mat[2][0] * _b.mat[0][3] +
			_a.mat[2][1] * _b.mat[1][3] +
			_a.mat[2][2] * _b.mat[2][3] +
			_a.mat[2][3] * _b.mat[3][3];

		// row 3
		retVal.mat[3][0] =
			_a.mat[3][0] * _b.mat[0][0] +
			_a.mat[3][1] * _b.mat[1][0] +
			_a.mat[3][2] * _b.mat[2][0] +
			_a.mat[3][3] * _b.mat[3][0];

		retVal.mat[3][1] =
			_a.mat[3][0] * _b.mat[0][1] +
			_a.mat[3][1] * _b.mat[1][1] +
			_a.mat[3][2] * _b.mat[2][1] +
			_a.mat[3][3] * _b.mat[3][1];

		retVal.mat[3][2] =
			_a.mat[3][0] * _b.mat[0][2] +
			_a.mat[3][1] * _b.mat[1][2] +
			_a.mat[3][2] * _b.mat[2][2] +
			_a.mat[3][3] * _b.mat[3][2];

		retVal.mat[3][3] =
			_a.mat[3][0] * _b.mat[0][3] +
			_a.mat[3][1] * _b.mat[1][3] +
			_a.mat[3][2] * _b.mat[2][3] +
			_a.mat[3][3] * _b.mat[3][3];

		return retVal;
	}

	Matrix4& operator*=(const Matrix4& _right)
	{
		*this = *this * _right;
		return *this;
	}

	// Invert the matrix - super slow
	void Invert();

	// Get the translation component of the matrix
	Vector3 GetTranslation() const
	{
		return Vector3(mat[3][0], mat[3][1], mat[3][2]);
	}

	// Get the X axis of the matrix (forward)
	Vector3 GetXAxis() const
	{
		return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
	}

	// Get the Y axis of the matrix (left)
	Vector3 GetYAxis() const
	{
		return Vector3::Normalize(Vector3(mat[1][0], mat[1][1], mat[1][2]));
	}

	// Get the Z axis of the matrix (up)
	Vector3 GetZAxis() const
	{
		return Vector3::Normalize(Vector3(mat[2][0], mat[2][1], mat[2][2]));
	}

	// Extract the scale component from the matrix
	Vector3 GetScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Length();
		retVal.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Length();
		retVal.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Length();
		return retVal;
	}

	// Create a scale matrix with x, y, and z scales
	static Matrix4 CreateScale(float _xScale, float _yScale, float _zScale)
	{
		float temp[4][4] =
		{
			{ _xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, _yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, _zScale, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& _scaleVector)
	{
		return CreateScale(_scaleVector.x, _scaleVector.y, _scaleVector.z);
	}

	// Create a scale matrix with a uniform factor
	static Matrix4 CreateScale(float _scale)
	{
		return CreateScale(_scale, _scale, _scale);
	}

	// Rotation about x-axis
	static Matrix4 CreateRotationX(float _theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f , 0.0f },
		{ 0.0f, Math::Cos(_theta), Math::Sin(_theta), 0.0f },
		{ 0.0f, -Math::Sin(_theta), Math::Cos(_theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about y-axis
	static Matrix4 CreateRotationY(float _theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(_theta), 0.0f, -Math::Sin(_theta), 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ Math::Sin(_theta), 0.0f, Math::Cos(_theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about z-axis
	static Matrix4 CreateRotationZ(float _theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(_theta), Math::Sin(_theta), 0.0f, 0.0f },
		{ -Math::Sin(_theta), Math::Cos(_theta), 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Create a rotation matrix from a quaternion
	static Matrix4 CreateFromQuaternion(const class Quaternion& _q);

	static Matrix4 CreateTranslation(const Vector3& _trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ _trans.x, _trans.y, _trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateLookAt(const Vector3& _eye, const Vector3& _target, const Vector3& _up)
	{
		Vector3 zaxis = Vector3::Normalize(_target - _eye);
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(_up, zaxis));
		Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));
		Vector3 trans;
		trans.x = -Vector3::Dot(xaxis, _eye);
		trans.y = -Vector3::Dot(yaxis, _eye);
		trans.z = -Vector3::Dot(zaxis, _eye);

		float temp[4][4] =
		{
			{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
			{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
			{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateOrtho(float _width, float _height, float _near, float _far)
	{
		float temp[4][4] =
		{
			{ 2.0f / _width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / _height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f / (_far - _near), 0.0f },
		{ 0.0f, 0.0f, _near / (_near - _far), 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspectiveFOV(float _fovY, float _width, float _height, float _near, float _far)
	{
		float yScale = Math::Cot(_fovY / 2.0f);
		float xScale = yScale * _height / _width;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, _far / (_far - _near), 1.0f },
		{ 0.0f, 0.0f, -_near * _far / (_far - _near), 0.0f }
		};
		return Matrix4(temp);
	}

	// Create "Simple" View-Projection Matrix from Chapter 6
	static Matrix4 CreateSimpleViewProj(float _width, float _height)
	{
		float temp[4][4] =
		{
			{ 2.0f / _width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / _height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(temp);
	}
	// 転置行列
	void Transpose();

	static const Matrix4 Identity;
};

// (Unit) Quaternion
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float _inX, float _inY, float _inZ, float _inW)
	{
		Set(_inX, _inY, _inZ, _inW);
	}

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& _axis, float _angle)
	{
		float scalar = Math::Sin(_angle / 2.0f);
		x = _axis.x * scalar;
		y = _axis.y * scalar;
		z = _axis.z * scalar;
		w = Math::Cos(_angle / 2.0f);
	}

	// Directly set the internal components
	void Set(float _inX, float _inY, float _inZ, float _inW)
	{
		x = _inX;
		y = _inY;
		z = _inZ;
		w = _inW;
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float LengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	// Normalize the provided quaternion
	static Quaternion Normalize(const Quaternion& _q)
	{
		Quaternion retVal = _q;
		retVal.Normalize();
		return retVal;
	}

	// Linear interpolation
	static Quaternion Lerp(const Quaternion& _a, const Quaternion& _b, float _f)
	{
		Quaternion retVal;
		retVal.x = Math::Lerp(_a.x, _b.x, _f);
		retVal.y = Math::Lerp(_a.y, _b.y, _f);
		retVal.z = Math::Lerp(_a.z, _b.z, _f);
		retVal.w = Math::Lerp(_a.w, _b.w, _f);
		retVal.Normalize();
		return retVal;
	}

	static float Dot(const Quaternion& _a, const Quaternion& _b)
	{
		return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z + _a.w * _b.w;
	}

	// Spherical Linear Interpolation
	static Quaternion Slerp(const Quaternion& _a, const Quaternion& _b, float _f)
	{
		float rawCosm = Quaternion::Dot(_a, _b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Math::Acos(cosom);
			const float invSin = 1.f / Math::Sin(omega);
			scale0 = Math::Sin((1.f - _f) * omega) * invSin;
			scale1 = Math::Sin(_f * omega) * invSin;
		}
		else
		{
			// Use linear interpolation if the quaternions
			// are collinear
			scale0 = 1.0f - _f;
			scale1 = _f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * _a.x + scale1 * _b.x;
		retVal.y = scale0 * _a.y + scale1 * _b.y;
		retVal.z = scale0 * _a.z + scale1 * _b.z;
		retVal.w = scale0 * _a.w + scale1 * _b.w;
		retVal.Normalize();
		return retVal;
	}

	// Concatenate
	// Rotate by q FOLLOWED BY p
	static Quaternion Concatenate(const Quaternion& _q, const Quaternion& _p)
	{
		Quaternion retVal;

		// Vector component is:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(_q.x, _q.y, _q.z);
		Vector3 pv(_p.x, _p.y, _p.z);
		Vector3 newVec = _p.w * qv + _q.w * pv + Vector3::Cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// Scalar component is:
		// ps * qs - pv . qv
		retVal.w = _p.w * _q.w - Vector3::Dot(pv, qv);

		return retVal;
	}

	//回転行列をクォータニオンにする
	static Quaternion MatrixToQuaternion(Matrix4 mat) {
		Quaternion q;

		float s;
		float tr = mat.mat[0][0] + mat.mat[1][1] + mat.mat[2][2] + 1.0f;
		if (tr >= 1.0f) {
			s = 0.5f / sqrt(tr);
			q.w = 0.25f / s;
			q.x = (mat.mat[1][2] - mat.mat[2][1]) * s;
			q.y = (mat.mat[2][0] - mat.mat[0][2]) * s;
			q.z = (mat.mat[0][1] - mat.mat[1][0]) * s;
			return q;
		}
		else {
			float max;
			if (mat.mat[1][1] > mat.mat[2][2]) {
				max = mat.mat[1][1];
			}
			else {
				max = mat.mat[2][2];
			}

			if (max < mat.mat[0][0]) {
				s = sqrt(mat.mat[0][0] - (mat.mat[1][1] + mat.mat[2][2]) + 1.0f);
				float x = s * 0.5f;
				s = 0.5f / s;
				q.x = x;
				q.y = (mat.mat[0][1] + mat.mat[1][0]) * s;
				q.z = (mat.mat[2][0] + mat.mat[0][2]) * s;
				q.w = (mat.mat[1][2] - mat.mat[2][1]) * s;
				return q;
			}
			else if (max == mat.mat[1][1]) {
				s = sqrt(mat.mat[1][1] - (mat.mat[2][2] + mat.mat[0][0]) + 1.0f);
				float y = s * 0.5f;
				s = 0.5f / s;
				q.x = (mat.mat[0][1] + mat.mat[1][0]) * s;
				q.y = y;
				q.z = (mat.mat[1][2] + mat.mat[2][1]) * s;
				q.w = (mat.mat[2][0] - mat.mat[0][2]) * s;
				return q;
			}
			else {
				s = sqrt(mat.mat[2][2] - (mat.mat[0][0] + mat.mat[1][1]) + 1.0f);
				float z = s * 0.5f;
				s = 0.5f / s;
				q.x = (mat.mat[2][0] + mat.mat[0][2]) * s;
				q.y = (mat.mat[1][2] + mat.mat[2][1]) * s;
				q.z = z;
				q.w = (mat.mat[0][1] - mat.mat[1][0]) * s;
				return q;
			}
		}
	}

	static const Quaternion Identity;
};

namespace Color
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}