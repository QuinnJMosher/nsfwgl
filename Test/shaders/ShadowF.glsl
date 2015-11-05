#version 410

out vec3 FragDepth;

void main() {
	FragDepth = gl_FragCoord.zzz;
}