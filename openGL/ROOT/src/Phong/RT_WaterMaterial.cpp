#include "RT_WaterMaterial.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "..\Mage\RT_Shader.h"

RT_WaterMaterial::RT_WaterMaterial() :
				  RT_SimpleMaterial("src/Resource/Phong/water"),
				  offSet(RT::Vec2f(-0.01, -0.06))
{}

void RT_WaterMaterial::SetRefraction(RT_FrameBuffer *refractionFB)
{
	SetTexture("uRefraction", refractionFB->GetTexture());
}

void RT_WaterMaterial::SetReflection(RT_FrameBuffer *reflectionFB)
{
	SetTexture("uReflection", reflectionFB->GetTexture());
}

void RT_WaterMaterial::AddTime(float seconds)
{
	time += seconds;
}

void RT_WaterMaterial::Apply()
{
	shader->SetUniform("uOffSet", &(offSet * time));
	RT_SimpleMaterial::Apply();
}
