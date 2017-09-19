#include "Terrain.h"
#include "..\Mage\RT_Mesh.h"
#include "MeshFactory.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Camera.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_Texture.h"

Terrain::Terrain() :
		 camera(nullptr),
		 light(nullptr),
		 mesh(nullptr),
		 material(nullptr),
		 keys(nullptr)
{}

Terrain::~Terrain()
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

void Terrain::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_FACE, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera = new RT_Camera();
	camera->GetPosition()->Set(40.f, 20.f, 145.f);

	light = new RT_DirectionalLight(
				new RT::Vec3f(1.0f, -1.0f, -1.0f),
				new RT::Vec3f(0.1f, 0.1f, 0.1f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f));

	mesh = MeshFactory::loadTerrain("image/heights/river.png", 0.4f, 3);
	material = new RT_PhongMaterial(
				new RT::Vec3f(0.2f, 0.2f, 0.2f),
				new RT::Vec3f(0.9f, 0.9f, 0.9f),
				new RT::Vec3f(0.f, 0.f, 0.f),
				0.0f);

	material->SetTexture(new RT_Texture("image/textures/grass.png"));
	keys = RT_Keyboard::GetInstance();
}

void Terrain::Update(float secs)
{
}

void Terrain::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RT_Shader *shader = material->GetShader();
	shader->Bind()
		.SetUniform("uProjection", &camera->GetProjectionMatrix())
		.SetUniform("uView", &camera->GetViewMatrix())
		.SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f()
							    .RotateY(
									RT::Math::ToRadians(85.0)))
		.Draw(material);
}

void Terrain::Deinit()
{
}
