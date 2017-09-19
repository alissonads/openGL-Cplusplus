#include "Water.h"
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
#include "..\Phong\RT_WaterMaterial.h"
#include <GLFW\glfw3.h>

Water::Water() :
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
	   water(nullptr),
	   waterMaterial(nullptr),
	   refractinFB(nullptr),
	   reflectinFB(nullptr),
	   lookX(0), lookY(0),
	   WATER_H(11.0f)
{}

Water::~Water()
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
	if (water)
	{
		delete water;
		water = nullptr;
	}
}

RT::Mat4f Water::GetReflexView()
{
	RT::Vec3f reflPos = RT::Vec3f(*camera->GetPosition());
	reflPos.y = (-reflPos[1] + WATER_H * 2);

	RT::Mat4f reflexView = RT::mt4::LookAt(
							       reflPos,
							       RT::Vec3f(lookX,
								             -lookY + 
									          WATER_H * 2,
								              0),
							       RT::Vec3f(0, 1, 0));
	return reflexView;
}

void Water::Init()
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

	//agua
	water = MeshFactory::createXZSquare(400, 300, WATER_H);
	waterMaterial = new RT_WaterMaterial();

	refractinFB = RT_FrameBuffer::ForCurrentViewport();
	waterMaterial->SetRefraction(refractinFB);

	reflectinFB = RT_FrameBuffer::ForCurrentViewport();
	waterMaterial->SetReflection(reflectinFB);

	waterMaterial->SetTexture("uWaterNormal",
						      new RT_Texture("image/normals/waterNormals.png"));

	keys = RT_Keyboard::GetInstance();

	//Carga do canvas para o PostFX
	canvas = MeshFactory::createCanvas();
	fb = RT_FrameBuffer::ForCurrentViewport();
	postFX = RT_PostFXMaterial::DefaultPostFX("fxNone", fb);
}

void Water::Update(float secs)
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
	waterMaterial->AddTime(secs);
}

void Water::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DrawSky();
	DrawTerrain();
	DrawWater();
}

void Water::DrawTerrain()
{
	DrawTerrain(camera->GetViewMatrix());
}

void Water::DrawTerrain(RT::Mat4f &view)
{
	RT_Shader *shader = material->GetShader();
	shader->Bind()
		   .SetUniform("uProjection", &camera->GetProjectionMatrix())
		   .SetUniform("uView", &view)
		   .SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f()
		                       .RotateY(
			                      RT::Math::
								      ToRadians(85.0)))
		 .Draw(material);
}

void Water::DrawRefraction()
{
	material->SetClippingPlane(new RT::Vec4f(0, -1, 0, WATER_H));
	
	refractinFB->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawTerrain();
	refractinFB->Unbind();

	material->SetClippingPlane(nullptr);
}

void Water::DrawReflection()
{
	RT::Mat4f reflexView = GetReflexView();
	material->SetClippingPlane(new RT::Vec4f(0, 1, 0, -WATER_H + 0.5f));

	reflectinFB->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSky(reflexView);
	DrawTerrain(reflexView);
	reflectinFB->Unbind();

	material->SetClippingPlane(nullptr);
}

void Water::DrawWater()
{
	RT_Shader *shader = waterMaterial->GetShader();
	shader->Bind()
		   .SetUniform("uProjection", &camera->GetProjectionMatrix())
		   .SetUniform("uView", &camera->GetViewMatrix())
		   .SetUniform("uReflexView", &GetReflexView())
		   .SetUniform("uCameraPosition", camera->GetPosition())
		   .SetUniform("uWaveHeight", 0.5f);
	shader->Unbind();

	water->SetUniform("uWorld", &RT::Mat4f())
		  .Draw(waterMaterial);
}

void Water::DrawSky()
{
	DrawSky(camera->GetViewMatrix());
}

void Water::DrawSky(RT::Mat4f &view)
{
	glDisable(GL_DEPTH_TEST);
	RT_Shader *shader = skyMaterial->GetShader();
	shader->Bind()
		   .SetUniform("uProjection",
			           &camera->GetProjectionMatrix())
		   .SetUniform("uView",
			           &view)
		   .Unbind();

	skyMesh->SetUniform("uWorld", &RT::Mat4f().Scale(300))
		    .Draw(skyMaterial);
	glEnable(GL_DEPTH_TEST);
}

void Water::Draw()
{
	DrawRefraction();
	DrawReflection();

	fb->Bind();
	DrawScene();
	fb->Unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	canvas->Draw(postFX);
}

void Water::Deinit()
{
}
