#include "RT_BasicMaterial.h"
#include "..\Mage\RT_Shader.h"

RT_BasicMaterial::RT_BasicMaterial(std::string _shader) :
	shader(RT_Shader::LoadProgram({ _shader }))
{
}

RT_BasicMaterial::~RT_BasicMaterial()
{
	delete shader;
	shader = nullptr;
}

void RT_BasicMaterial::SetShader(RT_Shader *_shader)
{
	if (!_shader)
	{
		throw std::exception("Shader cannot be NULL!");
	}
	if (shader)
	{
		delete shader;
	}

	shader = _shader;
}

RT_Shader *RT_BasicMaterial::GetShader() const
{
	return shader;
}

void RT_BasicMaterial::Apply()
{
}
