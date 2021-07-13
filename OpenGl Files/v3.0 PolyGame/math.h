#pragma once
#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <cmath>
#include "constants.h"

class Vector2
{
public:
	float x, y;
	Vector2() :x(0.0f), y(0.0f) {};
	explicit Vector2(float inX, float inY) :x(inX), y(inY) {};
	void Set(float inX, float inY) { x = inX; y = inY; }
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}
	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& right)
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
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}
	static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);
};
class Matrix3
{
public:
	float mat[3][3];
	static const Matrix3 Identity;
	Matrix3()
	{
		*this = Matrix3::Identity;
	};
	explicit Matrix3(float inMat[3][3])
	{
		memcpy(mat, inMat, 9 * sizeof(float));
	};
	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
	{
		Matrix3 retVal;

		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				retVal.mat[row][col] = (left.mat[row][0] * right.mat[0][col]) +
				(left.mat[row][1] * right.mat[1][col]) +
				(left.mat[row][2] * right.mat[2][col]);
		return retVal;
	};
	Matrix3& operator*=(Matrix3& right)
	{
		*this = *this * right;
		return *this;
	};
	static Matrix3 createScale(float xScale, float yScale)
	{
		float temp[3][3] =
		{
			{xScale, 0.0f, 0.0f},
			{0.0f, yScale, 0.0f},
			{0.0f, 0.0f, 1.0f}
		};
		return Matrix3(temp);
	};
	static Matrix3 createScale(const Vector2& scaleVector)
	{
		return createScale(scaleVector.x, scaleVector.y);
	};
	static Matrix3 createScale(float scale)
	{
		return createScale(scale, scale);
	};
	static Matrix3 createRotation(float theta)
	{
		float temp[3][3] =
		{
			{ cosf(theta), -sinf(theta), 0.0f },
			{ sinf(theta), cosf(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
		return Matrix3(temp);
	};
	static Matrix3 createTranslation(const Vector2& trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, trans.x },
			{ 0.0f, 1.0f, trans.y },
			{ 0.0f, 0.0f, 1.0f }
		};
		return Matrix3(temp);
	};
};
#endif