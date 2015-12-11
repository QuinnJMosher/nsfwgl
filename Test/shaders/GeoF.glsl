#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec4 vTangent;
in vec4 vBiTangent;
in vec2 vTexCoord;

layout(location = 0) out vec3 tAlbedo;
layout(location = 1) out vec3 tNormals;
layout(location = 2) out vec3 tPositions;

uniform sampler2D Diffuse;
uniform sampler2D NormalMap;
uniform int useNormMap;

void main() {
	tAlbedo = texture(Diffuse, vTexCoord).xyz;
	tPositions = vPosition.xyz;
	
	mat3 TBN = mat3(1);
	vec3 texNorm = vec3(0);
	
	if (useNormMap == 0) {
		tNormals = vNormal.xyz;
	} else {
		TBN = mat3 (
			normalize( vTangent.xyz ),
			normalize( vBiTangent.xyz ),
			normalize( vNormal.xyz ));
			
		tNormals = TBN * normalize(texture(NormalMap, vTexCoord).xyz*2-1);
	}
}