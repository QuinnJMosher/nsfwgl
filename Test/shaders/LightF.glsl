#version 410

in vec2 vTexCoord;
out vec3 LightOutput;

uniform float shadowBais = 0.01;

uniform vec3 CameraPos;
uniform float SpecPow = 2;

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
	
	vec4 shadowCoord = texSpaceOff * lightProjection * lightView * inverse(View) * vec4(position, 1);
	vec4 shadowValue = texture(ShadowMap, shadowCoord.xy);
	
	vec3 ambient = lightDiffuse * (1.f / 3.f);
	
	float lambert = max(0, dot(normal, -lightDirection));
	vec3 diffuse = lightDiffuse * lambert;
	
	
	vec3 R = normalize(reflect(lightDirection, normal));
	
	float specTerm = pow(max(0.0f, dot(R, eye)), SpecPow);
	vec3 specular = lightDiffuse * specTerm;
	specular = clamp(specular, 0.0f, 1.0f);
	
	if (shadowValue.x < shadowCoord.z) {
		LightOutput = ambient;
		//LightOutput = vec3(1, 0, 0);
	} else {
		LightOutput = (ambient + diffuse + specular);
		//LightOutput = vec3(0, 0, 1);
	}
	
	//LightOutput = shadowCoord.zzz;
	//LightOutput = shadowValue.zzz;
}