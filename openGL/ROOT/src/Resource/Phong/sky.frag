#version 330

in float vY;
in vec2 vTexCoord;

uniform vec3 uColorLow;
uniform vec3 uColorHigh;

uniform vec2 uCloudOffset0;
uniform vec2 uCloudOffset1;

uniform sampler2D uCloud0;
uniform sampler2D uCloud1;

out vec4 outColor;

void main()
{
	vec3 color = mix(uColorLow, uColorHigh, vY);

	vec3 cloud0 = vec3(texture(uCloud0, (vTexCoord * 2.0) + uCloudOffset0));
	vec3 cloud1 = vec3(texture(uCloud1, (vTexCoord * 2.0) + uCloudOffset1));
	vec3 clouds = clamp(cloud0 + cloud1, 0.0, 0.7);

	outColor = vec4(clamp(color + clouds, 0.0, 1.0), 1.0);
}