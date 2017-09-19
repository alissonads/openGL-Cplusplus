#ifndef	 __MESH_FACTORY_H__
#define	 __MESH_FACTORY_H__

#include <RTmath.h>
#include <GL\glew.h>

class RT_Mesh;
class RT_MeshBuilder;

class MeshFactory
{
private:
	static float CalcLinear(float min, float max, 
							float value, bool inverse);
	static float CalcPiramid(float min, 
							 float max, 
							 float value);
public:
	static RT_Mesh *createSquare(float width = 1.0f, 
								 float height = 1.0f);
	static RT_Mesh *createXZSquare(const float width = 1.0f,
								   const float depth = 1.0f);
	static RT_Mesh *createCube(float width = 1.0f, 
							   float height = 1.0f,
							   float depth = 1.0f);
	static RT_Mesh *createCanvas();
	static RT_Mesh *loadTerrain(GLchar *name, 
								float scale, 
								int texRepeat);
	static RT_Mesh *createSquareWithNormalMap();
	static RT_Mesh *createXZSquare(const int width, 
								   const int depth,
								   const float y   );
	static RT_Mesh *createSkySphere(const int slices, 
									const int stacks);
	static RT_Mesh *createSphere(const int horizontalLines,
								 const int verticalLines,
								 const float ray);

	static RT_Mesh *carregarTerreno(GLchar *nome, float p);
};

#endif //__MESH_FACTORY_H__
