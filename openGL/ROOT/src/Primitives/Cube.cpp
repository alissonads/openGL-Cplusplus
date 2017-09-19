#include "Cube.h"
#include "..\CG\MeshFactory.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Mage\RT_Mesh.h"
#include "..\Mage\RT_Shader.h"
#include "..\System\RT_Camera.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Keyboard.h"
#include <RTmath.h>

Cube::Cube(RT::Vec3f *position, float _width,
		   float _height, float _depth) :
	  Form(position), width(_width),
	  height(_height), depth(_depth)
{}

void Cube::Init()
{
	mesh = MeshFactory::createCube(width, height, depth);
}

void Cube::Update(float secs)
{
	/*if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_W))
	{
		position->z += 1.0f * secs;
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_S))
	{
		position->z -= 1.0f * secs;
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_A))
	{
		position->x -= 1.0f * secs;
	}
	if (RT_Keyboard::GetInstance()->IsDown(GLFW_KEY_D))
	{
		position->x += 1.0f * secs;
	}*/
}

void Cube::Draw(const RT_Camera *camera, 
				const RT_Light *light)
{
	RT_Shader *shader = material->GetShader();
	shader->Bind()
		   .SetUniform("uProjection", &camera->GetProjectionMatrix())
		   .SetUniform("uView", &camera->GetViewMatrix())
		   .SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f().Translate(*position))
		.Draw(material);
}
