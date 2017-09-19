#ifndef	 __RT_TEXTURE_H__
#define	 __RT_TEXTURE_H__

#include <GL\glew.h>
#include <SDL.h>
#include "RT_TextureParameters.h"


class RT_Texture
{
private:
	GLuint id;
	RT_TextureParameters *parameters;

	void SetTexture(SDL_Surface *image,
					RT_TextureParameters *_parameters);

public:
	RT_Texture(const int width, const int height,
			   RT_TextureParameters *_parameters);
	RT_Texture(SDL_Surface *image, 
			   RT_TextureParameters *_parameters = 
							new RT_TextureParameters());
	RT_Texture(GLchar *imagePath,
			   RT_TextureParameters *_parameters =
							new RT_TextureParameters());
	~RT_Texture();

	GLuint GetId() const;
	RT_TextureParameters *GetParameters() const;

	void SetParameters(RT_TextureParameters *_parameters);

	RT_Texture &Bind();
	RT_Texture &Unbind();
};

#endif //__RT_TEXTURE_H__
