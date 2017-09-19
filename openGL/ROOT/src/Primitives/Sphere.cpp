#include "Sphere.h"
#include "..\CG\MeshFactory.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Mage\RT_Mesh.h"
#include "..\Mage\RT_Shader.h"
#include "..\System\RT_Camera.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\Phong\RT_PhongPMaterial.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\System\RT_Keyboard.h"

Sphere::Sphere(RT::Vec3f *position, float _radius) :
		Form(position), radius(_radius)
{}

void Sphere::Init()
{
	mesh = MeshFactory::createSphere(60, 60, radius);
}

void Sphere::Update(float secs)
{
	/*if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_W))
	{
		anglex -= RTmath::ToRadians(90.0f * secs);
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_S))
	{
		anglex += RTmath::ToRadians(90.0f * secs);
	}*/
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_A))
	{
		angley -= RT::Math::ToRadians(90.0f * secs);
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_D))
	{
		angley += RT::Math::ToRadians(90.0f * secs);
	}
}

void Sphere::Draw(const RT_Camera *camera,
				  const RT_Light *light)
{
	RT_Shader *shader = material->GetShader();
	shader->Bind()
		.SetUniform("uProjection", &camera->GetProjectionMatrix())
		.SetUniform("uView", &camera->GetViewMatrix())
		.SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f().Translate(*position).RotateY(angley))
		.Draw(material);
}
