#ifndef	 __FORM_H__
#define	 __FORM_H__

#include "..\Abstract\GameObject.h"
#include <RTmath.h>

class RT_Mesh;
class RT_Material;
class RT_BasicMaterial;
class RT_Camera;

class Form : public GameObject
{
protected:
	RT_Mesh *mesh;
	RT_Material *material;
	RT::Vec3f *position;
	const RT_Camera *camera;

public:
	Form(RT::Vec3f *_position);
	~Form();

	RT_Mesh *GetMesh() const;
	RT_Material *GetMaterial() const;
	RT::Vec3f *GetPosition() const;
	void SetMaterial(RT_Material *_material);

	virtual void Init() = 0;
	virtual void Update(float secs) = 0;
	virtual void Draw(const RT_Camera *camera,
					  const RT_Light *light) = 0;
};

#endif //__FORM_H__
