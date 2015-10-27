#version 410

in vec2 vTexCoord;;
out vec4 FragColor;

uniform sampler2D Diffuse;

void main() {
	FragColor = texture(Diffuse, vTexCoord);
	//FragColor = vec4(vTexCoord, 0, 1);
	//FragColor = vec4(1, 0, 0, 1);
}