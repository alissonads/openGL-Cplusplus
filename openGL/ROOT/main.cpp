#include <iostream>
#include "src\System\Window.h"
#include "src\CG\MyScene.h"
#include "src\CG\Terrain.h"
#include "src\CG\PostProcessing.h"
#include "src\CG\NormalMapping.h"
#include "src\CG\MultiTexture.h"
#include "src\CG\Water.h"
#include "src\CG\Raytracing.h"
#include "src\CG\Terreno.h"

int main(int argc, char **argv)
{
	Window(new Water(),
		   "--- TESTE ---", 
		   1024, 768       ).show();
}