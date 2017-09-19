#include "RT_PhongMaterial.h"
#include "..\Mage\RT_Shader.h"

RT_PhongMaterial::RT_PhongMaterial(RT::Vec3f *_ambientColor, RT::Vec3f  *_diffuseColor,
								   RT::Vec3f *_specularColor, GLfloat _specularPower) :
				  RT_SimpleMaterial("src/Resource/Phong/phong"),
				  ambientColor(_ambientColor), diffuseColor(_diffuseColor),
				  specularColor(_specularColor), specularPower(_specularPower)
{}

RT_PhongMaterial::~RT_PhongMaterial()
{
	delete ambientColor;
	ambientColor = nullptr;
	delete diffuseColor;
	diffuseColor = nullptr;
	delete specularColor;
	specularColor = nullptr;
}

RT::Vec3f *RT_PhongMaterial::GetAmbientColor() const
{
	return ambientColor;
}

RT::Vec3f *RT_PhongMaterial::GetDiffuseColor() const
{
	return diffuseColor;
}

RT::Vec3f *RT_PhongMaterial::GetSpecularColor() const
{
	return specularColor;
}

GLfloat RT_PhongMaterial::GetSpecularPower() const
{
	return specularPower;
}

void RT_PhongMaterial::SetSpecularPower(float _specularPower)
{
	specularPower = _specularPower;
}

RT_PhongMaterial &RT_PhongMaterial::SetTexture(RT_Texture *texture)
{
	return static_cast<RT_PhongMaterial&>(
					   RT_SimpleMaterial::
					   SetTexture("uTexture",
								  texture));
}

void RT_PhongMaterial::Apply()
{
	shader->SetUniform("uAmbientMaterial", ambientColor)
		   .SetUniform("uDiffuseMaterial", diffuseColor)
		   .SetUniform("uSpecularMaterial", specularColor)
		   .SetUniform("uSpecularPower", specularPower);

	RT_SimpleMaterial::Apply();
}
