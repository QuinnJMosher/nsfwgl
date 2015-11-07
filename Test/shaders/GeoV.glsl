#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec4 Tangent;
layout(location = 3) in vec2 TexCoord;

out vec4 vPosition;
out vec4 vNormal;
out vec2 vTexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
	gl_Position = Projection * View * Model * Position;
	vTexCoord = TexCoord;
	vNormal = normalize(View * Model * Normal);
	vPosition = (View * Model * Position);
}