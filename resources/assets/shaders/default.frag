#version 330 core

out vec4 color;
in vec3 fcolor;
in vec3 fpos;
in vec3 fnormal;

uniform vec3 lightPosition; 
uniform vec3 lightColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse 
    vec3 norm = normalize(fnormal);
    vec3 lightDir = normalize(lightPosition - fpos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * fcolor;
    color = vec4(result, 1.0f);
}