#version 330

in vec2 vTexCoord;

uniform sampler2D uTexture;

out vec4 outColor;

void main()
{
	outColor = texture(uTexture, vTexCoord);
}