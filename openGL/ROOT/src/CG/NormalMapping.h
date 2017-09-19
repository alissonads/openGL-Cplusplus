#ifndef	 __NORMAL_MAPPING_H__
#define	 __NORMAL_MAPPING_H__

#include "..\Abstract\Scene.h"

class RT_Camera;
class RT_BasicMaterial;
class RT_DirectionalLight;
class RT_Mesh;
class RT_PhongMaterial;
class RT_Keyboard;
class RT_NormalMapMaterial;

class NormalMapping : public Scene
{
private:
	RT_Camera *camera;
	RT_DirectionalLight *light;

	RT_Keyboard *keys;

	RT_Mesh *mesh;
	RT_PhongMaterial *material;
	RT_NormalMapMaterial *materialNM;
	float dirx = 0, diry = 0;
	bool normals;

	void DrawScene();

public:
	NormalMapping();
	~NormalMapping();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};

#endif //__NORMAL_MAPPING_H__
