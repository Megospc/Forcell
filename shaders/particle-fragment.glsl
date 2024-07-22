#version 330 core

#define INNER_SIZE 0.3
#define HOLE_SIZE 0.72

in vec2 fPos;
in vec3 fBaseColor;
in vec2 fTexPos;
in float fOpacity;
in float fBright;

out vec4 fColor;

uniform float uOpacity;
uniform float uHole;
uniform float uSizing;
uniform float uGlowing;

void main() {
    float d = length(fPos);

    if (d < INNER_SIZE*uSizing) {
        if (d < HOLE_SIZE*INNER_SIZE*uSizing*uHole) {
            fColor = vec4(fBaseColor, (d/(HOLE_SIZE*INNER_SIZE*uSizing*uHole)*0.6+0.4));
        } else {
            fColor = vec4(fBaseColor, 1.0);
        }
    } else {
        fColor = vec4(fBaseColor, (1.0-(d-INNER_SIZE*uSizing)/(1.0-INNER_SIZE*uSizing))*0.6*uGlowing);
    }

    fColor.rgb *= fBright;

    fColor.a *= uOpacity*fOpacity;
}