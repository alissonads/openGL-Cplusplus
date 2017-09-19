#include "Plane.h"
#include "..\CG\MeshFactory.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Mage\RT_Mesh.h"
#include "..\Mage\RT_Shader.h"
#include "..\System\RT_Camera.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\System\RT_Keyboard.h"

Plane::Plane(RT::Vec3f *position, 
			 RT::Vec3f _angle,
			 float _width,
			 float _height) :
	   Form(position), 
	   width(_width), 
	   height(_height),
	   angle(_angle)
{}

void Plane::SetAngle(RT::Vec3f &_angle)
{
	angle.Set(_angle);
}

void Plane::Init()
{
	mesh = MeshFactory::createSquare(width, height);
}

void Plane::Update(float secs)
{
	/*if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_W))
	{
		angle.SetX(angle[0] - RTmath::ToRadians(90.0f * secs));
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_S))
	{
		angle.SetX(angle[0] + RTmath::ToRadians(90.0f * secs));
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_A))
	{
		angle.SetY(angle[1] - RTmath::ToRadians(90.0f * secs));
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_D))
	{
		angle.SetY(angle[1] + RTmath::ToRadians(90.0f * secs));
	}*/
}

void Plane::Draw(const RT_Camera *camera,
			     const RT_Light * light)
{
	RT_Shader *shader = material->GetShader();
	shader->Bind()
		.SetUniform("uProjection", &camera->GetProjectionMatrix())
		.SetUniform("uView", &camera->GetViewMatrix())
		.SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f().Translate(*position)
										   .RotateX(angle.x)
										   .RotateY(angle.y)
										   .RotateZ(angle.z))
		.Draw(material);
}
