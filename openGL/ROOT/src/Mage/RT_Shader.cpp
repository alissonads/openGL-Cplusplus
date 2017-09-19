#include "RT_Shader.h"
#include "RT_ArrayBuffer.h"
#include <fstream>
#include <sstream>

RT_Shader::RT_Shader(const GLuint _id) :
		   id(_id)
{}

std::string RT_Shader::ReadInputStream(std::string &name)
{
	std::string code;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | 
						  std::ifstream::badbit   );

	try
	{
		shaderFile.open(name.c_str());

		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		code = shaderStream.str();
	}
	catch (std::ifstream::failure &e)
	{
		throw std::out_of_range(e.what());
	}

	return code;
}

GLuint RT_Shader::LoadShader(std::string &name)
{
	int index = name.find('.');
	std::string extension = (index == -1) ? "" : name.substr(index);

	GLuint type;

	if (extension == ".vert" || extension == ".vs")
	{
		type = GL_VERTEX_SHADER;
	}
	else if (extension == ".frag" || extension == ".fs")
	{
		type = GL_FRAGMENT_SHADER;
	}
	else if (extension == ".geom" || extension == ".gs")
	{
		type = GL_GEOMETRY_SHADER;
	}
	else
	{
		std::stringstream error;
		error << "Invalid shader name: " + name << std::endl;

		throw std::out_of_range(error.str());
	}

	std::string code = ReadInputStream(name);

	return CompileShader(type, code.c_str());
}

GLuint RT_Shader::CompileShader(const GLuint type, 
								const GLchar *name)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &name, nullptr);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	/*if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), 
						   nullptr, infoLog);
		throw std::exception(infoLog);
	}*/

	return shader;
}

GLuint RT_Shader::LinkProgram(std::vector<GLuint> &shaders)
{
	GLuint program = glCreateProgram();

	for (GLuint shader : shaders)
	{
		glAttachShader(program, shader);
	}

	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(program, GL_LINK_STATUS, &success);

	/*if (!success)
	{
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		std::stringstream error;
		error << "Unable to link shaders. "
		      << infoLog;
		throw std::out_of_range(error.str());
	}*/

	for (GLuint shader : shaders)
	{
		glDeleteShader(shader);
	}

	return program;
}

GLuint RT_Shader::FindUniform(GLchar *name)
{
	GLint uniform = glGetUniformLocation(id, name);

	/*if (uniform == -1)
	{
		std::cerr << "Uniform does not exists: " << name << std::endl;
	}*/

	return uniform;
}

RT_Shader *RT_Shader::LoadProgram(std::initializer_list<std::string> shaders)
{
	if (shaders.size() == 0)
	{
		throw std::exception("You must provide shader names!");
	}

	std::vector<std::string> s;

	if (shaders.size() == 1)
	{
		std::initializer_list<std::string>::iterator i = shaders.begin();
		s = { *i + ".vert", *i + ".frag" };
	}
	else
	{
		s = shaders;
	}

	std::vector<GLuint> ids;// = std::vector<GLuint>(s.size());

	for (std::string shader : s)
	{
		ids.push_back(LoadShader(shader));
	}

	return new RT_Shader(LinkProgram(ids));
}

GLuint RT_Shader::GetId() const
{
	return id;
}

RT_Shader &RT_Shader::Bind()
{
	glUseProgram(id);
	return (*this);
}

RT_Shader &RT_Shader::Unbind()
{
	glUseProgram(NULL);
	return (*this);
}

RT_Shader &RT_Shader::SetAttribute(GLchar *name, RT_ArrayBuffer *buffer)
{
	GLint attribute = glGetAttribLocation(id, name);

	/*if (attribute == -1)
	{
		std::stringstream ss;
		ss << "Attribute does not exists: "
		   << name.c_str() << std::endl;
		throw std::out_of_range(ss.str());
	}*/

	if (!buffer)
	{
		glDisableVertexAttribArray(attribute);
	}
	else
	{
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, buffer->GetElementSize(), 
							  GL_FLOAT, GL_FALSE, NULL, nullptr);
	}

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, RT::Mat3f *matrix)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	//GLfloat ptr[9];
	//matrix->SetPtr(ptr);

	glUniformMatrix3fv(uniform, 1, GL_FALSE, matrix->GetMatrix());

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, RT::Mat4f *matrix)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	//GLfloat ptr[16];
	//matrix->SetPtr(ptr);

	glUniformMatrix4fv(uniform, 1, GL_FALSE, matrix->GetMatrix());

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, RT::Vec2f *vector)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	glUniform2f(uniform, vector->x, vector->y);

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, RT::Vec3f *vector)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	glUniform3f(uniform, vector->x, 
			    vector->y, vector->z);

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, RT::Vec4f *vector)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	glUniform4f(uniform, vector->x,
		        vector->y, vector->z, 
				vector->w);

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, GLint value)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	glUniform1i(uniform, value);

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, GLfloat value)
{
	GLint uniform = FindUniform(name);
	if (uniform == -1) return (*this);

	glUniform1f(uniform, value);

	return (*this);
}

RT_Shader &RT_Shader::SetUniform(GLchar *name, bool value)
{
	return SetUniform(name, value ? GL_TRUE : GL_FALSE);
}
