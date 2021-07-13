#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "math.h"
#include "constants.h"

class Camera
{
private:
	bool first;
	Vec3 eye;
	Vec3 target;
	Vec3 up;
	Vec3 angle;
	Vec2 Pos;
public:
	Camera();
	~Camera() {};
	Mat4 getView() { return Mat4::createLookAt(eye, eye + target, up); };
	Vec3 getEyePos() { return eye; }
	Vec3 getFrontPos() { return target; }
	void processInput(GLFWwindow* window, float frameTime);
	void mouseControls(GLFWwindow* window);
	void keyBoardControls(GLFWwindow* window, float frameTime);
};
#endif