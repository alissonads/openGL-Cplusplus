#ifndef	 __POST_PROCESSING_H__
#define	 __POST_PROCESSING_H__

#include "..\Abstract\Scene.h"

class RT_Camera;
class RT_BasicMaterial;
class RT_DirectionalLight;
class RT_Mesh;
class RT_PhongMaterial;
class RT_Keyboard;
class RT_FrameBuffer;
class RT_PostFXMaterial;

class PostProcessing : public Scene
{
private:
	RT_Camera *camera;
	RT_DirectionalLight *light;

	RT_Keyboard *keys;

	RT_Mesh *mesh;
	RT_PhongMaterial *material;

	RT_Mesh *canvas;
	RT_FrameBuffer *fb;
	RT_PostFXMaterial *postFX;

	void DrawScene();

public:
	PostProcessing();
	~PostProcessing();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};

#endif //__POST_PROCESSING_H__
