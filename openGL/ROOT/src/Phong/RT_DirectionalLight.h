#ifndef	 __RT_DIRECTIONAL_LIGHT_H__
#define	 __RT_DIRECTIONAL_LIGHT_H__

#include <RTmath.h>
#include "..\Abstract\RT_Light.h"

class RT_DirectionalLight : public RT_Light
{
private:
	RT::Vec3f *direction;
	RT::Vec3f *ambient;
	RT::Vec3f *diffuse;
	RT::Vec3f *specular;

public:
	RT_DirectionalLight(RT::Vec3f *_direction, RT::Vec3f *_ambient,
						RT::Vec3f *_diffuse, RT::Vec3f *_specular);
	~RT_DirectionalLight();

	RT::Vec3f *GetDirection() const;
	RT::Vec3f *GetAmbient() const;
	RT::Vec3f *GetDiffuse() const;
	RT::Vec3f *GetSpecular() const;

	virtual void Apply(RT_Shader &shader) const;
};

#endif //__RT_DIRECTIONAL_LIGHT_H__
