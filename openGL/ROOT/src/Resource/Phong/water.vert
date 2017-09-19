#version 330

in vec3 aPosition;
in vec2 aTexCoord;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uCameraPosition;

uniform mat4 uReflexView;

out vec4 vRefractPos;
out vec4 vReflectPos;
out vec3 vViewPath;

void main()
{
	vec4 worldPos = uWorld * vec4(aPosition, 1.0);
	gl_Position = uProjection * uView * worldPos;
	vRefractPos = gl_Position;
	vReflectPos = uProjection * uReflexView * worldPos;
	vViewPath = uCameraPosition - worldPos.xyz;
}