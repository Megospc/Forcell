#version 330 core

in vec2 fPos;

out vec4 fColor;

uniform sampler2D uTexture;

void main() {
    fColor = texture(uTexture, fPos);
}