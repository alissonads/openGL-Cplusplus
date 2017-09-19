#include "Form.h"

Form::Form(RT::Vec3f *_position) :
	  position(_position),
	  mesh(nullptr),
	  material(nullptr)
{}

Form::~Form()
{
	if (material)
	{
		delete material;
		material = nullptr;
	}
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
	if (position)
	{
		delete position;
		position = nullptr;
	}
}

RT_Mesh *Form::GetMesh() const
{
	return mesh;
}

RT_Material *Form::GetMaterial() const
{
	return material;
}

RT::Vec3f *Form::GetPosition() const
{
	return position;
}

void Form::SetMaterial(RT_Material *_material)
{
	if (material)
		delete material;

	material = _material;
}
