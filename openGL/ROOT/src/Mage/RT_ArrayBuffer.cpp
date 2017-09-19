#include "RT_ArrayBuffer.h"
#include <exception>

RT_ArrayBuffer::RT_ArrayBuffer(const GLfloat *data, 
							   const int	  sizeData,
							   const int	  _elementSize)
{
	if (_elementSize < 1)
	{
		throw std::exception("Element size < 1!\n");
	}
	if (!data)
	{
		throw std::exception("Data is NULL!\n");
	}

	glGenBuffers(1, &id);
	elementSize = _elementSize;
	elementCount = static_cast<int>(sizeData / 
									_elementSize);

	glBindBuffer(GL_ARRAY_BUFFER, id);
	int byts = sizeData * sizeof(GLfloat);
	glBufferData(GL_ARRAY_BUFFER, byts, 
				 data, GL_STATIC_DRAW  );
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

GLuint RT_ArrayBuffer::GetId() const
{
	return id;
}

int RT_ArrayBuffer::GetElementSize() const
{
	return elementSize;
}

int RT_ArrayBuffer::GetElementCont() const
{
	return elementCount;
}

int RT_ArrayBuffer::GetSize() const
{
	return elementSize * elementCount;
}

RT_ArrayBuffer &RT_ArrayBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	return (*this);
}

RT_ArrayBuffer &RT_ArrayBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	return (*this);
}

void RT_ArrayBuffer::Draw() const
{
	glDrawArrays(GL_TRIANGLES,
				 NULL,
				 GetElementCont());
}
