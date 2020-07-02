#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 texCoords;
	vec4 normal;
}gs_in[];

const float MAGNITUDE = 0.4;
uniform float time;
out vec2 fTexCoords;

void explode(int index)
{
	vec4 normal = gs_in[index].normal;
	vec4 position = gl_in[index].gl_Position;
	vec4 direction = normal * ((sin(time)+ 1.0)/ 2.0) * MAGNITUDE;
	gl_Position = position + direction;
	fTexCoords = gs_in[index].texCoords;
	EmitVertex();
}

void generate_Line(int index)
{
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = gl_in[index].gl_Position + gs_in[index].normal * MAGNITUDE;
	EmitVertex();
	EndPrimitive();
}

void main()
{
	explode(0);
	explode(1);
	explode(2);
	EndPrimitive();
}