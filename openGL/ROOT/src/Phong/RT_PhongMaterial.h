#ifndef	 __RT_PHONG_MATERIAL_H__
#define	 __RT_PHONG_MATERIAL_H__

#include "RT_SimpleMaterial.h"
#include <RTmath.h>
#include <unordered_map>

class RT_PhongMaterial : public RT_SimpleMaterial
{
private:
	RT::Vec3f *ambientColor;
	RT::Vec3f *diffuseColor;
	RT::Vec3f *specularColor;
	GLfloat specularPower;

public:
	RT_PhongMaterial(RT::Vec3f *_ambientColor  = new RT::Vec3f(1.0f, 1.0f, 1.0f), 
					 RT::Vec3f  *_diffuseColor = new RT::Vec3f(1.0f, 1.0f, 1.0f),
					 RT::Vec3f *_specularColor = new RT::Vec3f(), 
					 GLfloat _specularPower = 0.0f                         );
	~RT_PhongMaterial();

	RT::Vec3f *GetAmbientColor() const;
	RT::Vec3f *GetDiffuseColor() const;
	RT::Vec3f *GetSpecularColor() const;
	GLfloat GetSpecularPower() const;

	void SetSpecularPower(float _specularPower);
	RT_PhongMaterial &SetTexture(RT_Texture *texture);
	virtual void Apply();

};

#endif //__RT_PHONG_MATERIAL_H__