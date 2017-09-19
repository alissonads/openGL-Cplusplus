#include "RT_DFMaterial.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "..\Mage\RT_Shader.h"
#include "..\Mage\RT_Texture.h"

RT_DFMaterial::RT_DFMaterial() :
	shader(RT_Shader::LoadProgram(
		{ "src/Resource/Phong/Desfoque" }))
{
}

RT_DFMaterial::~RT_DFMaterial()
{
	delete shader;
	shader = nullptr;

	textures.clear();
}

void RT_DFMaterial::SetD(RT_FrameBuffer *dFb)
{
	SetTexture("uTex0", dFb->GetTexture());
}

void RT_DFMaterial::SetF(RT_FrameBuffer *fFb)
{
	SetTexture("uTex1", fFb->GetTexture());
}

RT_Material &RT_DFMaterial::SetTexture(GLchar *name, RT_Texture *texture)
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

void RT_DFMaterial::SetShader(RT_Shader *_shader)
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

RT_Shader *RT_DFMaterial::GetShader() const
{
	return shader;
}

void RT_DFMaterial::Apply()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	shader->SetUniform("uWidth", viewport[2])
		   .SetUniform("uHeight", viewport[3]);

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
