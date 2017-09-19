#pragma once

#include "..\Abstract\Scene.h"
#include <GL\glew.h>

class RT_Camera;
class RT_BasicMaterial;
class RT_DirectionalLight;
class RT_Mesh;
class RT_PhongMaterial;
class RT_Keyboard;

class Terreno : public Scene
{
private:
	RT_Camera *camera;
	RT_Mesh *mesh;
	RT_BasicMaterial *material;
	RT_DirectionalLight *light;
	RT_Keyboard *keys;

	float angley;
	float anglex;
	float z = 0.0f;
public:
	Terreno();
	~Terreno();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};