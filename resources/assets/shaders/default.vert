#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 icolor;


out vec4 fcolor;
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    fcolor = vec4(color*icolor, 1.0);
}