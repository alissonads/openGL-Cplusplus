#ifndef	 __RT_TEXTURE_PARAMETERS_H__
#define	 __RT_TEXTURE_PARAMETERS_H__

#include <GL\glew.h>

class RT_TextureParameters
{
private:
	GLuint minFilter;
	GLuint magFilter;
	GLuint wrapS;
	GLuint wrapT;

public:
	RT_TextureParameters(GLuint _minFilter = GL_LINEAR_MIPMAP_LINEAR,
						 GLuint _magFilter = GL_LINEAR,
						 GLuint _wrapS = GL_REPEAT,
						 GLuint _wrapT = GL_REPEAT);

	GLuint GetMinFilter() const;
	GLuint GetMagFilter() const;
	GLuint GetWrapS() const;
	GLuint GetWrapT() const;
	bool IsMipMapped() const;

	void Apply(GLuint target) const;
};

#endif //__RT_TEXTURE_PARAMETERS_H__
