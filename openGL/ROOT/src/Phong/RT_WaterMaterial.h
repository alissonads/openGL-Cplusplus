#ifndef	 __RT_WATER_MATERIAL_H__
#define	 __RT_WATER_MATERIAL_H__

#include "RT_SimpleMaterial.h"
#include <RTmath.h>

class RT_FrameBuffer;

class RT_WaterMaterial : public RT_SimpleMaterial
{
private:
	RT::Vec2f offSet;
	float time;

public:
	RT_WaterMaterial();
	void SetRefraction(RT_FrameBuffer *refractionFB);
	void SetReflection(RT_FrameBuffer *reflectionFB);
	void AddTime(float seconds);
	virtual void Apply();
};

#endif //__RT_WATER_MATERIAL_H__
