/**********************************
 * FORCELL Simulation
 * 
 * Copyright (c) 2024 Megospc
 * 
 * Version: 1.0.0 (01.07.2024)
 * 
**********************************/

#define VERSION "Version: 1.0.0 (01.07.2024)"

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#endif

#include "Definitions.h"
#include "Interface.h"
#include "GL.h"

GL::Window* window;

int main() {
    if (!GL::Init()) return 1;

    #ifdef FULLSCREEN
    window = new GL::Window("Forcell");
    #else
    window = new GL::Window("Forcell", WINDOW_WIDTH, WINDOW_HEIGHT, true);
    #endif
    

    if (!window->isOk()) return 1;

    Interface::Init(window);

    Interface::Begin();

    Interface::Destroy();

    delete window;

    GL::Destroy();
    
    return 0;
}