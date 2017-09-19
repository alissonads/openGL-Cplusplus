#include "MyScene.h"
#include "..\Mage\RT_Mesh.h"
#include "MeshFactory.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Camera.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_Texture.h"

MyScene::MyScene() :
		 camera(nullptr),
		 light(nullptr),
		 mesh(nullptr),
		 material(nullptr),
		 keys(nullptr)
{}

MyScene::~MyScene()
{
	if (camera)
	{
		delete camera; 
		camera = nullptr;
	}
	if (light)
	{
		delete light;
		light = nullptr;
	}
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
	if (material)
	{
		delete material;
		material = nullptr;
	}
}

void MyScene::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_FACE, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	light = new RT_DirectionalLight(
				new RT::Vec3f(0.0f, 0.0f, -1.0f),
				new RT::Vec3f(0.02f, 0.02f, 0.02f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f));

	camera = new RT_Camera();
	camera->GetPosition()->z = 0.9f;

	mesh = MeshFactory::createSquare();
	material = new RT_PhongMaterial(
				new RT::Vec3f(1.0f, 1.0f, 1.0f),
				new RT::Vec3f(0.7f, 0.7f, 0.7f),
				new RT::Vec3f(0.5f, 0.5f, 0.5f),
				64.0f                           );
	material->SetTexture(new RT_Texture("image/textures/bricks_t.jpg"));
	keys = RT_Keyboard::GetInstance();
}

float dirx = 0, diry = 0;
void MyScene::Update(float secs)
{
	if (keys->IsDown(GLFW_KEY_A))
	{
		dirx += secs;
	}
	if (keys->IsDown(GLFW_KEY_D))
	{
		dirx -= secs;
	}
	if (keys->IsDown(GLFW_KEY_W))
	{
		diry -= secs;
	}
	if (keys->IsDown(GLFW_KEY_S))
	{
		diry += secs;
	}

	if (keys->IsPressed(GLFW_KEY_SPACE))
	{
		dirx = diry = 0;
	}

	light->GetDirection()->x = dirx;
	light->GetDirection()->y = diry;
}

void MyScene::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RT_Shader *shader = material->GetShader();
	shader->Bind()
		.SetUniform("uProjection", &camera->GetProjectionMatrix())
		.SetUniform("uView", &camera->GetViewMatrix())
		.SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f()).Draw(material);
}

void MyScene::Deinit()
{
}


