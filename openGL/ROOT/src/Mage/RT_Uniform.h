#ifndef	 __RT_UNIFORM_H__
#define	 __RT_UNIFORM_H__

#include <string>
#include <GL\glew.h>
#include <RTmath.h>

class RT_Shader;
class RT_BaseUniformType;

class RT_Uniform
{
private:
	void *value;
	RT_BaseUniformType *type;

public:
	RT_Uniform(RT_BaseUniformType *_type, void *_value);
	~RT_Uniform();
	void Set(RT_Shader &shader, GLchar *name);

};

#endif //__RT_UNIFORM_H__
