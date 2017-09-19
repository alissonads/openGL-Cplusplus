#include "RT_MeshBuilder.h"
#include "RT_Mesh.h"
#include "RT_ArrayBuffer.h"
#include "RT_IndexBuffer.h"
#include "RT_Shader.h"

RT_MeshBuilder::RT_MeshBuilder() :
				mesh(new RT_Mesh())
{
	glBindVertexArray(mesh->GetId());
}

RT_MeshBuilder::~RT_MeshBuilder()
{
	/*delete mesh;
	mesh = nullptr;*/
}

RT_MeshBuilder &RT_MeshBuilder::AddBufferAttribute(GLchar *name, RT_ArrayBuffer *data)
{
	mesh->AddAttribute(name, data);
	return (*this);
}

RT_MeshBuilder &RT_MeshBuilder::AddBufferAttribute(GLchar *name, GLfloat *values, 
												   int sizeData, int elementSize)
{
	return AddBufferAttribute(name, new RT_ArrayBuffer(values, sizeData, elementSize));
}

RT_MeshBuilder &RT_MeshBuilder::AddFloatArrayAttribute(GLchar *name, int elementSize, 
													   std::initializer_list<GLfloat> values)
{
	std::vector<GLfloat> valueBuffer = values;
	return AddBufferAttribute(name, valueBuffer.data(), 
							  valueBuffer.size(), elementSize);
}

RT_MeshBuilder &RT_MeshBuilder::AddFloatArrayAttribute(GLchar *name, int elementSize, 
														std::vector<GLfloat>& values)
{
	return AddBufferAttribute(name, values.data(), values.size(), elementSize);
}

///Vector2f
RT_MeshBuilder &RT_MeshBuilder::AddVector2fAttribute(GLchar *name, RT::Vec2f *values, int size)
{
	std::vector<GLfloat> valueBuffer;

	for (int i = 0; i < size; i++)
	{
		valueBuffer.push_back(values[i].x);
		valueBuffer.push_back(values[i].y);
	}

	return AddFloatArrayAttribute(name, 2, valueBuffer);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector2fAttribute(GLchar *name, RT::Vec2f **values, int size)
{
	return AddVector2fAttribute(name, *values, size);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector2fAttribute(GLchar *name, std::vector<RT::Vec2f*> &values)
{
	return AddVector2fAttribute(name, values.data(), values.size());
}

RT_MeshBuilder &RT_MeshBuilder::AddVector2fAttribute(GLchar *name, std::vector<RT::Vec2f> *values)
{
	return AddVector2fAttribute(name, values->data(), values->size());
}


RT_MeshBuilder &RT_MeshBuilder::AddVector2fAttribute(GLchar *name, std::initializer_list<GLfloat> values)
{
	return AddFloatArrayAttribute(name, 2, values);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector2fAttribute(GLchar *name, GLfloat *values, int size)
{
	return AddBufferAttribute(name, values, size, 2);
}

///Vector3f
RT_MeshBuilder &RT_MeshBuilder::AddVector3fAttribute(GLchar *name, RT::Vec3f *values, int size)
{
	std::vector<GLfloat> valueBuffer;

	for (int i = 0; i < size; i++)
	{
		valueBuffer.push_back(values[i].x);
		valueBuffer.push_back(values[i].y);
		valueBuffer.push_back(values[i].z);
	}

	return AddFloatArrayAttribute(name, 3, valueBuffer);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector3fAttribute(GLchar *name, RT::Vec3f **values, int size)
{
	return AddVector3fAttribute(name, *values, size);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector3fAttribute(GLchar *name, std::vector<RT::Vec3f*> &values)
{
	return AddVector3fAttribute(name, values.data(), values.size());
}

RT_MeshBuilder &RT_MeshBuilder::AddVector3fAttribute(GLchar *name, std::vector<RT::Vec3f> *values)
{
	return AddVector3fAttribute(name, values->data(), values->size());
}

RT_MeshBuilder &RT_MeshBuilder::AddVector3fAttribute(GLchar *name, std::initializer_list<GLfloat> values)
{
	return AddFloatArrayAttribute(name, 3, values);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector3fAttribute(GLchar *name, GLfloat *values, int size)
{
	return AddBufferAttribute(name, values, size, 3);
}

///Vector4f
RT_MeshBuilder &RT_MeshBuilder::AddVector4fAttribute(GLchar *name, RT::Vec4f *values, int size)
{
	std::vector<GLfloat> valueBuffer;

	for (int i = 0; i < size; i++)
	{
		valueBuffer.push_back(values[i].x);
		valueBuffer.push_back(values[i].y);
		valueBuffer.push_back(values[i].z);
		valueBuffer.push_back(values[i].w);
	}

	return AddFloatArrayAttribute(name, 4, valueBuffer);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector4fAttribute(GLchar *name, RT::Vec4f **values, int size)
{
	return AddVector4fAttribute(name, *values, size);
}

RT_MeshBuilder &RT_MeshBuilder::AddVector4fAttribute(GLchar *name, std::vector<RT::Vec4f*> &values)
{
	return AddVector4fAttribute(name, values.data(), values.size());
}

RT_MeshBuilder &RT_MeshBuilder::AddVector4fAttribute(GLchar *name, std::vector<RT::Vec4f> *values)
{
	return AddVector4fAttribute(name, values->data(), values->size());
}

RT_MeshBuilder &RT_MeshBuilder::AddVector4fAttribute(GLchar *name, std::initializer_list<GLfloat> values)
{
	return AddFloatArrayAttribute(name, 4, values);
}

RT_MeshBuilder & RT_MeshBuilder::AddVector4fAttribute(GLchar *name, GLfloat *values, int size)
{
	return AddBufferAttribute(name, values, size, 4);
}

///IndexBuffer
RT_MeshBuilder &RT_MeshBuilder::SetIndexBuffer(RT_IndexBuffer *indexBuffer)
{
	mesh->SetIndexBuffer(indexBuffer);
	return (*this);
}

RT_MeshBuilder &RT_MeshBuilder::SetIndexBuffer(const GLint *data, const int size)
{
	return SetIndexBuffer(new RT_IndexBuffer(data, size));
}

RT_MeshBuilder &RT_MeshBuilder::SetIndexBuffer(std::vector<GLint> &data)
{
	return SetIndexBuffer(data.data(), data.size());
}

RT_MeshBuilder &RT_MeshBuilder::SetIndexBuffer(std::initializer_list<GLint> data)
{
	std::vector<GLint> buffer = data;
	return SetIndexBuffer(buffer);
}

///Mesh
RT_Mesh *RT_MeshBuilder::Create() const
{
	glBindVertexArray(NULL);
	return mesh;
}
