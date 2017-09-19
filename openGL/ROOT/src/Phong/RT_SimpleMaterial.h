#ifndef	 __RT_SIMPLE_MATERIAL_H__
#define	 __RT_SIMPLE_MATERIAL_H__

#include "..\Abstract\RT_Material.h"
#include <unordered_map>
#include <string>
#include <GL\glew.h>

class RT_Texture;
class RT_Shader;

class RT_SimpleMaterial : public RT_Material
{
protected:
	std::unordered_map<std::string, RT_Texture*> textures;
	RT_Shader *shader;

public:
	RT_SimpleMaterial(GLchar *shader);
	~RT_SimpleMaterial();

	RT_Material &SetTexture(GLchar     *name, 
							RT_Texture *texture);

	virtual void SetShader(RT_Shader *_shader);
	virtual RT_Shader *GetShader() const;
	virtual void Apply();
};

#endif //__RT_SIMPLE_MATERIAL_H__
