#ifndef	__RT_POINT_LIGHT_H__
#define __RT_POINT_LIGHT_H__

#include <RTmath.h>
#include "..\Abstract\RT_Light.h"

class RT_PointLight : public RT_Light
{
private:
	RT::Vec3f *point;
	RT::Vec3f *ambient;
	RT::Vec3f *diffuse;
	RT::Vec3f *specular;

public:
	RT_PointLight(RT::Vec3f *_point,
				  RT::Vec3f *_ambient,
				  RT::Vec3f *_diffuse,
				  RT::Vec3f *_specular);
	~RT_PointLight();

	RT::Vec3f *GetPoint() const;
	RT::Vec3f *GetAmbient() const;
	RT::Vec3f *GetDiffuse() const;
	RT::Vec3f *GetSpecular() const;

	virtual void Apply(RT_Shader &shader) const;
};

#endif //__RT_POINT_LIGHT_H__
