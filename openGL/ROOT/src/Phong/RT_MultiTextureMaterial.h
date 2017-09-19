#ifndef	 __RT_MULTI_TEXTURE_MATERIAL_H__
#define	 __RT_MULTI_TEXTURE_MATERIAL_H__

#include "RT_SimpleMaterial.h"
#include <RTmath.h>
#include <vector>

class RT_MultiTextureMaterial : public RT_SimpleMaterial
{
private:
	RT::Vec3f *ambientColor;
	RT::Vec3f *diffuseColor;
	RT::Vec3f *specularColor;
	RT::Vec4f *clippingPlane;
	GLfloat specularPower;

public:
	RT_MultiTextureMaterial(RT::Vec3f *_ambientMaterial  = new  RT::Vec3f(1.0f, 1.0f, 1.0f),
							RT::Vec3f *_diffuseMaterial  = new  RT::Vec3f(1.0f, 1.0f, 1.0f),
							RT::Vec3f *_specularMaterial = new  RT::Vec3f(),
							float   _specularPower    = 0.0f);
	~RT_MultiTextureMaterial();

	RT::Vec3f *GetAmbientColor() const;
	RT::Vec3f *GetDiffuseColor() const;
	RT::Vec3f *GetSpecularColor() const;
	GLfloat GetSpecularPower() const;

	void SetSpecularPower(GLfloat _specularPower);

	RT_MultiTextureMaterial &SetTextures(std::initializer_list<RT_Texture*> textures);
	RT_MultiTextureMaterial &SetTextures(std::vector<RT_Texture*> &textures);

	void SetClippingPlane(RT::Vec4f *clippingPlane);

	virtual void Apply();
};

#endif //__RT_MULTI_TEXTURE_MATERIAL_H__
