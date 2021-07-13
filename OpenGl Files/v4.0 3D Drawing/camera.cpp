#include "camera.h"

Camera::Camera()
{
	first = true;
	Pos.Set(0.0f, 0.0f);
	angle.Set(0.0f, -PI / 2.0f, 0.0f);
	eye.Set(0.0f, 28.0f, 32.0f);
	target.Set(0.0f, 0.0f, -1.0f);
	up.Set(0.0f, 1.0f, 0.0f);
}
void Camera::processInput(GLFWwindow* window, float frameTime)
{
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		first = true;
	}
	mouseControls(window);
	keyBoardControls(window, frameTime);
}
void Camera::mouseControls(GLFWwindow* window)
{
	double xPos, yPos;
	float sensitivity = 0.250f;
	glfwGetCursorPos(window, &xPos, &yPos);
	if (first == false)
	{
		angle.y += ((xPos - Pos.x) * sensitivity * PI / 180.0f);
		angle.x += ((Pos.y - yPos) * sensitivity * PI / 180.0f);
		Pos.x = xPos;
		Pos.y = yPos;
		float angleTest = 89.0f * PI / 180.0f;
		if (angle.x > angleTest)
		{
			angle.x = angleTest;
		}
		if (angle.x < -angleTest)
		{
			angle.x = -angleTest;
		}
		target.x = cosf(angle.y) * cosf(angle.x);
		target.y = sin(angle.x);
		target.z = sinf(angle.y) * cosf(angle.x);
		target.Normalize();
	}
	else
	{
		Pos.x = xPos;
		Pos.y = yPos;
		first = false;
	}
}
void Camera::keyBoardControls(GLFWwindow* window, float frameTime)
{
	float cameraspeed = 24.0f;
	Vec3 vec3(cosf(angle.y), 0.0f, sinf(angle.y));
	// forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		eye += vec3 * cameraspeed * frameTime;
	}
	// back
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		eye -= vec3 * cameraspeed * frameTime;
	}
	vec3 = Vec3::Normalize(Vec3::Cross(target, up));
	// left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		eye -= vec3 * cameraspeed * frameTime;
	}
	// right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		eye += vec3 * cameraspeed * frameTime;
	}
}