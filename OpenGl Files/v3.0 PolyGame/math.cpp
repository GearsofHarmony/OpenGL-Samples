#include "math.h"

static float m3Ident[3][3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};
const Matrix3 Matrix3::Identity(m3Ident);
Vector2 Vector2::Transform(const Vector2& vec, const class Matrix3& mat, float w)
{
	Vector2 retVal;
	retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[0][1] + w * mat.mat[0][2];
	retVal.y = vec.x * mat.mat[1][0] + vec.y * mat.mat[1][1] + w * mat.mat[1][2];
	return retVal;
};