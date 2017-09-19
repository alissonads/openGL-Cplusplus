#include "RT_SkyMaterial.h"
#include "..\Mage\RT_Shader.h"

RT_SkyMaterial::RT_SkyMaterial() :
				RT_SimpleMaterial("src/Resource/Phong/sky"),
				colorLow(RT::Vec3f(0.516f, 0.986f, 1.000f)),
				colorHigh(RT::Vec3f(0.133f, 0.353f, 0.725f)),
				cloudOffset1(RT::Vec2f(0.0055f, 0.0025f)),
				cloudOffset2(RT::Vec2f(0.0125f, 0.0050f)),
				time(0.0f)
{}

RT_SkyMaterial::~RT_SkyMaterial()
{
	/*delete colorLow;
	colorLow = nullptr;
	delete colorHigh;
	colorHigh = nullptr;
	delete cloudOffset1;
	cloudOffset1 = nullptr;
	delete cloudOffset2;
	cloudOffset2 = nullptr;*/
}

const RT::Vec3f &RT_SkyMaterial::GetColorLow() const
{
	return colorLow;
}

const RT::Vec3f &RT_SkyMaterial::GetColorHigh() const
{
	return colorHigh;
}

const RT::Vec2f &RT_SkyMaterial::GetCloudOffset1() const
{
	return cloudOffset1;
}

const RT::Vec2f &RT_SkyMaterial::GetCloudOffset2() const
{
	return cloudOffset2;
}

void RT_SkyMaterial::AddTime(float seconds)
{
	time += seconds;
}

RT_SkyMaterial &RT_SkyMaterial::SetCloud1(RT_Texture * texture)
{
	return static_cast<RT_SkyMaterial&>(
					   RT_SimpleMaterial::
					   SetTexture("uCloud0", 
								   texture));
}

RT_SkyMaterial &RT_SkyMaterial::SetCloud2(RT_Texture * texture)
{
	return static_cast<RT_SkyMaterial&>(
					   RT_SimpleMaterial::
					   SetTexture("uCloud1",
						           texture));
}

RT_SkyMaterial &RT_SkyMaterial::SetClouds(std::initializer_list<RT_Texture*> textures)
{
	int i = 0;
	for (RT_Texture *t : textures)
	{
		std::string aux = "uCloud" + std::to_string(i);
		SetTexture(const_cast<GLchar*>(aux.c_str()), t);
		i++;
	}

	return (*this);
}

void RT_SkyMaterial::Apply()
{
	shader->SetUniform("uColorLow", &colorLow)
		   .SetUniform("uColorHigh", &colorHigh)
		   .SetUniform("uCloudOffset0", &(cloudOffset1 * time))
		   .SetUniform("uCloudOffset1", &(cloudOffset1 * time));

	RT_SimpleMaterial::Apply();
}
