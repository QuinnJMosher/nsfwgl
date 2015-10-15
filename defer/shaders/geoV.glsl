#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec4 tangent;
layout(location = 3) in vec2 TexCoord;

out vec4 vPosition;
out vec3 vNormal;
out vec3 vTangent;
out vec3 vBiTangent;
out vec2 vUV;

uniform mat4 View;
uniform mat4 Projection;
//uniform mat4 Model;//model's transform

void main() {
	vPosition = View * Position;
	vNormal = normalixe(View * Normal).xyz;
	vTangent = tangent.xyz
	vBiTangent = cross(vNormal, vTangent);
	vUV = TexCoord;
	
	//gl_Position = (Projection * View * Model) * position;
	gl_Position = (Projection * View) * position;
}