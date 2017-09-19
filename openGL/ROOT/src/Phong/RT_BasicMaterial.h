#ifndef	 __RT_BASIC_MATERIAL_H__
#define	 __RT_BASIC_MATERIAL_H__

#include "..\Abstract/RT_Material.h"
#include <GL\glew.h>
#include <string>

class RT_Shader;

class RT_BasicMaterial : public RT_Material
{
private:
	RT_Shader *shader;

public:
	RT_BasicMaterial(std::string _shader = "src/Resource/Basic/basic");
	~RT_BasicMaterial();

	virtual void SetShader(RT_Shader *_shader);
	virtual RT_Shader *GetShader() const;
	virtual void Apply();
};

#endif //__RT_BASIC_MATERIAL_H__
