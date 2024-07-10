#version 330 core

in vec3 fBaseColor;

out vec4 fColor;

uniform float uOpacity;

void main() {
    fColor = vec4(fBaseColor, 0.25*uOpacity);
}