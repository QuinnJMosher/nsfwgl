#version 410

in vec2 vTexCoord;
out vec3 LightOutput;

uniform float shadowBias = 0.2;

uniform vec3 CameraPos;
uniform float SpecPow = 25;

uniform mat4 View;

uniform vec3 lightDirection;
uniform vec3 lightDiffuse;

uniform mat4 texSpaceOff;
uniform mat4 lightProjection;
uniform mat4 lightView;

uniform sampler2D PosMap;
uniform sampler2D NormMap;
uniform sampler2D ShadowMap;

void main() {
	vec3 normal = normalize(texture(NormMap, vTexCoord).xyz);
	vec3 position = texture(PosMap, vTexCoord).xyz;
	vec3 eye = normalize(CameraPos - position); // for specular and deprojection
	vec3 vLightDir = normalize((View * vec4(-lightDirection, 0)).xyz);
	//vec3 vLightDir = normalize(-lightDirection);
	
	vec4 shadowCoord = texSpaceOff * lightProjection * lightView 
							* inverse(View)  * vec4(position, 1);
	vec4 shadowValue = texture(ShadowMap, shadowCoord.xy);
	
	vec3 ambient = lightDiffuse * (1.f / 3.f);
	
	float lambert = max(0, dot(normalize(normal), vLightDir));
	vec3 diffuse = lambert * lightDiffuse;
	
	vec3 R = normalize(reflect(vLightDir, normal));
	
	float specTerm = pow(max(0.0f, dot(R, eye)), SpecPow);
	vec3 specular = lightDiffuse * specTerm;
	specular = clamp(specular, 0.0f, 1.0f);
	
	if (shadowValue.z < shadowCoord.z) {
		LightOutput = ambient;
		//LightOutput = vec3(1, 0, 0);
	} else {
		LightOutput = (ambient + diffuse + specular);
		//LightOutput = vec3(0, 0, 1);
	}
	
	//LightOutput = ambient + diffuse;// + specular;//cancel out shadowing
	LightOutput = diffuse;//cancel out shadowing
	
	//LightOutput = shadowValue.xyz;
	//LightOutput = (inverse(View) * vec4(position,1)).xyz;
}