/**********************************
 * FORCELL Simulation
 * 
 * Copyright (c) 2024 Megospc
 * 
 * Version: 1.8.0 (11.07.2024)
 * 
**********************************/

#define VERSION "Version: 1.8.0 (11.07.2024)"

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