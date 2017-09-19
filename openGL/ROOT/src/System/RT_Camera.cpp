#include "RT_Camera.h"
#include "Window.h"

RT_Camera::RT_Camera() :
	position(new RT::Vec3f(0.f, 0.f, 2.f)),
	up(new RT::Vec3f(0.f, 1.f, 0.f)),
	target(new RT::Vec3f(0.f, 0.f, 0.f)),
	near(0.1f), far(1000.0f),
	fov(RT::Math::ToRadians(60.f))
{}

RT_Camera::~RT_Camera()
{
	delete position;
	position = nullptr;
	delete up;
	up = nullptr;
	delete target;
	target = nullptr;
}

float RT_Camera::GetAspect() const
{
	int w, h;
	GLFWwindow *window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &w, &h);

	return static_cast<float>(w) /
		   static_cast<float>(h);
}

RT::Vec3f *RT_Camera::GetPosition() const
{
	return position;
}

RT::Vec3f *RT_Camera::GetUp() const
{
	return up;
}

RT::Vec3f *RT_Camera::GetTarget() const
{
	return target;
}

float RT_Camera::GetFov() const
{
	return fov;
}

float RT_Camera::GetNear() const
{
	return near;
}

float RT_Camera::GetFar() const
{
	return far;
}

RT::Mat4f RT_Camera::GetViewMatrix() const
{
	return RT::mt4::LookAt(*position,
					       *target,
					       *up);
}

RT::Mat4f RT_Camera::GetProjectionMatrix() const
{
	return RT::mt4::Perspective(fov, GetAspect(),
							    near, far);
}

RT::Mat4f RT_Camera::GetOrthoMatrix() const
{
	int w, h;
	GLFWwindow *window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &w, &h);

	return RT::mt4::Ortho(0,  w, h,
					      0, -1, 1);
}

void RT_Camera::SetPosition(RT::Vec3f *position)
{
	if (!position)
	{
		throw std::exception("The parameter is null\n");
	}

	*this->position = *position;
}

void RT_Camera::SetUp(RT::Vec3f *up)
{
	if (!up)
	{
		throw std::exception("The parameter is null\n");
	}

	*this->up = *up;
}

void RT_Camera::SetTarget(RT::Vec3f *target)
{
	if (!target)
	{
		throw std::exception("The parameter is null\n");
	}

	*this->target = *target;
}

void RT_Camera::SetFov(const float fov)
{
	this->fov = fov;
}

void RT_Camera::SetNear(const float near)
{
	this->near = near;
}

void RT_Camera::SetFar(const float far)
{
	this->far = far;
}

