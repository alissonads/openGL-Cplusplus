#version 330

in vec3 vNormal;
in vec3 vViewPath;
in vec2 vTexCoord;

uniform vec3 uLightDir;

uniform vec3 uAmbientLight;
uniform vec3 uDiffuseLight;
uniform vec3 uSpecularLight;

uniform vec3 uAmbientMaterial;
uniform vec3 uDiffuseMaterial;
uniform vec3 uSpecularMaterial;

uniform float uSpecularPower;

uniform sampler2D uTexture;

uniform bool uUseText;

out vec4 outColor;

void main()
{
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

	vec4 texel = (uUseText)? texture(uTexture, vTexCoord) : 
							 vec4(1, 1, 1, 1);
	float a = (uUseText)? texel.a : 1.0;

	vec3 color = clamp(texel.rgb * (ambient + diffuse) + 
					   specular, 0.0, 1.0);
	outColor = vec4(color, a);
}