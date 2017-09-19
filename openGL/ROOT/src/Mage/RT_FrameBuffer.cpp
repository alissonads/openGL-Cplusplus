#include "RT_FrameBuffer.h"
#include "RT_Texture.h"
#include "RT_TextureParameters.h"

RT_FrameBuffer::RT_FrameBuffer(const int _width, 
							   const int _height) :
			    width(_width), height(_height),
				texture(new RT_Texture(_width, _height, 
					new RT_TextureParameters(GL_LINEAR)))
{
	glGenRenderbuffers(1, &idDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, idDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, 
						  GL_DEPTH_COMPONENT16,
						  width, height        );
	glBindRenderbuffer(GL_RENDERBUFFER, NULL);

/*------------------------------------------------------------------*/
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, 
						   GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D, 
						   texture->GetId(),
						   NULL                  );
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,
							  GL_DEPTH_ATTACHMENT,
							  GL_RENDERBUFFER,
							  idDepth             );
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}

RT_FrameBuffer::~RT_FrameBuffer()
{
	delete texture;
	texture = nullptr;
}

RT_FrameBuffer *RT_FrameBuffer::ForCurrentViewport()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	return new RT_FrameBuffer(viewport[2], viewport[3]);
}

GLuint RT_FrameBuffer::GetId() const
{
	return id;
}

int RT_FrameBuffer::GetWidth() const
{
	return width;
}

int RT_FrameBuffer::GetHeight() const
{
	return height;
}

RT_Texture *RT_FrameBuffer::GetTexture() const
{
	return texture;
}

RT_FrameBuffer &RT_FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	return (*this);
}

RT_FrameBuffer &RT_FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	return (*this);
}
