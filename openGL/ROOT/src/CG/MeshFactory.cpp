#include "MeshFactory.h"
#include "../Mage/RT_Mesh.h"
#include "../Mage/RT_MeshBuilder.h"
#include "Color.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>


RT_Mesh *MeshFactory::createSquare(float width, float height)
{
	float w = width / 2;
	float h = height / 2;

	return RT_MeshBuilder()
			.AddVector3fAttribute("aPosition", {
								 -w,  h, 0.0f,
								  w,  h, 0.0f,
								 -w, -h, 0.0f,
								  w, -h, 0.0f })
			.AddVector3fAttribute("aNormal", 
								  {0.0f, 0.0f, 1.0f,
								   0.0f, 0.0f, 1.0f,
								   0.0f, 0.0f, 1.0f,
								   0.0f, 0.0f, 1.0f})
			.AddVector2fAttribute("aTexCoord", 
								  {0.0f, 0.0f,
								   1.0f, 0.0f,
								   0.0f, 1.0f,
								   1.0f, 1.0f})
			.AddVector3fAttribute("aColor",
								  {1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f })
			.SetIndexBuffer({0, 2, 3,
							 0, 3, 1})
			.Create();
}

RT_Mesh *MeshFactory::createXZSquare(const float width, 
									 const float depth)
{
	float w = width / 2;
	float d = depth / 2;

	return RT_MeshBuilder()
		.AddVector3fAttribute("aPosition", {
			-w, 0.0f, -d,//0
			 w, 0.0f, -d,//1
			-w, 0.0f,  d,//2
			 w, 0.0f,  d})//3
		.AddVector3fAttribute("aNormal",
			{ 0.0f, 1.0f, 0.0f,
			  0.0f, 1.0f, 0.0f,
			  0.0f, 1.0f, 0.0f,
			  0.0f, 1.0f, 0.0f })
		.AddVector2fAttribute("aTexCoord",
			{ 0.0f, 0.0f,
			  1.0f, 0.0f,
			  0.0f, 1.0f,
			  1.0f, 1.0f })
		.AddVector3fAttribute("aColor",
			{ 0.5f, 0.5f, 1.0f,
			  0.5f, 0.5f, 1.0f,
			  0.5f, 0.5f, 1.0f,
			  0.5f, 0.5f, 1.0f })
		.SetIndexBuffer({ 0, 2, 3,
						  0, 3, 1 })
		.Create();
}

RT_Mesh *MeshFactory::createCube(float width,
							     float height,
								 float depth)
{
	return RT_MeshBuilder()
		.AddVector3fAttribute("aPosition",
			//Face próxima
			{-width,  height,  depth,  //0
			  width,  height,  depth,  //1
			 -width, -height,  depth,  //2
			  width, -height,  depth,  //3
								 //Face afastada
			 -width,  height, -depth,  //4
			  width,  height, -depth,  //5
			 -width, -height, -depth,  //6
			  width, -height, -depth,  //7
								 //Face superior
			 -width,  height,  depth,  //8
			  width,  height,  depth,  //9
			 -width,  height, -depth,  //10
			  width,  height, -depth,  //11
								 //Face inferior
			 -width, -height,  depth,  //12
			  width, -height,  depth,  //13
			 -width, -height, -depth,  //14
			  width, -height, -depth,  //15 
								 //Face direita
			  width, -height,  depth,  //16
			  width,  height,  depth,  //17
			  width, -height, -depth,  //18
			  width,  height, -depth,  //19
								 //Face esquerda
			  -width, -height,  depth,   //20
			  -width,  height,  depth,   //21
			  -width, -height, -depth,  //22
			  -width,  height, -depth })  //23
		.AddVector3fAttribute("aNormal",
			//Face próxima
			{ 0.0f,  0.0f,  1.0f,
			  0.0f,  0.0f,  1.0f,
			  0.0f,  0.0f,  1.0f,
			  0.0f,  0.0f,  1.0f,
			  //Face afastada
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  //Face superior
			  0.0f,  1.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,
			  //Face inferior
			  0.0f, -1.0f,  0.0f,
			  0.0f, -1.0f,  0.0f,
			  0.0f, -1.0f,  0.0f,
			  0.0f, -1.0f,  0.0f,
			  //Face direita
			  1.0f,  0.0f,  0.0f,
			  1.0f,  0.0f,  0.0f,
			  1.0f,  0.0f,  0.0f,
			  1.0f,  0.0f,  0.0f,
			  //Face esquerda
			  -1.0f,  0.0f,  0.0f,
			  -1.0f,  0.0f,  0.0f,
			  -1.0f,  0.0f,  0.0f,
			  -1.0f,  0.0f,  0.0f })
		.AddVector3fAttribute("aColor",
			{
				0.5f, 0.5f, 1.0f,
				0.5f, 0.5f, 1.0f,
				0.5f, 0.5f, 1.0f,
				0.5f, 0.5f, 1.0f,

				1.0f, 0.5f, 0.5f,
				1.0f, 0.5f, 0.5f,
				1.0f, 0.5f, 0.5f,
				1.0f, 0.5f, 0.5f,

				0.5f, 1.0f, 0.5f,
				0.5f, 1.0f, 0.5f,
				0.5f, 1.0f, 0.5f,
				0.5f, 1.0f, 0.5f,

				0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,

				1.0f, 0.5f, 1.0f,
				1.0f, 0.5f, 1.0f,
				1.0f, 0.5f, 1.0f,
				1.0f, 0.5f, 1.0f,

				1.0f, 1.0f, 0.5f,
				1.0f, 1.0f, 0.5f,
				1.0f, 1.0f, 0.5f,
				1.0f, 1.0f, 0.5f
			})
		.SetIndexBuffer(
			//Face próxima
			{ 0, 2, 3,
			  0, 3, 1,
			  //Face afastada
			  4, 7, 6,
			  4, 5, 7,
			  //Face superior
			  8, 11, 10,
			  8, 9, 11,
			  //Face inferior
			  12, 14, 15,
			  12, 15, 13,
			  //Face direita
			  16, 18, 19,
			  16, 19, 17,
			  //Face esquerda
			  20, 23, 22,
			  20, 21, 23 })
		.Create();
}

RT_Mesh *MeshFactory::createCanvas()
{
	return RT_MeshBuilder()
			.AddVector2fAttribute("aPosition", 
				{ -1.0f, 1.0f,
				   1.0f, 1.0f,
				  -1.0f, -1.0f,
				   1.0f, -1.0f })
			.AddVector2fAttribute("aTexCoord",
				{ 0.0f, 1.0f,
				  1.0f, 1.0f,
				  0.0f, 0.0f,
				  1.0f, 0.0f })
			.SetIndexBuffer(
				{ 0, 2, 3,
				  0, 3, 1 })
			.Create();
}

float MeshFactory::CalcLinear(float min, float max, float value, bool inverse)
{
	float range = max - min;
	float result = (value - min) / range;
	result = (result < 0) ? 0 : (result > 1) ? 1 : result;

	return (inverse)? 1 - result : result;
}

float MeshFactory::CalcPiramid(float min, float max, float value)
{
	float mid = (min + max) / 2.0f;

	return (value <= mid)?
			CalcLinear(min, mid, value, false) :
			CalcLinear(min, max, value, true);
}

RT_Mesh *MeshFactory::loadTerrain(GLchar *name, 
								  float scale, 
								  int texRepeat)
{
	SDL_Surface *image = IMG_Load(name);

	if (!image)
	{
		throw std::exception("I wander when carrying the image");
	}

	int width = image->w;
	int depth = image->h;
	float hw = width / 2.0f;
	float hd = depth / 2.0f;

	int maxHeight = 0;
	std::vector<RT::Vec3f> positions;

	for (int z = 0; z < depth; z++)
	{
		for (int x = 0; x < width; x++)
		{
			int tone1 = Color(image, z, x).GetRed();
			int tone2 = (x > 1) ? Color(image, z, x-1).GetRed() : tone1;
			int tone3 = (z > 1) ? Color(image, z-1, x).GetRed() : tone1;

			float h = (tone1 + tone2 + tone3) / 3.0f * scale;
			positions.push_back(RT::Vec3f(x - hw,
									      h,
									      z - hd ));
			
			maxHeight = (maxHeight < tone1) ? tone1 : maxHeight;
		}
	}

	std::vector<GLint> indices;

	for (int z = 0; z < depth - 1; z++)
	{
		for (int x = 0; x < width - 1; x++)
		{
			int zero = x + z * width;
			int one = (x + 1) + z * width;
			int two = x + (z + 1) * width;
			int three = (x + 1) + (z + 1) * width;

			indices.push_back(zero);
			indices.push_back(three);
			indices.push_back(one);

			indices.push_back(zero);
			indices.push_back(two);
			indices.push_back(three);
		}
	}
	
	std::vector<RT::Vec3f> normals;
	int size = positions.size();
	for (int i = 0; i < size; i++)
	{
		normals.push_back(RT::Vec3f());
	}

	size = indices.size();
	for (int i = 0; i < size; i+=3)
	{
		int i1 = indices[i];
		int i2 = indices[i + 1];
		int i3 = indices[i + 2];

		//RTvec3 v1 = positions[i1];
		//RTvec3 v2 = positions[i2];
		//RTvec3 v3 = positions[i3];

		RT::Vec3f side1 = positions[i2] - positions[i1];
		RT::Vec3f side2 = positions[i3] - positions[i1];
		//RTvec3 normal = vc3::CrossProduct(&side1, &side2);
		RT::Vec3f normal(side1);
		normal.Cross(side2);

		normals[i1] += normal;
		normals[i2] += normal;
		normals[i3] += normal;
	}

	for (RT::Vec3f &normal : normals)
	{
		normal.Normalize();
	}

	float tx = 1.0f / image->w * texRepeat;
	float ty = 1.0f / image->h * texRepeat;

	std::vector<RT::Vec2f> texCoord;
	for (int z = 0; z < image->h - 1; z++)
		for (int x = 0; x < image->w - 1; x++)
			texCoord.push_back(RT::Vec2f(x * tx, z * ty));
	
	//pesos
	std::vector<RT::Vec4f> texWeights;
	for (int z = 0; z < depth; z++)
	{
		for (int x = 0; x < width; x++)
		{
			int tone = Color(image, z, x).GetRed();
			float h = static_cast<float>(tone) / maxHeight;

			texWeights.push_back(RT::Vec4f(
						CalcLinear(0.75f, 1.00f, h, false),
						CalcPiramid(0.50f, 0.80f, h),
						CalcPiramid(0.15f, 0.60f, h),
						CalcLinear(0.00f, 0.16f, h, true)));
		}
	}

	SDL_FreeSurface(image);
	image = nullptr;

	return RT_MeshBuilder()
			.AddVector3fAttribute("aPosition", &positions)
			.AddVector3fAttribute("aNormal", &normals)
			.AddVector2fAttribute("aTexCoord", &texCoord)
			.AddVector4fAttribute("aTexWeight", &texWeights)
			.SetIndexBuffer(indices)
			.Create();
}

RT_Mesh *MeshFactory::createSquareWithNormalMap()
{
	std::vector<RT::Vec3f> positions;
	positions.push_back(RT::Vec3f(-0.5f,  0.5f, 0.0f));
	positions.push_back(RT::Vec3f( 0.5f,  0.5f, 0.0f));
	positions.push_back(RT::Vec3f(-0.5f, -0.5f, 0.0f));
	positions.push_back(RT::Vec3f( 0.5f, -0.5f, 0.0f));

	std::vector<GLint> indices = {
				0, 2, 3,
				0, 3, 1
			};

	std::vector<RT::Vec2f> texCoord;
	texCoord.push_back(RT::Vec2f(0.0f, 0.0f));
	texCoord.push_back(RT::Vec2f(1.0f, 0.0f));
	texCoord.push_back(RT::Vec2f(0.0f, 1.0f));
	texCoord.push_back(RT::Vec2f(1.0f, 1.0f));

	std::vector<RT::Vec3f> normals;
	std::vector<RT::Vec3f> tangents;

	int size = positions.size();
	for (int i = 0; i < size; i++)
	{
		normals.push_back(RT::Vec3f());
		tangents.push_back(RT::Vec3f());
	}

	size = indices.size();
	for (int i = 0; i < size; i+=3)
	{
		int i1 = indices[i];
		int i2 = indices[i+1];
		int i3 = indices[i+2];

		RT::Vec3f v1 = positions[i1];
		RT::Vec3f v2 = positions[i2];
		RT::Vec3f v3 = positions[i3];

		RT::Vec3f side1 = v2 - v1;
		RT::Vec3f side2 = v3 - v1;

		RT::Vec2f texSide1 = texCoord[1] - texCoord[0];
		RT::Vec2f texSide2 = texCoord[2] - texCoord[0];
		
		float f = 1.0f / (texSide1[0] * texSide2[1] -
						  texSide2[0] * texSide1[1]  );

		RT::Vec3f tangent = RT::vc3::Normalize(
							 RT::Vec3f(f * (texSide2[1] * side1[0] -
										  texSide1[1] * side2[0]),
									 f * (texSide2[1] * side1[1] -
										  texSide1[1] * side2[1]),
									 f * (texSide2[1] * side1[2] - 
										  texSide1[1] * side2[2])));

		tangents[i1] += tangent;
		tangents[i2] += tangent;
		tangents[i3] += tangent;

		RT::Vec3f normal = RT::vc3::Cross(side1, side2);
		
		normals[i1] += normal;
		normals[i2] += normal;
		normals[i3] += normal;
	}

	size = normals.size();
	for (int i = 0; i < size; i++)
	{
		normals[i].Normalize();
		tangents[i].Normalize();
	}

	return RT_MeshBuilder()
			.AddVector3fAttribute("aPosition", &positions)
			.AddVector2fAttribute("aTexCoord", &texCoord)
			.AddVector3fAttribute("aNormal", &normals)
			.AddVector3fAttribute("aTangent", &tangents)
			.SetIndexBuffer(indices)
			.Create();
}

RT_Mesh *MeshFactory::createXZSquare(const int width,
									 const int depth,
									 const float y)
{
	float w = (width - 1) / 2.0f;
	float d = (depth - 1) / 2.0f;
	return RT_MeshBuilder()
			.AddVector3fAttribute("aPosition",
				{ 
				  -w, y, -d,
				   w, y, -d,
				  -w, y,  d,
				   w, y,  d
			    })
			.AddVector2fAttribute("aTexCoord",
				{ 
				  0.0f, 0.0f,
				  1.0f, 0.0f,
				  0.0f, 1.0f,
				  1.0f, 1.0f 
				})
			.AddVector3fAttribute("aNormal", 
				{
				  0.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f,
				  0.0f, 1.0f, 0.0f
				})
			.SetIndexBuffer(
				{ 
				  2, 1, 0,
				  3, 1, 2 
				})
			.Create();
}

RT_Mesh *MeshFactory::createSkySphere(const int slices, 
									  const int stacks)
{
	std::vector<RT::Vec3f> vertices;
	std::vector<RT::Vec2f> texCoords;

	for (int slice = 0; slice <= slices; slice++)
	{
		double theta = slice * RT_PI / slices;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (int stack = 0; stack <= stacks; stack++)
		{
			double phi = stack * 2 * RT_PI / stacks;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);
			
			float x = static_cast<float>(cosPhi * sinTheta);
			float y = static_cast<float>(cosTheta);
			float z = static_cast<float>(sinPhi * sinTheta);
			float s = 1.0f - 
					  (static_cast<float>(stack) / 
					   stacks);
			float t = 1.0f - 
				      (static_cast<float>(slice) / 
					   slices);

			texCoords.push_back(RT::Vec2f(s, t));
			vertices.push_back(RT::Vec3f(x, y, z));
		}
	}

	std::vector<GLint> indices;

	for (int z = 0; z <= slices; z++)
	{
		for (int x = 0; x < stacks; x++)
		{
			GLint zero = x + z * stacks;
			GLint one = (x + 1) + z * stacks;
			GLint two = x + (z + 1) * stacks;
			GLint three = (x + 1) + (z + 1) * stacks;

			indices.push_back(zero);
			indices.push_back(two);
			indices.push_back(three);

			indices.push_back(zero);
			indices.push_back(three);
			indices.push_back(one);

		}
	}

	return RT_MeshBuilder()
			.AddVector3fAttribute("aPosition", &vertices)
			.AddVector2fAttribute("aTexCoord", &texCoords)
			.SetIndexBuffer(indices)
			.Create();
}

RT_Mesh *MeshFactory::createSphere(const int horizontalLines, 
								   const int verticalLines,
								   const float ray)
{
	float jumpCos = 360.0f / verticalLines;
	float jumpSin = 180.0f / horizontalLines;
	std::vector<RT::Vec3f> positions;
	std::vector<RT::Vec3f> normals;

	positions.push_back(RT::Vec3f(0.0f, ray, 0.0f));

	for (float y = 90 - jumpSin; y >= -90; y -= jumpSin)
	{
		float x = 180;
		float c = 0;

		while (c <= 360)
		{
			positions.push_back(RT::vc3::CartesianCoordinates(ray,
										  RT::Math::ToRadians(y), 
										  RT::Math::ToRadians(x)));
			x += jumpCos;
			if (x > 360)
				x -= 360;

			c += jumpCos;
		}
	}

	positions.push_back(RT::Vec3f(0.0f, -ray, 0.0f));

	for (RT::Vec3f &pos : positions)
	{
		RT::Vec3f normal(pos);
		normal.z = normal.z * -1;
		normals.push_back(normal.Normalize());
	}

	std::vector<GLint> indices;
	//indices.resize(positions.size() * 6);

	for (int i = 0; i < verticalLines; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);

		if (i == verticalLines - 1)
		{
			indices.push_back(verticalLines - i);
			continue;
		}

		indices.push_back(i + 2);
	}

	int control = (horizontalLines - 2) * verticalLines;
	int v1 = 1, v2 = verticalLines + 1;

	for (int i = 0; i < control; i++)
	{
		int zero = v1;
		int one = v2;
		int two = v2 + 1;
		int three = v1 + 1;

		if (v1 % verticalLines == 0)
		{
			two = v2 - (verticalLines - 1);
			three = v1 - (verticalLines - 1);
		}

		indices.push_back(zero);
		indices.push_back(one);
		indices.push_back(two);

		indices.push_back(zero);
		indices.push_back(two);
		indices.push_back(three);

		v1++;
		v2++;
	}

	for (int i = 0; i < verticalLines; i++)
	{
		int zero = v1;
		int one = v2;
		int two = v1 + 1;

		if (v1 % verticalLines == 0)
		{
			two = v1 - (verticalLines - 1);
		}

		indices.push_back(zero);
		indices.push_back(one);
		indices.push_back(two);

		v1++;
	}
	
	std::vector<RT::Vec3f> colors;
	int size = positions.size();

	for (int i = 0; i < size; i++)
	{
		colors.push_back(RT::Vec3f(0.5f, 0.5f, 1.0f));
	}

	return RT_MeshBuilder()
			.AddVector3fAttribute("aPosition", &positions)
			.AddVector3fAttribute("aNormal", &normals)
			.AddVector3fAttribute("aColor", &colors)
			.SetIndexBuffer(indices)
			.Create();;
}

RT_Mesh *MeshFactory::carregarTerreno(GLchar *nome, float p)
{
	SDL_Surface *image = IMG_Load(nome);

	if (!image)
	{
		throw std::exception("I wander when carrying the image");
	}

	std::vector<RT::Vec3f> positions;

	int prof = image->h;
	int largura = image->w;

	for (int z = 0; z < prof; z++)
	{
		for (int x = 0; x < largura; x++)
		{
			
			positions.push_back(
					RT::Vec3f(x - largura * 0.5f, 
							  Color(image, z, x).GetRed() * p,
							  z - prof * 0.5f)
				);
		}
	}

	std::vector<GLint> indices;

	for (int z = 0; z < prof - 1; z++)
	{
		for (int x = 0; x < largura - 1; x++)
		{
			int v1 = x + largura * z;
			int v2 = (x + 1) + (largura * z);
			int v3 = x + largura * (z + 1);
			int v4 = x + 1 + largura * (z + 1);


			indices.push_back(v1);
			indices.push_back(v4);
			indices.push_back(v2);

			indices.push_back(v1);
			indices.push_back(v3);
			indices.push_back(v4);
		}
	}

	std::vector<RT::Vec3f> colors;

	for (int z = 0; z < prof; z++)
	{
		for (int x = 0; x < largura; x++)
		{
			colors.push_back(RT::Vec3f(0.5f, 0.5f, 1.0f));
		}
	}

	SDL_FreeSurface(image);
	image = nullptr;

	return RT_MeshBuilder()
		.AddVector3fAttribute("aPosition", &positions)
		.AddVector3fAttribute("aColor", &colors)
		.SetIndexBuffer(indices)
		.Create();
}
