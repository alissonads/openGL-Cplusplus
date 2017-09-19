#ifndef	 __RT_SHADER_H__
#define	 __RT_SHADER_H__

#include <GL\glew.h>
#include <RTmath.h>
#include <string>
#include <vector>

class RT_ArrayBuffer;

class RT_Shader
{
private:
	GLuint id;

	RT_Shader(const GLuint _id);
	static std::string ReadInputStream(std::string &name);
	static GLuint LoadShader(std::string &name);
	static GLuint CompileShader(const GLuint type, 
							    const GLchar *name);
	static GLuint LinkProgram(std::vector<GLuint> &shaders);
	GLuint FindUniform(GLchar *name);

public:
	static RT_Shader *LoadProgram(std::initializer_list<std::string> shaders);
	GLuint GetId() const;

	RT_Shader &Bind();
	RT_Shader &Unbind();
	RT_Shader &SetAttribute(GLchar *name, RT_ArrayBuffer *buffer);

	RT_Shader &SetUniform(GLchar *name, RT::Mat3f *matrix);
	RT_Shader &SetUniform(GLchar *name, RT::Mat4f *matrix);
	RT_Shader &SetUniform(GLchar *name, RT::Vec2f *vector);
	RT_Shader &SetUniform(GLchar *name, RT::Vec3f *vector);
	RT_Shader &SetUniform(GLchar *name, RT::Vec4f *vector);
	RT_Shader &SetUniform(GLchar *name, GLint value);
	RT_Shader &SetUniform(GLchar *name, GLfloat value);
	RT_Shader &SetUniform(GLchar *name, bool value);
};

#endif //__RT_SHADER_H__
