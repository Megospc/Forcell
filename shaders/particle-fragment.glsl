#version 330 core

#define INNER_SIZE 0.3
#define HOLE_SIZE 0.72

in vec2 fPos;
in vec3 fBaseColor;
in vec2 fTexPos;

out vec4 fColor;

uniform float uBright;

void main() {
    float d = length(fPos);

    if (d < INNER_SIZE) {
        if (d < HOLE_SIZE*INNER_SIZE) fColor = vec4(fBaseColor, d/(HOLE_SIZE*INNER_SIZE)*0.6+0.4);
        else fColor = vec4(fBaseColor, 1.0);
    } else {
        fColor = vec4(fBaseColor, (1.0-(d-INNER_SIZE)/(1.0-INNER_SIZE))*0.6);
    }

    fColor.a *= uBright;
}