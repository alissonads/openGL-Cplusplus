#include "RT_NormalMapMaterial.h"
#include "..\Mage\RT_Shader.h"

RT_NormalMapMaterial::RT_NormalMapMaterial(RT::Vec3f *_ambientColor, RT::Vec3f  *_diffuseColor,
								           RT::Vec3f *_specularColor, GLfloat _specularPower) :
				  RT_SimpleMaterial("src/Resource/Phong/phongNM"),
				  ambientColor(_ambientColor), diffuseColor(_diffuseColor),
				  specularColor(_specularColor), specularPower(_specularPower)
{}

RT_NormalMapMaterial::~RT_NormalMapMaterial()
{
	delete ambientColor;
	ambientColor = nullptr;
	delete diffuseColor;
	diffuseColor = nullptr;
	delete specularColor;
	specularColor = nullptr;
}

RT::Vec3f *RT_NormalMapMaterial::GetAmbientColor() const
{
	return ambientColor;
}

RT::Vec3f *RT_NormalMapMaterial::GetDiffuseColor() const
{
	return diffuseColor;
}

RT::Vec3f *RT_NormalMapMaterial::GetSpecularColor() const
{
	return specularColor;
}

GLfloat RT_NormalMapMaterial::GetSpecularPower() const
{
	return specularPower;
}

RT_NormalMapMaterial &RT_NormalMapMaterial::SetNormalMap(RT_Texture *normalMap)
{
	return static_cast<RT_NormalMapMaterial&>(
					   RT_SimpleMaterial::
					   SetTexture("uNormalMap",
								   normalMap));
}

void RT_NormalMapMaterial::SetSpecularPower(float _specularPower)
{
	specularPower = _specularPower;
}

RT_NormalMapMaterial &RT_NormalMapMaterial::SetTexture(RT_Texture *texture)
{
	return static_cast<RT_NormalMapMaterial&>(
					   RT_SimpleMaterial::
					   SetTexture("uTexture",
								  texture));
}

void RT_NormalMapMaterial::Apply()
{
	shader->SetUniform("uAmbientMaterial", ambientColor)
		   .SetUniform("uDiffuseMaterial", diffuseColor)
		   .SetUniform("uSpecularMaterial", specularColor)
		   .SetUniform("uSpecularPower", specularPower);

	RT_SimpleMaterial::Apply();
}
