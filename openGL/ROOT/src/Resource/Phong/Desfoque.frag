#version 330

in vec2 vTexCoord;

uniform sampler2D uTex0;
uniform sampler2D uTex1;

uniform int uWidth;
uniform int uHeight;

uniform float uPercentage;
uniform int uSize;

out vec4 outColor;

void main(void)
{
	float dx = 1.0 / uWidth;
	float dy = 1.0 / uHeight;

	vec4 rColor = vec4(0, 0, 0, 0);
	
	float m = 1.0 / (uSize * uSize);
	int s = uSize / 2;

	for(int y = 0; y < uSize; y++)
	{
		for(int x = 0; x < uSize; x++)
		{
			rColor += texture(uTex0, vTexCoord + 
						vec2( dx * (x - (0.5 * uSize)),  
							  dy * (y - (0.5 * uSize)))) * m;
		}
	}
				   
	vec4 tex = texture(uTex0, vTexCoord);
	tex = vec4(mix(tex, rColor, uPercentage));

	vec4 f = texture(uTex1, vTexCoord);

	outColor = ((f.rgb == 0.0)? tex : f);
}
