#include "MultiTexture.h"
#include "..\Mage\RT_Mesh.h"
#include "MeshFactory.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Phong\RT_MultiTextureMaterial.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Camera.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_Texture.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "..\Postfx\RT_PostFXMaterial.h"
#include "..\Phong\RT_SkyMaterial.h"
#include <GLFW\glfw3.h>

MultiTexture::MultiTexture() :
	camera(nullptr),
	light(nullptr),
	mesh(nullptr),
	material(nullptr),
	keys(nullptr),
	canvas(nullptr),
	fb(nullptr),
	postFX(nullptr),
	skyMesh(nullptr),
	skyMaterial(nullptr),
	lookX(0), lookY(0)
{}

MultiTexture::~MultiTexture()
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
	if (canvas)
	{
		delete canvas;
		canvas = nullptr;
	}
	if (fb)
	{
		delete fb;
		fb = nullptr;
	}
	if (postFX)
	{
		delete postFX;
		postFX = nullptr;
	}
	if (skyMesh)
	{
		delete skyMesh;
		skyMesh = nullptr;
	}
	if (skyMaterial)
	{
		delete skyMaterial;
		skyMaterial = nullptr;
	}
}

void MultiTexture::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_FACE, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera = new RT_Camera();
	camera->GetPosition()->Set(0.f, 20.f, 145.f);

	light = new RT_DirectionalLight(
				new RT::Vec3f(1.0f, -1.0f, -1.0f),
				new RT::Vec3f(0.1f, 0.1f, 0.1f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f));

	skyMesh = MeshFactory::createSkySphere(30, 30);
	skyMaterial = new RT_SkyMaterial();
	/*skyMaterial->SetCloud1(new RT_Texture("image/textures/cloud1.png"));
	skyMaterial->SetCloud2(new RT_Texture("image/textures/cloud2.png"));*/

	skyMaterial->SetClouds({ new RT_Texture("image/textures/cloud1.png"),
							 new RT_Texture("image/textures/cloud2.png") });

	mesh = MeshFactory::loadTerrain("image/heights/river.png", 0.4f, 3);

	material = new RT_MultiTextureMaterial(
					new RT::Vec3f(1.0f, 1.0f, 1.0f),//ambient
					new RT::Vec3f(0.9f, 0.9f, 0.9f),//diffuse
					new RT::Vec3f(0.0f, 0.0f, 0.0f),//specular
					0.0f);						 //specular power

	material->SetTextures(
				{ new RT_Texture("image/textures/sand.png"), 
				  new RT_Texture("image/textures/grass.png"),
				  new RT_Texture("image/textures/rock.png"),
				  new RT_Texture("image/textures/snow.png")
				});

	keys = RT_Keyboard::GetInstance();

	canvas = MeshFactory::createCanvas();
	fb = RT_FrameBuffer::ForCurrentViewport();
	postFX = RT_PostFXMaterial::DefaultPostFX("fxNone", fb);
}

void MultiTexture::Update(float secs)
{
	float speed = 1000 * secs;

	if (keys->IsDown(GLFW_KEY_LEFT_SHIFT))
	{
		speed *= 10;
	}

	if (keys->IsDown(GLFW_KEY_LEFT))
	{
		lookX -= speed * secs;
	}
	else if (keys->IsDown(GLFW_KEY_RIGHT))
	{
		lookX += speed * secs;
	}

	if (keys->IsDown(GLFW_KEY_UP))
	{
		lookY -= speed * secs;
	}
	else if (keys->IsDown(GLFW_KEY_DOWN))
	{
		lookY += speed * secs;
	}

	if (keys->IsDown(GLFW_KEY_SPACE))
	{
		lookY = lookY = 0;
	}

	camera->GetTarget()->Set(lookX, lookY, 0.0f);
	skyMaterial->AddTime(secs);
}

void MultiTexture::DrawScene()
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

	shader = skyMaterial->GetShader();
	shader->Bind()
				.SetUniform("uProjection", 
							&camera->GetProjectionMatrix())
				.SetUniform("uView", 
							&camera->GetViewMatrix())
		   .Unbind();

	skyMesh->SetUniform("uWorld", &RT::Mat4f().Scale(300))
		    .Draw(skyMaterial);
}

void MultiTexture::Draw()
{
	fb->Bind();
	DrawScene();
	fb->Unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	canvas->Draw(postFX);
}

void MultiTexture::Deinit()
{
}
