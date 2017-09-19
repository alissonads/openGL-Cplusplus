#ifndef	 __RT_MESH_BUILDER_H__
#define	 __RT_MESH_BUILDER_H__

#include <GL\glew.h>
#include <RTmath.h>
#include <vector>
#include <string>

class RT_Mesh;
class RT_ArrayBuffer;
class RT_IndexBuffer;

class RT_MeshBuilder
{
private:
	RT_Mesh *mesh;

public:
	RT_MeshBuilder();
	~RT_MeshBuilder();

	RT_MeshBuilder &AddBufferAttribute(GLchar *name, RT_ArrayBuffer *data);
	RT_MeshBuilder &AddBufferAttribute(GLchar *name, GLfloat *values, 
									   int sizeData, int elementSize);

	RT_MeshBuilder &AddFloatArrayAttribute(GLchar *name, int elementSize, 
										   std::initializer_list<GLfloat> values);
	RT_MeshBuilder &AddFloatArrayAttribute(GLchar *name, int elementSize,
										   std::vector<GLfloat> &values);

	///Vector2f
	RT_MeshBuilder &AddVector2fAttribute(GLchar *name, RT::Vec2f *values, int size);
	RT_MeshBuilder &AddVector2fAttribute(GLchar *name, RT::Vec2f **values, int size);
	RT_MeshBuilder &AddVector2fAttribute(GLchar *name, std::vector<RT::Vec2f*> &values);
	RT_MeshBuilder &AddVector2fAttribute(GLchar *name, std::vector<RT::Vec2f> *values);
	RT_MeshBuilder &AddVector2fAttribute(GLchar *name, std::initializer_list<GLfloat> values);
	RT_MeshBuilder &AddVector2fAttribute(GLchar *name, GLfloat *values, int size);

	///Vector3f
	RT_MeshBuilder &AddVector3fAttribute(GLchar *name, RT::Vec3f *values, int size);
	RT_MeshBuilder &AddVector3fAttribute(GLchar *name, RT::Vec3f **values, int size);
	RT_MeshBuilder &AddVector3fAttribute(GLchar *name, std::vector<RT::Vec3f*> &values);
	RT_MeshBuilder &AddVector3fAttribute(GLchar *name, std::vector<RT::Vec3f> *values);
	RT_MeshBuilder &AddVector3fAttribute(GLchar *name, std::initializer_list<GLfloat> values);
	RT_MeshBuilder &AddVector3fAttribute(GLchar *name, GLfloat *values, int size);

	///Vector4f
	RT_MeshBuilder &AddVector4fAttribute(GLchar *name, RT::Vec4f *values, int size);
	RT_MeshBuilder &AddVector4fAttribute(GLchar *name, RT::Vec4f **values, int size);
	RT_MeshBuilder &AddVector4fAttribute(GLchar *name, std::vector<RT::Vec4f*> &values);
	RT_MeshBuilder &AddVector4fAttribute(GLchar *name, std::vector<RT::Vec4f> *values);
	RT_MeshBuilder &AddVector4fAttribute(GLchar *name, std::initializer_list<GLfloat> values);
	RT_MeshBuilder &AddVector4fAttribute(GLchar *name, GLfloat *values, int size);

	//IndexBuffer
	RT_MeshBuilder &SetIndexBuffer(RT_IndexBuffer *indexBuffer);
	RT_MeshBuilder &SetIndexBuffer(const GLint *data, const int size);
	RT_MeshBuilder &SetIndexBuffer(std::vector<GLint> &data);
	RT_MeshBuilder &SetIndexBuffer(std::initializer_list<GLint> data);

	//Mesh
	RT_Mesh *Create() const;
};

#endif //__RT_MESH_BUILDER_H__
