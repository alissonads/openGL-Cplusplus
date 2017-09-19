#include "RT_PhongPMaterial.h"
#include "..\Mage\RT_Shader.h"

RT_PhongPMaterial::RT_PhongPMaterial(RT::Vec3f *_ambientColor, RT::Vec3f  *_diffuseColor,
									 RT::Vec3f *_specularColor, GLfloat _specularPower) :
	RT_SimpleMaterial("src/Resource/Phong/phongP"),
	ambientColor(_ambientColor), diffuseColor(_diffuseColor),
	specularColor(_specularColor), specularPower(_specularPower),
	shader(RT_Shader::LoadProgram({ "src/Resource/Phong/phongP" }))
{}

RT_PhongPMaterial::~RT_PhongPMaterial()
{
	delete ambientColor;
	ambientColor = nullptr;
	delete diffuseColor;
	diffuseColor = nullptr;
	delete specularColor;
	specularColor = nullptr;
}

RT::Vec3f *RT_PhongPMaterial::GetAmbientColor() const
{
	return ambientColor;
}

RT::Vec3f *RT_PhongPMaterial::GetDiffuseColor() const
{
	return diffuseColor;
}

RT::Vec3f *RT_PhongPMaterial::GetSpecularColor() const
{
	return specularColor;
}

GLfloat RT_PhongPMaterial::GetSpecularPower() const
{
	return specularPower;
}

void RT_PhongPMaterial::SetSpecularPower(float _specularPower)
{
	specularPower = _specularPower;
}

void RT_PhongPMaterial::Apply()
{
	shader->SetUniform("uAmbientMaterial", ambientColor)
		   .SetUniform("uDiffuseMaterial", diffuseColor)
		   .SetUniform("uSpecularMaterial", specularColor)
		   .SetUniform("uSpecularPower", specularPower);

	RT_SimpleMaterial::Apply();
}
