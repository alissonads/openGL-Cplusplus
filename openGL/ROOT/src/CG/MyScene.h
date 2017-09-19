#ifndef	 __MY_SCENE_H__
#define	 __MY_SCENE_H__

#include "..\Abstract\Scene.h"

class RT_Camera;
class RT_BasicMaterial;
class RT_DirectionalLight;
class RT_Mesh;
class RT_PhongMaterial;
class RT_Keyboard;

class MyScene : public Scene
{
private:
	RT_Camera *camera;
	RT_Mesh *mesh;
	RT_PhongMaterial *material;
	RT_DirectionalLight *light;
	RT_Keyboard *keys;

public:
	MyScene();
	~MyScene();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};

#endif //__MY_SCENE_H__
