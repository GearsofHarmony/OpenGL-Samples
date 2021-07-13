#include "math.h"

static float m3Ident[3][3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
}; 
static float m4Ident[4][4] =
{
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
const Mat3 Mat3::Identity(m3Ident);
const Mat4 Mat4::Identity(m4Ident);
Vec2 Vec2::Transform(const Vec2& vec, const class Mat3& mat, float w)
{
	Vec2 retVal;
	retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[0][1] + w * mat.mat[0][2];
	retVal.y = vec.x * mat.mat[1][0] + vec.y * mat.mat[1][1] + w * mat.mat[1][2];
	return retVal;
};
Vec3 Vec3::Transform(const Vec3& vec, const class Mat4& mat, float w)
{
	Vec3 retVal;
	retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[0][1] + vec.z * mat.mat[0][2] + w * mat.mat[0][3];
	retVal.y = vec.x * mat.mat[1][0] + vec.y * mat.mat[1][1] + vec.z * mat.mat[1][2] + w * mat.mat[1][3];
	retVal.z = vec.x * mat.mat[2][0] + vec.y * mat.mat[2][1] + vec.z * mat.mat[2][2] + w * mat.mat[2][3];
	float transformedW = vec.x * mat.mat[3][0] + vec.y * mat.mat[3][1] + vec.z * mat.mat[3][2] + w * mat.mat[3][3];
	if (transformedW != 1.0f)
	{
		transformedW = 1.0f / transformedW;
		retVal *= transformedW;
	}
	return retVal;
};
