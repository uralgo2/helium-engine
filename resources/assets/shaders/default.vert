#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 normalMatrix;

uniform vec3 icolor;

out vec3 fcolor;
out vec3 fpos;
out vec3 fnormal;
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    fpos = vec3(projection * view * model * vec4(position, 1.0f));
    fcolor = icolor;
    fnormal = vec3(normalMatrix * vec4(normal, 1.0f));
}