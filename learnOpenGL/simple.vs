#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT
{
    vec2 texCoords;
    vec4 normal;
}vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vs_out.texCoords = aTexCoords;
    mat4 normalMatrix = mat4(transpose(inverse(view * model)));
    vs_out.normal = projection * normalMatrix * vec4(aNormal, 0.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}