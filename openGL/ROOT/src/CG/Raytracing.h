#ifndef	 __RAY_TRACING_H__
#define	 __RAY_TRACING_H__

#include "..\Abstract\Scene.h"
#include <vector>

class RT_Camera;
class RT_DirectionalLight;
class RT_Keyboard;
class RT_FrameBuffer;
class RT_PostFXMaterial;
class Form;
class RT_Mesh;
class RT_Light;
class RT_DFMaterial;

class Raytracing : public Scene
{
private:
	std::vector<Form*> objects;
	RT_Camera *camera;
	RT_Light *light;
	RT_Keyboard *keys;

	RT_Mesh *dfVp;
	RT_FrameBuffer *dFb;
	RT_FrameBuffer *fFb;
	RT_DFMaterial *dfMaterial;

	//canvas
	RT_Mesh *canvas;
	RT_FrameBuffer *fb;
	RT_PostFXMaterial *postFX;

	void DrawScene();
	void CreateRoom();
	void CreateObjects();
	void CreateAmbient();

	void DrawNotFocus();
	void DrawFocus();

public:
	Raytracing();
	~Raytracing();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};

#endif //__RAY_TRACING_H__
