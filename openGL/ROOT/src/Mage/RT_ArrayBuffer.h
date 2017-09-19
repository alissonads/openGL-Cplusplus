#ifndef	 __RT_ARRAY_BUFFER_H__
#define	 __RT_ARRAY_BUFFER_H__

#include <GL\glew.h>

class RT_ArrayBuffer
{
private:
	GLuint id;
	int elementSize;
	int elementCount;

public:
	RT_ArrayBuffer(const GLfloat *data, 
				   const int	  sizeData, 
				   const int	  _elementSize);

	GLuint GetId() const;
	int GetElementSize() const;
	int GetElementCont() const;
	int GetSize() const;

	RT_ArrayBuffer &Bind();
	RT_ArrayBuffer &Unbind();

	void Draw() const;
};

#endif //__RT_ARRAY_BUFFER_H__
