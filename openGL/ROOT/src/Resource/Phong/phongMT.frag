#version 330

in vec3 vNormal;
in vec3 vViewPath;
in vec2 vTexCoord;
in vec4 vTexWeight;
in float vDepth;
in float vClip;

uniform vec3 uLightDir;

uniform vec3 uAmbientLight;
uniform vec3 uDiffuseLight;
uniform vec3 uSpecularLight;

uniform vec3 uAmbientMaterial;
uniform vec3 uDiffuseMaterial;
uniform vec3 uSpecularMaterial;

uniform float uSpecularPower;

uniform sampler2D uTex0;
uniform sampler2D uTex1;
uniform sampler2D uTex2;
uniform sampler2D uTex3;

uniform bool isClipping;

out vec4 outColor;

void main()
{
	if(isClipping && vClip < 0.0)
	{
		discard;
	}

	vec3 L = normalize(uLightDir);
	vec3 N = normalize(vNormal);
	 
	vec3 ambient = uAmbientLight * uAmbientMaterial;

	float diffuseIntensity = max(dot(N, -L), 0.0);
	vec3 diffuse = diffuseIntensity * 
				   uDiffuseLight   * 
				   uDiffuseMaterial;

	float specularIntensity = 0.0;

	if(uSpecularPower > 0.0)
	{
		vec3 V = normalize(vViewPath);
		vec3 R = reflect(L, N);
		specularIntensity = pow(max(dot(R, V), 0.0), uSpecularPower);
	}

	vec3 specular = specularIntensity * uSpecularLight * uSpecularMaterial;

	//Interpolação das texturas
	float blendDistance = 0.99;
	float blendWidth = 100.0;
	float blendFactor = clamp((vDepth - blendDistance) *
							   blendWidth, 0.0, 1.0);

	vec2 nearCoord = vec2(vTexCoord.s, vTexCoord.t) * 50.0;

	vec4 texelNear = texture2D(uTex0, nearCoord) * vTexWeight.w +
					 texture2D(uTex1, nearCoord) * vTexWeight.z +
					 texture2D(uTex2, nearCoord) * vTexWeight.y +
					 texture2D(uTex3, nearCoord) * vTexWeight.x;

	vec2 farCoord = vec2(vTexCoord.s, vTexCoord.t) * 10.0;

	vec4 texelFar = texture2D(uTex0, farCoord) * vTexWeight.w +
					texture2D(uTex1, farCoord) * vTexWeight.z +
					texture2D(uTex2, farCoord) * vTexWeight.y +
					texture2D(uTex3, farCoord) * vTexWeight.x;

	vec4 texel = mix(texelNear, texelFar, blendFactor);

	vec3 color = clamp(texel.rgb * (ambient + diffuse) + 
					   specular, 0.0, 1.0);
	outColor = vec4(color, texel.a);
}