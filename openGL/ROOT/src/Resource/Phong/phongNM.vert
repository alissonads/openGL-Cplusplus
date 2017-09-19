#version 330

in vec3 aPosition;
in vec3 aNormal;
in vec3 aTangent;
in vec2 aTexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uWorld;

uniform vec3 uCameraPosition;
uniform vec3 uLightDir;

out vec3 vNormal;
out vec2 vTexCoord;

out vec3 vTangentLightDir;
out vec3 vTangentViewPos;
out vec3 vTangentPosition;

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

	vTexCoord = aTexCoord;

	vec3 T = normalize(vec3(uWorld * vec4(aTangent, 0.0)));
	vec3 N = normalize(vec3(uWorld * vec4(aNormal, 0.0)));
	T = normalize(T - dot(T, N) * N);

	vec3 B = cross(T, N);

	mat3 TBN = transpose(mat3(T, B, N));

	vTangentLightDir = TBN * uLightDir;
	vTangentViewPos = TBN * uCameraPosition;
	vTangentPosition = TBN * vec3(uWorld * vec4(aPosition, 0.0));
}