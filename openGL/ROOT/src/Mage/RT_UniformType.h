#ifndef	 __RT_UNIFORM_TYPE_H__
#define	 __RT_UNIFORM_TYPE_H__

#include <GL\glew.h>
#include <RTmath.h>
#include <string>

#include "RT_Shader.h"

class RT_Shader;

class RT_BaseUniformType
{
public:
	virtual void Set(RT_Shader &shader, GLchar *name, void *value) = 0;
	virtual ~RT_BaseUniformType(){}
};

template<typename T>
class RT_UniformType : public RT_BaseUniformType
{
public:
	virtual void Set(RT_Shader &shader, GLchar *name, void *value);
};

typedef RT_UniformType<RT::Mat3f> Matrix3;
typedef RT_UniformType<RT::Mat4f> Matrix4;
typedef RT_UniformType<RT::Vec2f> Vector2;
typedef RT_UniformType<RT::Vec3f> Vector3;
typedef RT_UniformType<RT::Vec4f> Vector4;
typedef RT_UniformType<GLint> Intenger;
typedef RT_UniformType<GLfloat> Float;
typedef RT_UniformType<bool> Boolean;

#endif //__RT_UNIFORM_TYPE_H__

template<typename T>
inline void RT_UniformType<T>::Set(RT_Shader &shader, GLchar *name, void *value)
{
	shader.SetUniform(name, static_cast<T*>(value));
}