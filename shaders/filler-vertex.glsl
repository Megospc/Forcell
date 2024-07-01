#version 330 core

layout (location = 0) in vec2 aVertex;

void main() {
    gl_Position = vec4(aVertex, 1.0, 1.0);
}