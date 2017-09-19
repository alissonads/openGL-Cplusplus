#include "RT_IndexBuffer.h"
#include <exception>

RT_IndexBuffer::RT_IndexBuffer(const GLint *data, 
							   const int sizeData) :
			    count(sizeData)
{
	if (!data)
	{
		throw std::exception("Data is NULL!\n");
	}

	glGenBuffers(1, &id);
	int byts = sizeData * sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, byts, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

GLuint RT_IndexBuffer::GetId() const
{
	return id;
}

int RT_IndexBuffer::GetCount() const
{
	return count;
}

RT_IndexBuffer &RT_IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	return (*this);
}

RT_IndexBuffer &RT_IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	return (*this);
}

void RT_IndexBuffer::Draw()
{
	Bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
	Unbind();
}
