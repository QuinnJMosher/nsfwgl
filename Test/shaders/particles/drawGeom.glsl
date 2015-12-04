#version 410

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 pPosition[];
in float pSize[];
in float pLifetime[];

out vec4 fColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 CamTransform;

uniform float size;
uniform float color;

void main() {
	fColor = color;
	
	float halfSize = size * 0.5f;
	
	vec3 corners[4];
	corners[0] = vec3( halfSize, -halfSize, 0);
	corners[1] = vec3( halfSize, halfSize, 0);
	corners[2] = vec3( -halfSize, -halfSize, 0);
	corners[3] = vec3( -halfSize, halfSize, 0);
	
	vec3 zAxis = normalize( CamTransform[3].xyz - pPosition[0] );
	vec3 xAxis = cross( CamTransform[1].xyz, zAxis);
	vec3 yAxis = cross( zAxis, xAxis );
	mat3 bilboard = mat3(xAxis,, yAxis, zAxis);
	
	gl_Position = Projection * View * vec4(bilboard * corners[0] + pPosition[0], 1);
	EmitVertex();
	
	gl_Position = Projection * View * vec4(bilboard * corners[1] + pPosition[1], 1);
	EmitVertex();
	
	gl_Position = Projection * View * vec4(bilboard * corners[2] + pPosition[2], 1);
	EmitVertex();
	
	gl_Position = Projection * View * vec4(bilboard * corners[3] + pPosition[3], 1);
	EmitVertex();
}