#include "RT_DirectionalLight.h"
#include "..\Mage\RT_Shader.h"

RT_DirectionalLight::RT_DirectionalLight(RT::Vec3f *_direction, RT::Vec3f *_ambient,
										 RT::Vec3f *_diffuse, RT::Vec3f *_specular) :
					 direction(_direction), ambient(_ambient),
					 diffuse(_diffuse), specular(_specular)
{}

RT_DirectionalLight::~RT_DirectionalLight()
{
	if (direction)
	{
		delete direction;
		direction = nullptr;
	}
	if (ambient)
	{
		delete ambient;
		ambient = nullptr;
	}
	if (diffuse)
	{
		delete diffuse;
		diffuse = nullptr;
	}
	if (specular)
	{
		delete specular;
		specular = nullptr;
	}
}

RT::Vec3f *RT_DirectionalLight::GetDirection() const
{
	return direction;
}

RT::Vec3f * RT_DirectionalLight::GetAmbient() const
{
	return ambient;
}

RT::Vec3f *RT_DirectionalLight::GetDiffuse() const
{
	return diffuse;
}

RT::Vec3f *RT_DirectionalLight::GetSpecular() const
{
	return specular;
}

void RT_DirectionalLight::Apply(RT_Shader &shader) const
{
	shader.SetUniform("uLightDir", &RT::vc3::Normalize(*direction));
	shader.SetUniform("uAmbientLight", ambient);
	shader.SetUniform("uDiffuseLight", diffuse);
	shader.SetUniform("uSpecularLight", specular);
	shader.SetUniform("uIsPoint", false);
}
