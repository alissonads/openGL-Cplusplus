#include "Terreno.h"
#include "..\Mage\RT_Mesh.h"
#include "MeshFactory.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Camera.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_Texture.h"

Terreno::Terreno() :
	camera(nullptr),
	light(nullptr),
	mesh(nullptr),
	material(nullptr),
	keys(nullptr),
	anglex(0.0f),
	angley(0.0f)
{
}

Terreno::~Terreno()
{
	delete camera;
	delete light;
	delete material;
	delete mesh;
}

void Terreno::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_FACE, GL_LINE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera = new RT_Camera();
	camera->GetPosition()->Set(0.0f, 50.0f, 200.0f);

	mesh = MeshFactory::carregarTerreno("image/heights/volcano.png", 0.6f);
	material = new RT_BasicMaterial();
	keys = RT_Keyboard::GetInstance();
}

void Terreno::Update(float secs)
{
	if (keys->IsDown(GLFW_KEY_LEFT))
	{
		angley -= RT::Math::ToRadians(90.0) * secs;
	}
	if (keys->IsDown(GLFW_KEY_RIGHT))
	{
		angley += RT::Math::ToRadians(90.0) * secs;
	}
	if (keys->IsDown(GLFW_KEY_DOWN))
	{
		z -= 1 * secs;
		//anglex -= RT::Math::ToRadians(90.0) * secs;
	}
	if (keys->IsDown(GLFW_KEY_UP))
	{
		z += 1 * secs;
		//anglex += RT::Math::ToRadians(90.0) * secs; 
	}
}

void Terreno::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RT_Shader *shader = material->GetShader();
	shader->Bind()
		.SetUniform("uProjection", &camera->GetProjectionMatrix())
		.SetUniform("uView", &camera->GetViewMatrix())
		.SetUniform("uCameraPosition", camera->GetPosition());
	shader->Unbind();

	mesh->SetUniform("uWorld", 
		&RT::Mat4f().Translate(0, 0, z)
					.RotateY(angley)
					.RotateX(anglex))
		.Draw(material);
}

void Terreno::Deinit()
{
}
