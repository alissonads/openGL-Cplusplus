#ifndef	 __RT_MATERIAL_H__
#define	 __RT_MATERIAL_H__

class RT_Shader;

class RT_Material
{
public:
	virtual void SetShader(RT_Shader *_shader) = 0;
	virtual RT_Shader *GetShader() const = 0;
	virtual void Apply() = 0;
};

#endif //__RT_MATERIAL_H__
