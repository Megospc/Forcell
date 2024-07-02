/**********************************
 * FORCELL Simulation
 * 
 * Copyright (c) 2024 Megospc
 * 
 * Version: 1.2.0 (02.07.2024)
 * 
**********************************/

#define VERSION "Version: 1.2.0 (02.07.2024)"

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#endif

#include "Definitions.h"
#include "Interface.h"
#include "GL.h"

int main() {
    if (!GL::Init()) return 1;

    if (!Interface::Init()) return 1;

    Interface::Begin();

    Interface::Destroy();

    GL::Destroy();
    
    return 0;
}