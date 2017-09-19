#ifndef	 __WATER_H__
#define	 __WATER_H__

#include "..\Abstract\Scene.h"
#include <RTmath.h>

class RT_Camera;
class RT_DirectionalLight;
class RT_Mesh;
class RT_MultiTextureMaterial;
class RT_Keyboard;
class RT_FrameBuffer;
class RT_PostFXMaterial;
class RT_SkyMaterial;
class RT_WaterMaterial;

class Water : public Scene
{
private:
	//dados da cena
	RT_Camera *camera;
	RT_DirectionalLight *light;
	RT_Keyboard *keys;

	//dados da malha
	RT_Mesh *mesh;
	RT_MultiTextureMaterial *material;

	//skydome
	RT_Mesh *skyMesh;
	RT_SkyMaterial *skyMaterial;

	//dados da agua
	RT_Mesh *water;
	RT_WaterMaterial *waterMaterial;
	RT_FrameBuffer *refractinFB;
	RT_FrameBuffer *reflectinFB;

	//canvas
	RT_Mesh *canvas;
	RT_FrameBuffer *fb;
	RT_PostFXMaterial *postFX;

	float lookX;
	float lookY;
	const float WATER_H;

	void DrawScene();
	void DrawTerrain();
	void DrawTerrain(RT::Mat4f &view);
	void DrawRefraction();
	void DrawReflection();
	void DrawWater();
	void DrawSky();
	void DrawSky(RT::Mat4f &view);
public:
	Water();
	~Water();

	RT::Mat4f GetReflexView();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};

#endif //__WATER_H__
