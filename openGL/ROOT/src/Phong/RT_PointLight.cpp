#include "RT_PointLight.h"
#include "..\Mage\RT_Shader.h"

RT_PointLight::RT_PointLight(RT::Vec3f *_point,
							 RT::Vec3f *_ambient, 
							 RT::Vec3f *_diffuse, 
							 RT::Vec3f *_specular) :
	point(_point), ambient(_ambient),
	diffuse(_diffuse), specular(_specular)
{}

RT_PointLight::~RT_PointLight()
{
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
	if (point)
	{
		delete point;
		point = nullptr;
	}
	if (specular)
	{
		delete specular;
		specular = nullptr;
	}

}

RT::Vec3f *RT_PointLight::GetPoint() const
{
	return point;
}

RT::Vec3f *RT_PointLight::GetAmbient() const
{
	return ambient;
}

RT::Vec3f *RT_PointLight::GetDiffuse() const
{
	return diffuse;
}

RT::Vec3f *RT_PointLight::GetSpecular() const
{
	return specular;
}

void RT_PointLight::Apply(RT_Shader &shader) const
{
	shader.SetUniform("uPointLight", point);
	shader.SetUniform("uAmbientLight", ambient);
	shader.SetUniform("uDiffuseLight", diffuse);
	shader.SetUniform("uSpecularLight", specular);
	shader.SetUniform("uIsPoint", true);
}
