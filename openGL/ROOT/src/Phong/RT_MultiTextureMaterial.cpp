#include "RT_MultiTextureMaterial.h"
#include "..\Mage\RT_Shader.h"
#include <string>

RT_MultiTextureMaterial::RT_MultiTextureMaterial(RT::Vec3f *_ambientColor,
												 RT::Vec3f *_diffuseColor,
												 RT::Vec3f *_specularColor,
												 float _specularPower) :
						 RT_SimpleMaterial("src/Resource/Phong/phongMT"),
						 ambientColor(_ambientColor), diffuseColor(_diffuseColor),
						 specularColor(_specularColor), specularPower(_specularPower),
						 clippingPlane(new RT::Vec4f)
{}

RT_MultiTextureMaterial::~RT_MultiTextureMaterial()
{
	delete ambientColor;
	ambientColor = nullptr;
	delete diffuseColor;
	diffuseColor = nullptr;
	delete specularColor;
	specularColor = nullptr;

	if (clippingPlane)
	{
		delete clippingPlane;
		clippingPlane = nullptr;
	}
}

RT::Vec3f *RT_MultiTextureMaterial::GetAmbientColor() const
{
	return ambientColor;
}

RT::Vec3f *RT_MultiTextureMaterial::GetDiffuseColor() const
{
	return diffuseColor;
}

RT::Vec3f *RT_MultiTextureMaterial::GetSpecularColor() const
{
	return specularColor;
}

GLfloat RT_MultiTextureMaterial::GetSpecularPower() const
{
	return specularPower;
}

void RT_MultiTextureMaterial::SetSpecularPower(GLfloat _specularPower)
{
	specularPower = _specularPower;
}

RT_MultiTextureMaterial &RT_MultiTextureMaterial::SetTextures(std::initializer_list<RT_Texture*> textures)
{
	int i = 0;
	for (RT_Texture *t : textures)
	{
		std::string aux = "uTex" + std::to_string(i);
		SetTexture(const_cast<GLchar*>(aux.c_str()), t);
		i++;
	}

	return (*this);
}

RT_MultiTextureMaterial &RT_MultiTextureMaterial::SetTextures(std::vector<RT_Texture*> &textures)
{
	int size = textures.size();
	for (int i = 0; i < size; i++)
	{
		std::string aux = "uTex" + std::to_string(i);
		SetTexture(const_cast<GLchar*>(aux.c_str()), textures[i]);
	}

	return (*this);
}

void RT_MultiTextureMaterial::SetClippingPlane(RT::Vec4f *_clippingPlane)
{
	if (clippingPlane)
	{
		delete clippingPlane;
	}

	clippingPlane = _clippingPlane;
}

void RT_MultiTextureMaterial::Apply()
{
	shader->SetUniform("uAmbientMaterial" , ambientColor)
		   .SetUniform("uDiffuseMaterial" , diffuseColor)
		   .SetUniform("uSpecularMaterial", specularColor)
		   .SetUniform("uSpecularPower"   , specularPower)
		   .SetUniform("isClipping", clippingPlane != nullptr);
		   
	if (clippingPlane)
	{
		shader->SetUniform("uClippingPlane", clippingPlane);
	}

	RT_SimpleMaterial::Apply();
}
