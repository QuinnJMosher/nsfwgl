#version 410

in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D Diffuse;
uniform sampler2D Light;

void main() {
	vec3 diffuseVal = texture(Diffuse, vTexCoord).rgb;	
	vec3 lightVal = texture(Light, vTexCoord).rgb;
	
	FragColor = vec4(diffuseVal * lightVal, 1);
	//FragColor = texture(Light, vTexCoord);//vec4(diffuseVal, 1);
}