#ifndef	 __CUBE_H__
#define	 __CUBE_H__

#include "Form.h"

class Cube : public Form
{
private:
	float width;
	float height;
	float depth;
	float anglex = 0, angley = 0;
public:
	Cube(RT::Vec3f *position, float _width = 1.0f,
		 float _height = 1.0f, float _depth = 1.0f);

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw(const RT_Camera *camera,
					  const RT_Light *light);
};

#endif //__CUBE_H__
