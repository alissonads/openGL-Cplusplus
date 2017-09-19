#include "RT_TextureParameters.h"

RT_TextureParameters::RT_TextureParameters(GLuint _minFilter, 
										   GLuint _magFilter, 
										   GLuint _wrapS, 
										   GLuint _wrapT) :
					  minFilter(_minFilter), 
					  magFilter(_magFilter),
					  wrapS(_wrapS), 
					  wrapT(_wrapT)
{}

GLuint RT_TextureParameters::GetMinFilter() const
{
	return minFilter;
}

GLuint RT_TextureParameters::GetMagFilter() const
{
	return magFilter;
}

GLuint RT_TextureParameters::GetWrapS() const
{
	return wrapS;
}

GLuint RT_TextureParameters::GetWrapT() const
{
	return wrapT;
}

bool RT_TextureParameters::IsMipMapped() const
{
	return (minFilter == GL_NEAREST_MIPMAP_NEAREST ||
			minFilter == GL_NEAREST_MIPMAP_LINEAR  ||
			minFilter == GL_LINEAR_MIPMAP_LINEAR   || 
			minFilter == GL_LINEAR_MIPMAP_NEAREST    );
}

void RT_TextureParameters::Apply(GLuint target) const
{
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
}
