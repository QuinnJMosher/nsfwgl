#version 410

in vec2 vUV;

out vec4 fragColor;

uniform sampler2D Albedo;
uniform sampler2D Light;

void main() {
	vec3 lt = texture(Light, vUV).rgb;
	vec3 abd = texture(Albedo, vUV).rgb;
	
	fragColor = vec4(abd * lt, 1);
}
