#version 330

in vec3 vNormal;
in vec2 vTexCoord;

in vec3 vTangentLightDir;
in vec3 vTangentViewPos;
in vec3 vTangentPosition;

uniform vec3 uAmbientLight;
uniform vec3 uDiffuseLight;
uniform vec3 uSpecularLight;

uniform vec3 uAmbientMaterial;
uniform vec3 uDiffuseMaterial;
uniform vec3 uSpecularMaterial;

uniform float uSpecularPower;

uniform sampler2D uTexture;
uniform sampler2D uNormalMap;

out vec4 outColor;

void main()
{
	vec3 L = normalize(vTangentLightDir);

	vec3 normal = texture(uNormalMap, vTexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 N = normalize(normal);
	 
	vec3 ambient = uAmbientLight * uAmbientMaterial;

	float diffuseIntensity = max(dot(N, -L), 0.0);
	vec3 diffuse = diffuseIntensity * 
				   uDiffuseLight   * 
				   uDiffuseMaterial;

	float specularIntensity = 0.0;

	if(uSpecularPower > 0.0)
	{
		vec3 viewPath = vTangentViewPos - vTangentPosition;
		vec3 V = normalize(viewPath);
		vec3 R = reflect(L, N);
		specularIntensity = pow(max(dot(R, V), 0.0), uSpecularPower);
	}

	vec3 specular = specularIntensity * uSpecularLight * uSpecularMaterial;

	vec4 texel = texture(uTexture, vTexCoord);

	vec3 color = clamp(texel.rgb * (ambient + diffuse) + 
					   specular, 0.0, 1.0);
	outColor = vec4(color, texel.a);
}