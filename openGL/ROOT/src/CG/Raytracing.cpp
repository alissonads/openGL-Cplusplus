#include "Raytracing.h"
#include "Raytracing.h"
#include "..\System\RT_Camera.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\Phong\RT_PointLight.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Mage\RT_Mesh.h"
#include "..\Postfx\RT_PostFXMaterial.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "MeshFactory.h"
#include "..\Primitives\Form.h"
#include "..\Primitives\Sphere.h"
#include "..\Primitives\Cube.h"
#include "..\Primitives\Plane.h"
#include "..\Primitives\Sphere.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_DFMaterial.h"
#include <RTmath.h>

Raytracing::Raytracing() :
			camera(nullptr),
			light(nullptr),
			canvas(nullptr),
			fb(nullptr),
			postFX(nullptr),
			dfMaterial(nullptr),
			dfVp(nullptr),
			fFb(nullptr),
			dFb(nullptr)
{}

Raytracing::~Raytracing()
{
	delete camera;
	camera = nullptr;
	delete light;
	light = nullptr;
	delete canvas;
	canvas = nullptr;
	delete fb;
	fb = nullptr;
	delete postFX;
	postFX = nullptr;
	delete dfMaterial;
	dfMaterial = nullptr;
	delete dfVp;
	dfVp = nullptr;
	delete fFb;
	fFb = nullptr;
	delete dFb;
	dFb = nullptr;

	for (Form *obj : objects)
	{
		delete obj;
		obj = nullptr;
	}

	objects.clear();
}

void Raytracing::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_FACE, GL_LINE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera = new RT_Camera();
	camera->GetPosition()->Set(2.0f, -0.8f, 2.0f);
	//camera->GetPosition()->Set(1.5f, -0.8f, 2.0f);
	//camera->GetPosition()->Set(0.0f, 0.0f, 3.0f);
	light = new RT_PointLight(
				new RT::Vec3f(1.0f, 2.0f, -1.0f),
				new RT::Vec3f(0.1f, 0.1f, 0.1f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f),
				new RT::Vec3f(1.0f, 1.0f, 1.0f));

	CreateAmbient();

	dfVp = MeshFactory::createCanvas();
	dfMaterial = new RT_DFMaterial();

	dFb = RT_FrameBuffer::ForCurrentViewport();
	dfMaterial->SetD(dFb);

	fFb = RT_FrameBuffer::ForCurrentViewport();
	dfMaterial->SetF(fFb);

	//canvas = MeshFactory::createCanvas();
	//fb = RT_FrameBuffer::ForCurrentViewport();
	//postFX = RT_PostFXMaterial::DefaultPostFX("fxNone", fb);
}

void Raytracing::Update(float secs)
{
	for (Form *obj : objects)
	{
		obj->Update(secs);
	}
}

void Raytracing::Draw()
{
	//fb->Bind();
	DrawScene();
	//fb->Unbind();

	RT_Shader *shader = dfMaterial->GetShader();
	shader->Bind()
		.SetUniform("uSize", 20)
		.SetUniform("uPercentage", 1.f)
		.Unbind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	dfVp->Draw(dfMaterial);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//canvas->Draw(postFX);
}

void Raytracing::Deinit()
{
}

void Raytracing::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawNotFocus();
	DrawFocus();
}

void Raytracing::CreateRoom()
{
	//parede do fundo
	Form *obj = new Plane(new RT::Vec3f(0.0f, 0.0f, -2.5f),
						  RT::Vec3f(0, 0, 0), 6.0f, 2.0f);
	obj->SetMaterial(new RT_PhongMaterial(new RT::Vec3f(0.5f, 0.5f, 0.6f),
										  new RT::Vec3f(0.5f, 0.5f, 0.6f),
										  new RT::Vec3f(1.0f, 1.0f, 1.0f),
										  32.f));
	objects.push_back(obj);

	//chao
	obj = new Plane(new RT::Vec3f(0.0f, -1.0f, 0.0f),
					RT::Vec3f(RT::Math::ToRadians(-90.0f), 0, 0),
					6.0f, 5.0f);
	obj->SetMaterial(new RT_PhongMaterial(new RT::Vec3f(0.4f, 0.3f, 0.3f),
										  new RT::Vec3f(0.4f, 0.3f, 0.3f),
										  new RT::Vec3f(1.0f, 1.0f, 1.0f),
										  32.f));
	objects.push_back(obj);

	//parede da esquerda
	obj = new Plane(new RT::Vec3f(-3.0f, 0.0f, 0.0f),
					RT::Vec3f(0, RT::Math::ToRadians(90.0f), 0),
					5.0f, 2.0f);
	obj->SetMaterial(new RT_PhongMaterial(new RT::Vec3f(0.6f, 0.5f, 0.5f),
										  new RT::Vec3f(0.6f, 0.5f, 0.5f),
										  new RT::Vec3f(1.0f, 1.0f, 1.0f),
										  32.f));
	objects.push_back(obj);

	//luz esquerda
	obj = new Plane(new RT::Vec3f(-1.0f, 2.0f, -1.0f),
		RT::Vec3f(RT::Math::ToRadians(90.0f), 0, 0),
		1.0, 1.0f);
	obj->SetMaterial(new RT_BasicMaterial());
	objects.push_back(obj);

	//luz direita
	obj = new Plane(new RT::Vec3f(1.0f, 2.0f, -1.0f),
		RT::Vec3f(RT::Math::ToRadians(90.0f), 0, 0),
		1.0f, 1.0f);
	obj->SetMaterial(new RT_BasicMaterial());
	objects.push_back(obj);
}

void Raytracing::CreateObjects()
{
	//esfera da esquerda
	Form *obj = new Sphere(new RT::Vec3f(0.3f, -0.5f, 1.3f), 0.5f);
	obj->SetMaterial(new RT_PhongMaterial(new RT::Vec3f(0.7f, 0.7f, 1.0f),
										  new RT::Vec3f(0.7f, 0.7f, 1.0f),
										  new RT::Vec3f(1.0f, 1.0f, 1.0f),
										  0.f));
	objects.push_back(obj);

	//esfera da direita
	obj = new Sphere(new RT::Vec3f(0.7f, -0.2f, -0.5f), 0.5f);
	obj->SetMaterial(new RT_PhongMaterial(new RT::Vec3f(0.6f, 0.6f, 0.6f),
										  new RT::Vec3f(0.6f, 0.6f, 0.6f),
										  new RT::Vec3f(1.0f, 1.0f, 1.0f),
										  32.f));
	objects.push_back(obj);

	//cubo em baixo da segunda esfera
	obj = new Cube(new RT::Vec3f(0.7f, -0.9f, -0.5f), 0.3f, 0.2f, 0.3f);
	obj->SetMaterial(new RT_PhongMaterial(new RT::Vec3f(0.7f, 0.7f, 1.0f),
										  new RT::Vec3f(0.7f, 0.7f, 1.0f),
										  new RT::Vec3f(1.0f, 1.0f, 1.0f),
										  32.f));
	objects.push_back(obj);
}

void Raytracing::CreateAmbient()
{
	CreateRoom();
	CreateObjects();

	for (Form *obj : objects)
	{
		obj->Init();
	}
}

void Raytracing::DrawNotFocus()
{
	int size = objects.size();

	dFb->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < size; i++)
	{
		if (i == size - 3)
			continue;
		objects[i]->Draw(camera, light);
	}
	dFb->Unbind();
}

void Raytracing::DrawFocus()
{
	int size = objects.size();

	fFb->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	objects[size - 3]->Draw(camera, light);
	fFb->Unbind();
}
