#ifndef	 __SPHERE_H__
#define	 __SPHERE_H__

#include "Form.h"

class Sphere : public Form
{
private:
	float radius;
	float anglex = 0, angley = 0;
public:
	Sphere(RT::Vec3f *position, float _radius);

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw(const RT_Camera *camera,
		              const RT_Light *light);
};

#endif //__SPHERE_H__
