#include "RT_Uniform.h"
#include "RT_UniformType.h"

RT_Uniform::RT_Uniform(RT_BaseUniformType *_type, 
					   void *_value) :
			type(_type), value(_value)
{
}

RT_Uniform::~RT_Uniform()
{
	/*if (value)
	{
		delete value;
		value = nullptr;
	}*/
	if (type)
	{
		delete type;
		type = nullptr;
	}
}

void RT_Uniform::Set(RT_Shader &shader, GLchar *name)
{
	type->Set(shader, name, value);
}
