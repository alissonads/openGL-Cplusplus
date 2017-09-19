#ifndef	 __RT_FRAME_BUFFER_H__
#define	 __RT_FRAME_BUFFER_H__

#include <GL\glew.h>

class RT_Texture;

class RT_FrameBuffer
{
private:
	GLuint id;
	GLuint idDepth;

	int width;
	int height;

	RT_Texture *texture;

public:
	RT_FrameBuffer(const int _width, 
				   const int _height);
	~RT_FrameBuffer();

	static RT_FrameBuffer *ForCurrentViewport();

	GLuint GetId() const;
	int GetWidth() const;
	int GetHeight() const;
	RT_Texture *GetTexture() const;

	RT_FrameBuffer &Bind();
	RT_FrameBuffer &Unbind();
};

#endif //__RT_FRAME_BUFFER_H__
