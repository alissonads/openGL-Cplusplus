#ifndef  __RT_DF_MATERIAL_H__
#define	 __RT_DF_MATERIAL_H__

#include "..\Abstract\RT_Material.h"
#include <unordered_map>
#include <GL\glew.h>
#include <string>

class RT_FrameBuffer;
class RT_Texture;

class RT_DFMaterial : public RT_Material
{
private:
	std::unordered_map<std::string, RT_Texture*> textures;
	RT_Shader *shader;

public:
	RT_DFMaterial();
	~RT_DFMaterial();

	void SetD(RT_FrameBuffer *dFb);
	void SetF(RT_FrameBuffer *fFb);
	RT_Material &SetTexture(GLchar     *name,
							RT_Texture *texture);

	virtual void SetShader(RT_Shader *_shader);
	virtual RT_Shader *GetShader() const;
	virtual void Apply();
};

#endif //__RT_DF_MATERIAL_H__
