#ifndef	 __RT_MESH_H__
#define	 __RT_MESH_H__

#include <GL\glew.h>
#include <RTmath.h>
#include <unordered_map>
#include <string>

class RT_ArrayBuffer;
class RT_IndexBuffer;
class RT_BaseUniformType;
class RT_Uniform;
class RT_Material;

class RT_Mesh
{
	friend class RT_MeshBuilder;
private:
	GLuint id;
	RT_IndexBuffer *indexBuffer;

	std::unordered_map<GLchar*, RT_ArrayBuffer*> attributes;
	std::unordered_map<GLchar*, RT_Uniform*> uniforms;
	
	RT_Mesh();
	void AddAttribute(GLchar *name, RT_ArrayBuffer *data);
	RT_Mesh &SetUniform(GLchar *name, RT_BaseUniformType *type, void *value);

public:
	~RT_Mesh();

	GLuint GetId() const;
	RT_Mesh &SetIndexBuffer(RT_IndexBuffer *_indexBuffer);

	RT_Mesh &SetUniform(GLchar *name, RT::Mat3f *matrix);
	RT_Mesh &SetUniform(GLchar *name, RT::Mat4f *matrix);
	RT_Mesh &SetUniform(GLchar *name, RT::Vec2f *vector);
	RT_Mesh &SetUniform(GLchar *name, RT::Vec3f *vector);
	RT_Mesh &SetUniform(GLchar *name, RT::Vec4f *vector);
	RT_Mesh &SetUniform(GLchar *name, GLint value);
	RT_Mesh &SetUniform(GLchar *name, GLfloat value);
	RT_Mesh &SetUniform(GLchar *name, bool value);

	RT_Mesh &Draw(RT_Material *material);
};

#endif //__RT_MESH_H__
