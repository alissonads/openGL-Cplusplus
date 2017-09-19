#include "RT_SimpleMaterial.h"
#include "..\Mage\RT_Shader.h"
#include "..\Mage\RT_Texture.h"

RT_SimpleMaterial::RT_SimpleMaterial(GLchar *shader) :
				   shader(RT_Shader::LoadProgram(
									   { shader }))
{}

RT_SimpleMaterial::~RT_SimpleMaterial()
{
	delete shader;
	shader = nullptr;

	for (std::unordered_map<std::string,
						    RT_Texture*>
		::iterator i = textures.begin();
		i != textures.end(); i++)
	{
		delete i->second;
	}

	textures.clear();
}

RT_Material &RT_SimpleMaterial::SetTexture(GLchar *name, RT_Texture *texture)
{
	if (!texture)
	{
		if (textures.find(name) != textures.end())
		{
			delete textures[name];
			textures.erase(name);
		}
	}
	else
	{
		if (textures.find(name) != textures.end())
		{
			delete textures[name];
		}

		textures[name] = texture;
	}

	return (*this);
}

void RT_SimpleMaterial::SetShader(RT_Shader *_shader)
{
	if (!_shader)
	{
		throw std::exception("Shader cannot be NULL!\n");
	}
	if (shader)
	{
		delete shader;
	}

	shader = _shader;
}

RT_Shader *RT_SimpleMaterial::GetShader() const
{
	return shader;
}

void RT_SimpleMaterial::Apply()
{
	int texCount = 0;

	for (auto i = textures.begin();
		i != textures.end(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		i->second->Bind();
		shader->SetUniform(const_cast<GLchar*>(i->first.c_str()), texCount);
		texCount++;
	}

	shader->SetUniform("uUseText", textures.size() > 0);
}
