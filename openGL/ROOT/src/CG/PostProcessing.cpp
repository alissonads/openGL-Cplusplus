#include "PostProcessing.h"
#include "..\Mage\RT_Mesh.h"
#include "MeshFactory.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_BasicMaterial.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Camera.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_Texture.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "..\Postfx\RT_PostFXMaterial.h"

PostProcessing::PostProcessing() :
	camera(nullptr),
	light(nullptr),
	mesh(nullptr),
	material(nullptr),
	keys(nullptr),
	canvas(nullptr),
	fb(nullptr),
	postFX(nullptr)
{}

PostProcessing::~PostProcessing()
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
}

void PostProcessing::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_FACE, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera = new RT_Camera();
	keys = RT_Keyboard::GetInstance();
	/*camera->GetPosition()->SetZ(0.9f);*/

	light = new RT_DirectionalLight(
			new RT::Vec3f(1.0f, -1.0f, -1.0f),
			new RT::Vec3f(0.02f, 0.02f, 0.02f),
			new RT::Vec3f(1.0f, 1.0f, 1.0f),
			new RT::Vec3f(1.0f, 1.0f, 1.0f));


	mesh = MeshFactory::createSquare();
	material = new RT_PhongMaterial(
			new RT::Vec3f(1.0f, 1.0f, 1.0f),
			new RT::Vec3f(0.7f, 0.7f, 0.7f),
			new RT::Vec3f(0.5f, 0.5f, 0.5f),
			2.0f);
	material->SetTexture(new RT_Texture("image/textures/stone_t.png"));

	canvas = MeshFactory::createCanvas();
	fb = RT_FrameBuffer::ForCurrentViewport();
	postFX = RT_PostFXMaterial::DefaultPostFX("fxBorders", fb);
}

void PostProcessing::Update(float secs)
{
}

void PostProcessing::DrawScene()
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

void PostProcessing::Draw()
{
	fb->Bind();
	DrawScene();
	fb->Unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*RT_Shader *shader = postFX->GetShader();
	shader->Bind().Unbind();*/

	canvas->Draw(postFX);
}

void PostProcessing::Deinit()
{
}
