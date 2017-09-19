#version 330

in vec3 aPosition;
in vec3 aColor;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uWorld;

out vec4 vColor;

void main()
{
	vec4 worldPos = uWorld * vec4(aPosition, 1.0);
	gl_Position = uProjection * uView * worldPos;
	vColor = vec4(aColor, 1.0);
}