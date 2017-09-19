#version 330

in vec4 vRefractPos;
in vec4 vReflectPos;
in vec3 vViewPath;

uniform sampler2D uRefraction;
uniform sampler2D uReflection;

uniform sampler2D uWaterNormal;
uniform float uWaveHeight;

uniform vec2 uOffSet;

out vec4 outColor;

void main()
{
	vec2 refractCoords = vRefractPos.xy / vRefractPos.w / 2.0 + 0.5;
	vec2 reflectCoords = vReflectPos.xy / vReflectPos.w / 2.0 + 0.5;

	vec2 waveColor = ((texture(uWaterNormal, reflectCoords + uOffSet).rg - 0.5) * 0.2) * uWaveHeight;

	vec4 refractColor = texture(uRefraction, refractCoords + waveColor);
	vec4 reflectColor = texture(uReflection, reflectCoords + waveColor); 

	vec4 dullColor = vec4(0.3, 0.3, 0.5, 1.0);
	float fresnel = dot(normalize(vViewPath), vec3(0, 1, 0));

	outColor = mix(mix(reflectColor, refractColor, fresnel), dullColor, 0.1);
}