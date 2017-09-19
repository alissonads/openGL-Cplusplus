#ifndef	 __INDEX_BUFFER_H__
#define	 __INDEX_BUFFER_H__

#include <GL\glew.h>

class RT_IndexBuffer
{
private:
	GLuint id;
	int count;

public:
	RT_IndexBuffer(const GLint *data, 
				   const int sizeData);

	GLuint GetId() const;
	int GetCount() const;

	RT_IndexBuffer &Bind();
	RT_IndexBuffer &Unbind();

	void Draw();
};

#endif //__INDEX_BUFFER_H__
