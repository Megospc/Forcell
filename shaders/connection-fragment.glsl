#version 330 core

in vec3 fBaseColor;

out vec4 fColor;

void main() {
    fColor = vec4(fBaseColor, 0.25);
}