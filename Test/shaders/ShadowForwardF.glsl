#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec4 vTan;
in vec4 vBiTan;
in vec4 vShadowCoord;
in vec2 vUV;

out vec4 FragColor;

uniform vec3 lightDirection;
uniform float shadowBais = 0.01;

uniform sampler2D shadowMap;
uniform sampler2D albedo;
uniform sampler2D normalMap;

uniform vec3 cameraPos;
uniform float specPow = 25;

uniform int useNormMap;

//debug stuff
uniform int db_useSpec = 1;
uniform int db_useDiffuse = 1;
uniform int db_useAmbient = 1;
uniform int db_useShadow = 1;
uniform int db_useColor = 1;

void main() {
	//normalMap read
	mat3 TBN = mat3(1);
	vec3 fNormal = vec3(0);
	
	if (useNormMap == 0) {
		fNormal = vNormal.xyz;
	} else {
		TBN = mat3(
			normalize(vTan.xyz),
			normalize(vBiTan.xyz),
			normalize(vNormal.xyz));
		fNormal = TBN * (texture(normalMap, vUV).xyz * 2 - 1);
	}
	
	//light calculations
	float ambient = 0.3;
	float diffuse = max(0, dot(normalize(fNormal), lightDirection));
	
	//specular
	vec3 eye = normalize(cameraPos - vPosition.xyz);
	vec3 R = reflect(-lightDirection, fNormal);
	float specular = pow(max(0.0f, dot(R, eye)), specPow);
	specular = clamp(specular, 0.0f, 1.0f);
	
	//shadow calculations
	vec4 shadowColor = texture(shadowMap, vShadowCoord.xy);
	
	if (shadowColor.z < vShadowCoord.z - shadowBais && db_useShadow == 1) {
		diffuse = 0;
		specular = 0;
	}
	
	//final assignment
	float totalLight = (specular * db_useSpec) + (diffuse * db_useDiffuse) + (ambient * db_useAmbient);
	
	if (db_useColor == 1) {
		if (db_useDiffuse + db_useSpec + db_useAmbient == 0) {
			FragColor = texture(albedo, vUV);
		} else {
			FragColor = texture(albedo, vUV) * totalLight;
		}
	} else {
		FragColor = vec4(totalLight, totalLight, totalLight, 1);
	}
}