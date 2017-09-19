#version 330

in vec3 aPosition;
in vec2 aTexCoord;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;

out float vY;
out vec2 vTexCoord;

void main()
{
	vec4 worldPos = uWorld * vec4(aPosition, 1.0);
	gl_Position = uProjection * uView * worldPos;
	
	vY = aPosition.y;
	vTexCoord = aTexCoord;
}