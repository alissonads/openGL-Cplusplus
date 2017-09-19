#ifndef	 __RT_PHONGP_MATERIAL_H__
#define	 __RT_PHONGP_MATERIAL_H__

#include "RT_SimpleMaterial.h"
#include <RTmath.h>
#include <unordered_map>

class RT_PhongPMaterial : public RT_SimpleMaterial
{
private:
	RT::Vec3f *ambientColor;
	RT::Vec3f *diffuseColor;
	RT::Vec3f *specularColor;
	GLfloat specularPower;

	RT_Shader *shader;
public:
	RT_PhongPMaterial(RT::Vec3f *_ambientColor =  new RT::Vec3f(1.0f, 1.0f, 1.0f),
					  RT::Vec3f  *_diffuseColor = new RT::Vec3f(1.0f, 1.0f, 1.0f),
					  RT::Vec3f *_specularColor = new RT::Vec3f(),
					  GLfloat _specularPower = 0.0f);
	~RT_PhongPMaterial();

	RT::Vec3f *GetAmbientColor() const;
	RT::Vec3f *GetDiffuseColor() const;
	RT::Vec3f *GetSpecularColor() const;
	GLfloat GetSpecularPower() const;

	void SetSpecularPower(float _specularPower);
	virtual void Apply();

};

#endif //__RT_PHONGP_MATERIAL_H__