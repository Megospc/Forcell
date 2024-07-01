#version 330 core

layout (location = 0) in vec2 aVertex;

out vec2 fPos;

void main() {
    fPos = (aVertex+1.0)/2.0;

    gl_Position = vec4(aVertex, 1.0, 1.0);
}