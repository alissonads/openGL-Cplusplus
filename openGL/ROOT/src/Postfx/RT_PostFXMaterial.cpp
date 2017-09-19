#include "RT_PostFXMaterial.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "..\Mage\RT_Shader.h"
#include "..\Mage\RT_Texture.h"

RT_PostFXMaterial::RT_PostFXMaterial(std::string efferctName,
									 RT_FrameBuffer *_frameBuffer) :
				   frameBuffer(_frameBuffer)
{
	std::string frag = efferctName + ".frag";
	std::string vert = "src/Resource/Postfx/fxVertexShader.vert";
	shader = RT_Shader::LoadProgram({ vert.c_str(),
									  frag.c_str() });
}

RT_PostFXMaterial::~RT_PostFXMaterial()
{
	/*delete frameBuffer;
	frameBuffer = nullptr;*/
	delete shader;
	shader = nullptr;
}

RT_PostFXMaterial *RT_PostFXMaterial::DefaultPostFX(std::string name,
													RT_FrameBuffer *_frameBuffer)
{
	return new RT_PostFXMaterial("src/Resource/Postfx/" + name, _frameBuffer);
}

void RT_PostFXMaterial::SetFrameBuffer(RT_FrameBuffer *_frameBuffer)
{
	if (!_frameBuffer)
	{
		throw std::exception("FrameBuffer cannot be NULL!\n");
	}
	if (frameBuffer)
	{
		delete frameBuffer;
	}

	frameBuffer = _frameBuffer;
}

RT_FrameBuffer *RT_PostFXMaterial::GetFrameBuffer() const
{
	return frameBuffer;
}

void RT_PostFXMaterial::SetShader(RT_Shader *_shader)
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

RT_Shader *RT_PostFXMaterial::GetShader() const
{
	return shader;
}

void RT_PostFXMaterial::Apply()
{
	shader->SetUniform("uWidth", frameBuffer->GetWidth());
	shader->SetUniform("uHeight", frameBuffer->GetHeight());

	glActiveTexture(GL_TEXTURE0);
	frameBuffer->GetTexture()->Bind();
	shader->SetUniform("uTexture", NULL);
}
