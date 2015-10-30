#version 410

in vec4 vNormal;
out float FragDepth;

uniform vec3 lightDir;

void main() {
	FragDepth = gl_FragCoord.z;
}