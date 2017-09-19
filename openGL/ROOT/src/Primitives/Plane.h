#ifndef	 __PLANE_H__
#define	 __PLANE_H__

#include <RTmath.h>
#include "Form.h"

class Plane : public Form
{
private:
	float width;
	float height;
	RT::Vec3f angle;

public:
	Plane(RT::Vec3f *position,
		  RT::Vec3f _angle,
		  float _width = 1, 
		  float _height = 1);

	void SetAngle(RT::Vec3f &_angle);

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw(const RT_Camera *camera,
					  const RT_Light *light);
};

#endif //__PLANE_H__
