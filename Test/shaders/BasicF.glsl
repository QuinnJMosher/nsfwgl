#version 410

in vec2 vTexCoord;;
out vec4 FragColor;

uniform sampler2D Tex;

void main() {
	FragColor = texture(Tex, vTexCoord);
}