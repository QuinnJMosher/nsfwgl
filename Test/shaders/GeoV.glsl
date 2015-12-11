#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec4 Tangent;
layout(location = 3) in vec2 TexCoord;

out vec4 vPosition;
out vec4 vNormal;
out vec4 vTangent;
out vec4 vBiTangent;
out vec2 vTexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
	gl_Position = Projection * View * Model * Position;
	vTexCoord = TexCoord;
	vNormal = normalize(View * Model * Normal);
	vTangent = normalize(View * Model * Tangent);
	vBiTangent = normalize(View * Model * vec4(cross(Normal.xyz, Tangent.xyz), 0));
	vPosition = (View * Model * Position);
}