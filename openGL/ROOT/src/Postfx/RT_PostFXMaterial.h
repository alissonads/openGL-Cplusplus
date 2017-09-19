#ifndef	 __RT_POST_FX_MATERIAL_H__
#define	 __RT_POST_FX_MATERIAL_H__

#include "..\Abstract\RT_Material.h"
#include <GL\glew.h>
#include <string>

class RT_FrameBuffer;

class RT_PostFXMaterial : public RT_Material
{
private:
	RT_FrameBuffer *frameBuffer;
	RT_Shader *shader;

public:
	RT_PostFXMaterial(std::string efferctName, 
				     RT_FrameBuffer *_frameBuffer);
	~RT_PostFXMaterial();

	static RT_PostFXMaterial *DefaultPostFX(std::string name,
							 RT_FrameBuffer *_frameBuffer);

	void SetFrameBuffer(RT_FrameBuffer *_frameBuffer);

	RT_FrameBuffer *GetFrameBuffer() const;

	virtual void SetShader(RT_Shader *_shader);
	virtual RT_Shader *GetShader() const;
	virtual void Apply();
};

#endif //__RT_POST_FX_MATERIAL_H__
