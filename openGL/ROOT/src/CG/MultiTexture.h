#ifndef	 __MULTI_TEXTURE_H__
#define	 __MULTI_TEXTURE_H__

#include "..\Abstract\Scene.h"

class RT_Camera;
class RT_BasicMaterial;
class RT_DirectionalLight;
class RT_Mesh;
class RT_MultiTextureMaterial;
class RT_Keyboard;
class RT_FrameBuffer;
class RT_PostFXMaterial;
class RT_SkyMaterial;

class MultiTexture : public Scene
{
private:
	RT_Camera *camera;
	RT_Mesh *mesh;
	RT_MultiTextureMaterial *material;
	RT_DirectionalLight *light;
	RT_Keyboard *keys;

	RT_Mesh *skyMesh;
	RT_SkyMaterial *skyMaterial;

	RT_Mesh *canvas;
	RT_FrameBuffer *fb;
	RT_PostFXMaterial *postFX;

	float lookX;
	float lookY;

	void DrawScene();
public:
	MultiTexture();
	~MultiTexture();

	virtual void Init();
	virtual void Update(float secs);
	virtual void Draw();
	virtual void Deinit();
};

#endif //__MULTI_TEXTURE_H__
