#include "NormalMapping.h"
#include "..\Mage\RT_Mesh.h"
#include "MeshFactory.h"
#include "..\Mage\RT_Shader.h"
#include "..\Phong\RT_PhongMaterial.h"
#include "..\Phong\RT_NormalMapMaterial.h"
#include "..\Phong\RT_DirectionalLight.h"
#include "..\System\RT_Camera.h"
#include "..\System\RT_Keyboard.h"
#include "..\Mage\RT_Texture.h"
#include "..\Mage\RT_FrameBuffer.h"
#include "..\Postfx\RT_PostFXMaterial.h"

NormalMapping::NormalMapping() :
	camera(nullptr),
	light(nullptr),
	mesh(nullptr),
	material(nullptr),
	materialNM(nullptr),
	keys(nullptr),
	normals(false)
{}

NormalMapping::~NormalMapping()
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
	if (materialNM)
	{
		delete materialNM;
		materialNM = nullptr;
	}
}

void NormalMapping::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_FACE, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	camera = new RT_Camera();
	camera->GetPosition()->z = 0.9f;
	keys = RT_Keyboard::GetInstance();

	light = new RT_DirectionalLight(
			new RT::Vec3f(0.0f, 0.0f, -1.0f),
			new RT::Vec3f(0.02f, 0.02f, 0.02f),
			new RT::Vec3f(1.0f, 1.0f, 1.0f),
			new RT::Vec3f(1.0f, 1.0f, 1.0f));


	mesh = MeshFactory::createSquareWithNormalMap();
	material = new RT_PhongMaterial(
			new RT::Vec3f(1.0f, 1.0f, 1.0f),
			new RT::Vec3f(0.7f, 0.7f, 0.7f),
			new RT::Vec3f(0.5f, 0.5f, 0.5f),
			64.0f);
	material->SetTexture(new RT_Texture("image/textures/stone_t.png"));

	materialNM = new RT_NormalMapMaterial(
			new RT::Vec3f(1.0f, 1.0f, 1.0f),
			new RT::Vec3f(0.7f, 0.7f, 0.7f),
			new RT::Vec3f(0.5f, 0.5f, 0.5f),
			64.0f
		);
	materialNM->SetTexture(new RT_Texture("image/textures/stone_t.png"));
	materialNM->SetNormalMap(new RT_Texture("image/normals/stone_n.png"));
}

void NormalMapping::Update(float secs)
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

	if (keys->IsPressed(GLFW_KEY_N))
	{
		normals = !normals;
	}

	light->GetDirection()->x = dirx;
	light->GetDirection()->y = diry;
}

void NormalMapping::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RT_Material *materialToDraw = nullptr;
	if (normals) 
		materialToDraw = materialNM;
	else 
		materialToDraw = material;

	RT_Shader *shader = materialToDraw->GetShader();
	shader->Bind()
		   .SetUniform("uProjection", &camera->GetProjectionMatrix())
		   .SetUniform("uView", &camera->GetViewMatrix())
		   .SetUniform("uCameraPosition", camera->GetPosition());
	light->Apply(*shader);
	shader->Unbind();

	mesh->SetUniform("uWorld", &RT::Mat4f()).Draw(materialToDraw);
}

void NormalMapping::Draw()
{
	DrawScene();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*RT_Shader *shader = postFX->GetShader();
	shader->Bind().Unbind();*/

}

void NormalMapping::Deinit()
{
}
