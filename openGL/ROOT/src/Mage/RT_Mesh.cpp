#include "RT_Mesh.h"
#include "RT_ArrayBuffer.h"
#include "RT_IndexBuffer.h"
#include "..\Abstract\RT_Material.h"
#include "RT_Shader.h"
#include "RT_Uniform.h"
#include "RT_UniformType.h"
#include <sstream>

RT_Mesh::RT_Mesh() : 
		 indexBuffer(nullptr), 
		 id(0)
{
	glGenVertexArrays(1, &id);
}


RT_Mesh::~RT_Mesh()
{
	if (indexBuffer)
	{
		delete indexBuffer;
		indexBuffer = nullptr;
	}

	for (std::unordered_map<GLchar*,
							RT_ArrayBuffer*>::
		iterator i = attributes.begin();
		i != attributes.end(); i++)
	{
		delete i->second;
	}

	attributes.clear();

	for (std::unordered_map<GLchar*,
							RT_Uniform*>::
		iterator i = uniforms.begin();
		i != uniforms.end(); i++)
	{
		delete i->second;
	}

	uniforms.clear();

	glDeleteVertexArrays(1, &id);
}

void RT_Mesh::AddAttribute(GLchar *name, RT_ArrayBuffer *data)
{
	if (attributes.find(name) != attributes.end())
	{
		std::stringstream ss;
		ss << "Attribute already exists: "
		   << name << std::endl;

		throw std::out_of_range(ss.str());
	}
	if (!data)
	{
		std::stringstream ss;
		ss << "Data can't be null!" << std::endl;

		throw std::out_of_range(ss.str());
	}
	
	attributes[name] = data;
}

GLuint RT_Mesh::GetId() const
{
	return id;
}

RT_Mesh &RT_Mesh::SetIndexBuffer(RT_IndexBuffer *_indexBuffer)
{
	if (indexBuffer)
	{
		delete indexBuffer;
	}

	indexBuffer = _indexBuffer;
	return (*this);
}


RT_Mesh &RT_Mesh::SetUniform(GLchar *name, RT_BaseUniformType *type, void *value)
{
	if (!value)
	{
		delete uniforms[name];
		uniforms.erase(name);
	}
	else
	{
		if (uniforms.find(name) != uniforms.end())
			delete uniforms[name];
		
		uniforms[name] = new RT_Uniform(type, value);
	}

	return(*this);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, RT::Mat3f *matrix)
{
	return SetUniform(name, new Matrix3, matrix);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, RT::Mat4f *matrix)
{
	return SetUniform(name, new Matrix4, matrix);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, RT::Vec2f *vector)
{
	return SetUniform(name, new Vector2, vector);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, RT::Vec3f *vector)
{
	return SetUniform(name, new Vector3, vector);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, RT::Vec4f *vector)
{
	return SetUniform(name, new Vector4, vector);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, GLint value)
{
	return SetUniform(name, new Intenger, &value);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, GLfloat value)
{
	return SetUniform(name, new Float, &value);
}

RT_Mesh &RT_Mesh::SetUniform(GLchar *name, bool value)
{
	return SetUniform(name, new Boolean, &value);
}

RT_Mesh &RT_Mesh::Draw(RT_Material *material)
{
	if (!material || attributes.size() == 0)
	{
		return (*this);
	}

	RT_Shader *shader = material->GetShader();

	glBindVertexArray(id);

	shader->Bind();

	for (std::unordered_map<GLchar*,
						    RT_ArrayBuffer*>::
		iterator i = attributes.begin();
		i != attributes.end(); i++)
	{
		RT_ArrayBuffer *buffer = i->second;
		buffer->Bind();
		shader->SetAttribute(i->first, buffer);
		buffer->Unbind();
	}

	for (std::unordered_map<GLchar*,
							RT_Uniform*>::
		iterator i = uniforms.begin();
		i != uniforms.end(); i++)
	{
		i->second->Set(*shader, i->first);
	}

	material->Apply();

	if (!indexBuffer)
	{
		std::unordered_map<GLchar*,
						   RT_ArrayBuffer*>::
			iterator i = attributes.begin();

		i->second->Draw();
	}
	else
	{
		indexBuffer->Draw();
	}

	for (std::unordered_map<GLchar*,
							RT_ArrayBuffer*>::
		iterator i = attributes.begin();
		i != attributes.end(); i++)
	{
		shader->SetAttribute(i->first, nullptr);
	}

	//material->Apply();

	shader->Unbind();
	glBindVertexArray(NULL);

	return (*this);
}
