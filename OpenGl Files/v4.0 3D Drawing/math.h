#pragma once
#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <cmath>
#include "constants.h"

class Vec2
{
public:
	float x, y;
	Vec2() :x(0.0f), y(0.0f) {};
	explicit Vec2(float inX, float inY) :x(inX), y(inY) {};
	void Set(float inX, float inY) { x = inX; y = inY; }
	friend Vec2 operator+(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x + right.x, left.y + right.y);
	}
	friend Vec2 operator-(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x - right.x, left.y - right.y);
	}
	friend Vec2 operator*(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x * right.x, left.y * right.y);
	}
	friend Vec2 operator*(const Vec2& vec, float scalar)
	{
		return Vec2(vec.x * scalar, vec.y * scalar);
	}
	friend Vec2 operator*(float scalar, const Vec2& vec)
	{
		return Vec2(vec.x * scalar, vec.y * scalar);
	}
	Vec2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vec2& operator+=(const Vec2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}
	float Length() const
	{
		return sqrtf((x * x) + (y * y));
	}
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}
	static Vec2 Normalize(const Vec2& vec)
	{
		Vec2 temp = vec;
		temp.Normalize();
		return temp;
	}
	static float Dot(const Vec2& left, const Vec2& right)
	{
		return (left.x * right.x + left.y * right.y);
	}
	static Vec2 Transform(const Vec2& vec, const class Mat3& mat, float w = 1.0f);
};

class Vec3
{
public:
	float x, y, z;
	Vec3() :x(0.0f), y(0.0f), z(0.0f) {};
	explicit Vec3(float inX, float inY, float inZ) :x(inX), y(inY), z(inZ) {};
	void Set(float inX, float inY, float inZ) { x = inX; y = inY; z = inZ; }
	friend Vec3 operator+(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}
	friend Vec3 operator-(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}
	friend Vec3 operator*(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x * right.x, left.y * right.y, left.z * right.z);
	}
	friend Vec3 operator*(const Vec3& vec, float scalar)
	{
		return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
	friend Vec3 operator*(float scalar, const Vec3& vec)
	{
		return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
	Vec3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	Vec3& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	Vec3& operator+=(const Vec3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}
	float Length() const
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}
	static Vec3 Normalize(const Vec3& vec)
	{
		Vec3 temp = vec;
		temp.Normalize();
		return temp;
	}
	static float Dot(const Vec3& left, const Vec3& right)
	{
		return (left.x * right.x + left.y * right.y + left.z * right.z);
	}
	static Vec3 Cross(const Vec3& left, const Vec3& right)
	{
		Vec3 temp;
		temp.x = left.y * right.z - left.z * right.y;
		temp.y = left.z * right.x - left.x * right.z;
		temp.z = left.x * right.y - left.y * right.x;
		return temp;
	}
	static Vec3 Transform(const Vec3& vec, const class Mat4& mat, float w = 1.0f);
};

class Mat3
{
public:
	float mat[3][3];
	static const Mat3 Identity;
	Mat3()
	{
		*this = Mat3::Identity;
	};
	explicit Mat3(float inMat[3][3])
	{
		memcpy(mat, inMat, 9 * sizeof(float));
	};
	friend Mat3 operator*(const Mat3& left, const Mat3& right)
	{
		Mat3 retVal;

		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				for (int ii = 0; ii < 3; ii++)
					if (ii == 0)
						retVal.mat[row][col] = (left.mat[row][ii] * right.mat[ii][col]);
					else
						retVal.mat[row][col] += (left.mat[row][ii] * right.mat[ii][col]);
				//retVal.mat[row][col] = (left.mat[row][0] * right.mat[0][col]) +
				//						(left.mat[row][1] * right.mat[1][col]) +
				//						(left.mat[row][2] * right.mat[2][col]);
		return retVal;
	};
	//Mat3& operator*=(Mat3& right)
	//{
	//	*this = *this * right;
	//	return *this;
	//};
	static Mat3 createScale(float xScale, float yScale)
	{
		float temp[3][3] =
		{
			{xScale, 0.0f, 0.0f},
			{0.0f, yScale, 0.0f},
			{0.0f, 0.0f, 1.0f}
		};
		return Mat3(temp);
	};
	static Mat3 createScale(const Vec2& scaleVector)
	{
		return createScale(scaleVector.x, scaleVector.y);
	};
	static Mat3 createScale(float scale)
	{
		return createScale(scale, scale);
	};
	static Mat3 createRotation(float theta)
	{
		float temp[3][3] =
		{
			{ cosf(theta), -sinf(theta), 0.0f },
			{ sinf(theta), cosf(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
		return Mat3(temp);
	};
	static Mat3 createTranslation(const Vec2& trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, trans.x },
			{ 0.0f, 1.0f, trans.y },
			{ 0.0f, 0.0f, 1.0f }
		};
		return Mat3(temp);
	};
};

class Mat4
{
public:
	float mat[4][4];
	static const Mat4 Identity;
	Mat4()
	{
		*this = Mat4::Identity;
	};
	explicit Mat4(float inMat[4][4])
	{
		memcpy(mat, inMat, 16 * sizeof(float));
	};
	friend Mat4 operator*(const Mat4& left, const Mat4& right)
	{
		Mat4 retVal;

		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 4; col++)
				for (int ii = 0; ii < 4; ii++)
					if (ii == 0)
						retVal.mat[row][col] = (left.mat[row][ii] * right.mat[ii][col]);
					else
						retVal.mat[row][col] += (left.mat[row][ii] * right.mat[ii][col]);
					//retVal.mat[row][col] = (left.mat[row][0] * right.mat[0][col]) +
					//	(left.mat[row][1] * right.mat[1][col]) +
					//	(left.mat[row][2] * right.mat[2][col]) +
					//	(left.mat[row][3] * right.mat[3][col]);
		return retVal;
	};
	//Mat4& operator*=(Mat4& right)
	//{
	//	*this = *this * right;
	//	return *this;
	//};
	static Mat4 transpose(const Mat4& mat)
	{
		float temp[4][4];
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				temp[row][col] = mat.mat[col][row];
			}
		}
		return Mat4(temp);
	}
	static Mat4 createScale(float xScale, float yScale, float zScale)
	{
		float temp[4][4] =
		{
			{xScale, 0.0f, 0.0f, 0.0f},
			{0.0f, yScale, 0.0f,0.0f},
			{0.0f, 0.0f, zScale,0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};
		return Mat4(temp);
	};
	static Mat4 createScale(const Vec3& scaleVector)
	{
		return createScale(scaleVector.x, scaleVector.y, scaleVector.z);
	};
	static Mat4 createScale(float scale)
	{
		return createScale(scale, scale, scale);
	};
	static Mat4 createRotationX(float theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, cosf(theta), -sinf(theta), 0.0f },
			{ 0.0f, sinf(theta), cosf(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Mat4(temp);
	};
	static Mat4 createRotationY(float theta)
	{
		float temp[4][4] =
		{
			{ cosf(theta), 0.0f, sinf(theta), 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ -sinf(theta), 0.0f, cosf(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Mat4(temp);
	};
	static Mat4 createRotationZ(float theta)
	{
		float temp[4][4] =
		{
			{ cosf(theta), -sinf(theta), 0.0f, 0.0f },
			{ sinf(theta), cosf(theta), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Mat4(temp);
	};
	static Mat4 createTranslation(const Vec3& trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, trans.x },
			{ 0.0f, 1.0f, 0.0f, trans.y },
			{ 0.0f, 0.0f, 1.0f, trans.z },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Mat4(temp);
	};
	static Mat4 createLookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		Vec3 zaxis = Vec3::Normalize(target - eye);
		Vec3 xaxis = Vec3::Normalize(Vec3::Cross(zaxis, up));
		Vec3 yaxis = Vec3::Cross(xaxis, zaxis);
		Vec3 trans;
		trans.x = Vec3::Dot(xaxis, eye);
		trans.y = Vec3::Dot(yaxis, eye);
		trans.z = Vec3::Dot(zaxis, eye);
		float temp[4][4] =
		{
			{xaxis.x,xaxis.y,xaxis.z,-trans.x},
			{yaxis.x,yaxis.y,yaxis.z,-trans.y},
			{-zaxis.x,-zaxis.y,-zaxis.z,trans.z},
			{0.0f,0.0f,0.0f,1.0f}
		};
		return Mat4(temp);
	}
	static Mat4 createPerspectiveFOV(float fovY, float aspect, float zNear, float zFar)
	{
		float yScale = 1.0f / tanf(fovY / 2.0f);
		float xScale = 1.0f / aspect * yScale;
		float zz = -(zFar + zNear) / (zFar - zNear);
		float xx = -(2.0f * zFar * zNear) / (zFar - zNear);
		float yy = -1.0f;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, zz, xx },
			{ 0.0f, 0.0f, yy, 0.0f }
		};
		return Mat4(temp);
	};
};

#endif