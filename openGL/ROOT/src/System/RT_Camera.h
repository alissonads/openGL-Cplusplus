#ifndef	 __RT_CAMERA_H__
#define	 __RT_CAMERA_H__

#include <RTmath.h>

class Window;

class RT_Camera
{
private:
	RT::Vec3f *position;
	RT::Vec3f *up;
	RT::Vec3f *target;
	float fov;
	float near;
	float far;

	float GetAspect() const;

public:
	RT_Camera();
	~RT_Camera();

	RT::Vec3f *GetPosition() const;
	RT::Vec3f *GetUp() const;
	RT::Vec3f *GetTarget() const;
	float GetFov() const;
	float GetNear() const;
	float GetFar() const;

	RT::Mat4f GetViewMatrix() const;
	RT::Mat4f GetProjectionMatrix() const;
	RT::Mat4f GetOrthoMatrix() const;

	void SetPosition(RT::Vec3f *position);;
	void SetUp(RT::Vec3f *up);
	void SetTarget(RT::Vec3f *target);
	void SetFov(const float fov);
	void SetNear(const float near);
	void SetFar(const float far);
};

#endif //__RT_CAMERA_H__