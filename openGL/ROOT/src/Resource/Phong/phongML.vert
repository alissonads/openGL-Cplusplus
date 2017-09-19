#version 330

in vec3 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uWorld;

uniform vec3 uCameraPosition;

out vec3 vNormal;
out vec3 vViewPath;
out vec2 vTexCoord;

void main()
{
	vec4 worldPos = uWorld * vec4(aPosition, 1.0);
	gl_Position = uProjection * uView * worldPos;

	//converte os valores da normal 
	//de coordenada de modelo
	//para coordenada de mundo.
	//ultimo parametro 0.0 pq é
	//uma direção
	vNormal = (uWorld * vec4(aNormal, 0.0)).xyz;

	vViewPath = uCameraPosition - worldPos.xyz;
	vTexCoord = aTexCoord;
}