#version 330 core

#define INNER_SIZE 0.3

layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aPosition;
layout (location = 2) in float aSize;
layout (location = 3) in float aType;
layout (location = 4) in vec2 aVelocity;

out vec2 fPos;
out vec3 fBaseColor;
out vec2 fTexPos;
out float fOpacity;
out float fBright;

uniform vec3 uBaseColors[10];
uniform vec2 uSimSize;
uniform int uVelshow;

void main() {
    fPos = aVertex;

    if (uVelshow == 1) {
        fBaseColor = uBaseColors[int(aType)];

        float opacity = 0.5+(abs(aVelocity.x)+abs(aVelocity.y))/20.0;

        if (opacity > 1.2) opacity = 1.2;

        if (opacity > 1.0) fOpacity = 1.0, fBright = opacity;
        else fOpacity = opacity, fBright = 1.0;
    } else {
        fOpacity = 1.0;
        fBright = 1.0;
    }

    fTexPos = (aVertex*aSize/INNER_SIZE+aPosition)/uSimSize;

    gl_Position = vec4(fTexPos*2.0-1.0, 1.0, 1.0);
}