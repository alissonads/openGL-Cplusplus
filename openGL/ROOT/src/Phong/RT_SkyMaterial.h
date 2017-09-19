#ifndef	 __RT_SKY_MATERIAL__
#define	 __RT_SKY_MATERIAL__

#include "RT_SimpleMaterial.h"
#include <RTmath.h>

class RT_SkyMaterial : public RT_SimpleMaterial
{
private:
	RT::Vec3f colorLow;
	RT::Vec3f colorHigh;

	RT::Vec2f cloudOffset1;
	RT::Vec2f cloudOffset2;

	float time;
public:
	RT_SkyMaterial();
	~RT_SkyMaterial();

	const RT::Vec3f &GetColorLow() const;
	const RT::Vec3f &GetColorHigh() const;
	const RT::Vec2f &GetCloudOffset1() const;
	const RT::Vec2f &GetCloudOffset2() const;

	void AddTime(float seconds);
	RT_SkyMaterial &SetCloud1(RT_Texture *texture);
	RT_SkyMaterial &SetCloud2(RT_Texture *texture);
	RT_SkyMaterial &SetClouds(
					std::initializer_list<RT_Texture*> 
		                                      textures);

	virtual void Apply();
};

#endif //__RT_SKY_MATERIAL__
