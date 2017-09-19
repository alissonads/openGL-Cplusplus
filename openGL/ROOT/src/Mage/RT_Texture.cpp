#include "RT_Texture.h"
#include <exception>
#include <SDL_image.h>
#include <iostream>

RT_Texture::RT_Texture(const int width, const int height,
					   RT_TextureParameters *_parameters) :
	parameters(_parameters)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, NULL, GL_RGBA,
				 width, height, NULL,
				 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	parameters->Apply(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

RT_Texture::RT_Texture(SDL_Surface *image, 
					   RT_TextureParameters *_parameters) :
			parameters(nullptr)
{
	try 
	{
		SetTexture(image, _parameters);
	}
	catch (std::exception &e)
	{
		throw std::exception(e.what());
	}
}

RT_Texture::RT_Texture(GLchar *imagePath, 
					   RT_TextureParameters *_parameters)
{
	try
	{
		SetTexture(IMG_Load(imagePath), _parameters);
	}
	catch (std::exception &e)
	{
		throw std::exception(e.what());
	}
}

RT_Texture::~RT_Texture()
{
	if (parameters)
	{
		delete parameters;
		parameters = nullptr;
	}
}

void RT_Texture::SetTexture(SDL_Surface *image, 
							RT_TextureParameters *_parameters)
{
	if (!image)
		throw std::exception("Surface can't be NULL");
	if (image->format->BytesPerPixel < 3)
		throw std::exception("Image must be RGB or RGBA!");
	if (!_parameters)
		throw std::exception("Parameters can't be NULL!");

	GLint format = (image->format->BytesPerPixel == 3)?
					GL_RGB : GL_RGBA;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, NULL, format, 
				 image->w, image->h, NULL, 
				 format, GL_UNSIGNED_BYTE, 
				 image->pixels                );

	parameters = _parameters;
	parameters->Apply(GL_TEXTURE_2D);

	if (parameters->IsMipMapped())
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	glBindTexture(GL_TEXTURE_2D, NULL);
	SDL_FreeSurface(image);
}

GLuint RT_Texture::GetId() const
{
	return id;
}

RT_TextureParameters *RT_Texture::GetParameters() const
{
	return parameters;
}

void RT_Texture::SetParameters(RT_TextureParameters * _parameters)
{
	if (!_parameters)
		throw std::exception("Class Texture: Parameters is null!");
	if (parameters)
		delete parameters;

	parameters = _parameters;

	Bind();
	parameters->Apply(GL_TEXTURE_2D);
	Unbind();
}

RT_Texture &RT_Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
	return (*this);
}

RT_Texture &RT_Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
	return (*this);
}

