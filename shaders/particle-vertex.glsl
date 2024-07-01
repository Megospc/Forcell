#version 330 core

#define INNER_SIZE 0.3

layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aPosition;
layout (location = 2) in float aSize;
layout (location = 3) in float aType;

out vec2 fPos;
out vec3 fBaseColor;
out vec2 fTexPos;

uniform vec3 uBaseColors[10];
uniform vec2 uSimSize;

void main() {
    fPos = aVertex;

    fBaseColor = uBaseColors[int(aType)];

    fTexPos = (aVertex*aSize/INNER_SIZE+aPosition)/uSimSize;

    gl_Position = vec4(fTexPos*2.0-1.0, 1.0, 1.0);
}