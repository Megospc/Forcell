#version 330 core

layout (location = 0) in vec2 aVertex;
layout (location = 1) in float aType;

out vec3 fBaseColor;

uniform vec2 uSimSize;
uniform vec3 uBaseColors[10];

void main() {
    fBaseColor = uBaseColors[int(aType)];

    gl_Position = vec4(aVertex/uSimSize*2.0-1.0, 1.0, 1.0);
}