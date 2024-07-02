#pragma once

#define FONT_PATH "assets/Reef/Reef.ttf"

#ifndef INTERFACE_SCALE
#define INTERFACE_SCALE 1.0
#endif

#ifndef WHEEL_STEP
#define WHEEL_STEP 2.0
#endif

#define ZOOM_STEP 1.01
#define MAX_ZOOM 100.0
#define MIN_ZOOM -30.0
#define CAMERA_STEP 0.1

#include "GUI.h"
#include "Input.h"
#include "Simulation.h"
#include "Render.h"

#define CollapsingHeader(name) ImGui::Separator();if (ImGui::TreeNodeEx(name))
#define CollapsingEnd ImGui::TreePop()

namespace Interface {
    GL::Window* window = nullptr;

    ImFont* fontMedium;
    ImFont* fontSmall;

    bool escaping = false;
    bool pause = false;
    bool rendering = true;
    bool glowing = true;
    bool fullscreen = false;

    Simulation::Simulation* simulation = nullptr;
    Render::Render* render = nullptr;

    Simulation::Params params;
    Simulation::Rule rule;

    uint fps = 60, sps = 60;
    uint lastsecond;
    uint framecount = 0, stepcount = 0;
    int stepsperframe = 1;

    vec2 camera;
    float zoomsteps;

    float particlebright = 1.0;

    float zoom() {
        return POW(ZOOM_STEP, zoomsteps);
    }

    bool mousedown = false;
    vec2 mousepos;
    vec2 smouse;
    vec2 scamera;
    
    vec2 simsize() {
        return vec2(simulation->width, simulation->height);
    }
    vec2 scrsize() {
        return vec2(window->getWidth(), window->getHeight());
    }

    float simratio() {
        return simulation->width/simulation->height;
    }
    float scrratio() {
        return (float)window->getWidth()/window->getHeight();
    }

    vec2 getsimpos(vec2 scrpos) {
        return scrpos*vec2(scrratio()/simratio(), 1.0)/zoom();
    }

    void updatemouse() {
        mousepos = (Input::GetMouse()/scrsize()*2.0-1.0)*vec2(1.0, -1.0);
    }

    void updatecamera() {
        camera = scamera+(getsimpos(mousepos)-smouse);
    }

    void mousemove(float x, float y) {
        updatemouse();

        if (mousedown) updatecamera();
    }

    void mousestart() {
        updatemouse();

        mousedown = true;
        scamera = camera;
        smouse = getsimpos(mousepos);
    }

    void mouseend() {
        updatemouse();

        updatecamera();

        mousedown = false;
    }

    void mousebtn(ImGuiMouseButton button, bool down) {
        if (button == ImGuiMouseButton_Left) {
            if (down) mousestart();
            else mouseend();
        }
    }

    void mousewheel(float x, float y) {
        zoomsteps += y*WHEEL_STEP;

        SCLAMP(zoomsteps, MIN_ZOOM, MAX_ZOOM);
    }

    void cleanup() {
        if (simulation != nullptr) delete simulation;
        if (render != nullptr) delete render;
    }

    uint seed() { // Get random seed
        srand((uint)(Logger::Bench::Time()*1000.0));

        for (uint i = 0; i < 10; i++) rand();

        return rand();
    }

    void start() {
        cleanup();

        params.rule = &rule;
        params.seed = seed();

        simulation = new Simulation::Simulation(params);
        render = new Render::Render(window, simulation);
    }

    void updateFullscreen() {
        window->fullscreen(fullscreen, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    void keyboard(ImGuiKey key, int action) {
        if (action == GLFW_PRESS || action == GLFW_RELEASE) {
            if (key == ImGuiKey_Minus) zoomsteps -= 1.0;
            if (key == ImGuiKey_Equal) zoomsteps += 1.0;

            SCLAMP(zoomsteps, MIN_ZOOM, MAX_ZOOM);

            if (!mousedown) {
                if (key == ImGuiKey_LeftArrow) camera.x -= CAMERA_STEP/zoom();
                if (key == ImGuiKey_RightArrow) camera.x += CAMERA_STEP/zoom();
                if (key == ImGuiKey_DownArrow) camera.y -= CAMERA_STEP/zoom();
                if (key == ImGuiKey_UpArrow) camera.y += CAMERA_STEP/zoom();
            }
        }

        if (action == GLFW_PRESS) {
            if (key == ImGuiKey_Escape) escaping = true;

            if (key == ImGuiKey_Space || key == ImGuiKey_P) pause = !pause;

            if (key == ImGuiKey_O || key == ImGuiKey_9) camera = vec2(0.0, 0.0);
            if (key == ImGuiKey_O || key == ImGuiKey_0) zoomsteps = 0.0;

            if (key == ImGuiKey_R) start();

            if (key == ImGuiKey_F11) {
                fullscreen = !fullscreen;

                updateFullscreen();
            }
        }
    }

    bool Init() {
        window = new GL::Window("Forcell", WINDOW_WIDTH, WINDOW_HEIGHT, true);

        GUI::INI("assets/imgui.ini");

        if (!window->isOk()) return false;

        if (!GUI::Init(window)) return false;

        fontMedium = GUI::LoadTTF(FONT_PATH, 16.0*INTERFACE_SCALE);
        fontSmall = GUI::LoadTTF(FONT_PATH, 8.0*INTERFACE_SCALE);

        Input::Window(window);
        Input::Keyboard(keyboard);
        Input::MouseMove(mousemove);
        Input::MouseButton(mousebtn);
        Input::MouseWheel(mousewheel);

        start();

        zoomsteps = 0.0;
        camera = vec2(0.0, 0.0);

        lastsecond = time(NULL);

        GUI::style->FrameRounding = 5.0*INTERFACE_SCALE;
        GUI::style->GrabRounding = 5.0*INTERFACE_SCALE;
        GUI::style->WindowRounding = 5.0*INTERFACE_SCALE;
        
        return true;
    }

    void ColorLabel(string id, ImVec4 clr, ImVec2 size) {
        ImGui::PushStyleColor(ImGuiCol_Button, clr);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, clr);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, clr);

        ImGui::Button(id.c_str(), size);

        ImGui::PopStyleColor(3);
    }

    ImVec4 GetTypeColor(uint i) {
        return ImVec4(
            Render::baseColors[i*3],
            Render::baseColors[i*3+1],
            Render::baseColors[i*3+2],
            1.0
        );
    }

    void SmallOffset() {
        ImGui::PushFont(fontSmall);
        ImGui::NewLine();
        ImGui::PopFont();
    }
    
    void frame() {
        ImVec2 buttonTiny = ImVec2(18.0*INTERFACE_SCALE, 18.0*INTERFACE_SCALE);
        ImVec2 buttonShort = ImVec2(40.0*INTERFACE_SCALE, 18.0*INTERFACE_SCALE);
        ImVec2 buttonMedium = ImVec2(80.0*INTERFACE_SCALE, 18.0*INTERFACE_SCALE);
        ImVec2 buttonDouble = ImVec2(160.0*INTERFACE_SCALE+GUI::style->ItemSpacing.x, 18.0*INTERFACE_SCALE);

        if (!pause) for (uint i = 0; i < stepsperframe; i++) {
            simulation->step();

            stepcount++;
        }

        static float colorTone[3] = { 1.0, 1.0, 1.0 };

        if (rendering) {
            render->render(
                camera, zoom(),
                particlebright,
                (escaping ? vec3(0.5):vec3(1.0))*vec3(colorTone[0], colorTone[1], colorTone[2]),
                glowing,
                escaping
            );
        } else GL::Clear(0.0, 0.0, 0.0);

        if (escaping) {
            ImGui::PushFont(fontMedium);

            ImGui::Begin("Quit");
            ImGui::Text("Are you sure you really wish to quit the app?");

            if (ImGui::Button("Quit", buttonMedium)) window->close();
            ImGui::SameLine();
            if (ImGui::Button("Stay", buttonMedium)) escaping = false;

            ImGui::End();

            ImGui::PopFont();

            return;
        }

        ImGui::PushFont(fontMedium);

        ImGui::Begin("Forcell");

        if (ImGui::Button(pause ? "Continue":"Pause", buttonMedium)) pause = !pause;
        ImGui::SameLine();
        if (ImGui::Button("Quit", buttonMedium)) escaping = true;

        ImGui::Text("Time steps: %d", simulation->frame);

        SmallOffset();

        CollapsingHeader("Performance") {
            ImGui::Text("Frames per second: %d", fps);
            ImGui::Text("Steps  per second: %d", sps);

            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);

            ImGui::SliderInt("##stepsperframe", &stepsperframe, 1, 5, stepsperframe == 1 ? "%d step per frame":"%d steps per frame");

            ImGui::Checkbox("Rendering", &rendering);

            CollapsingEnd;
        }

        CollapsingHeader("Appearence") {
            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::SliderFloat("Particles opacity", &particlebright, 0.0, 1.0, "%.2f");

            #ifdef POSTPROCESSING
            ImGui::SetNextItemWidth(120.0*INTERFACE_SCALE);
            ImGui::ColorEdit3("Color tone", colorTone);
            #endif

            ImGui::Checkbox("Glow effect", &glowing);
            if (ImGui::Checkbox("Fullscreen mode", &fullscreen)) updateFullscreen();

            CollapsingEnd;
        }

        CollapsingHeader("Rule") {
            //if (ImGui::Button("Export", buttonMedium));
            //ImGui::SameLine();
            //if (ImGui::Button("Import", buttonMedium));

            if (ImGui::Button("Randomize", buttonDouble)) {
                rule.random(seed());
                start();
            }

            SmallOffset();

            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::InputInt("Number of types", &rule.types, 1, 1);
            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::DragFloat("Friction", &rule.friction, 0.0002, 0.0, 1.0, "%.3f");
            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::DragFloat("Attractor", &rule.attractor, 0.000001, 0.0, 1.0, "%.5f");
            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::DragFloat("Bounce force", &rule.bounceForce, 0.001, 0.0, 1.0, "%.2f");

            SmallOffset();

            CollapsingHeader("Forces") {
                if (ImGui::BeginTable(
                    "forcestable",
                    rule.types+2,
                    ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY,
                    ImVec2(180.0*INTERFACE_SCALE, 140.0*INTERFACE_SCALE)
                )) {
                    ImGui::TableSetupScrollFreeze(1, 1);
                    
                    for (int j = -1; j < rule.types; j++) {
                        ImGui::TableNextRow();

                        if (j >= 0) {
                            ImGui::TableSetColumnIndex(0);

                            ColorLabel("##typescolumnnames"+std::to_string(j), GetTypeColor(j), ImVec2(28.0*INTERFACE_SCALE, 18.0*INTERFACE_SCALE));

                            for (uint i = 0; i < rule.types; i++) {
                                ImGui::TableSetColumnIndex(i+1);

                                ImGui::SetNextItemWidth(30.0*INTERFACE_SCALE);
                                ImGui::DragFloat(("##forcetable"+std::to_string(i)+"-"+std::to_string(j)).c_str(), &rule.forces[i+j*10], 0.001, -5.0, 5.0, "%.2f");
                            }
                        } else {
                            for (uint i = 0; i < rule.types; i++) {
                                ImGui::TableSetColumnIndex(i+1);

                                ColorLabel("##typesrownames"+std::to_string(i), GetTypeColor(i), ImVec2(28.0*INTERFACE_SCALE, 18.0*INTERFACE_SCALE));
                            }
                        }
                    }

                    ImGui::EndTable();
                }

                CollapsingEnd;

                SmallOffset();
            }

            CollapsingHeader("Frequencies") {
                for (uint i = 0; i < rule.types; i++) {
                    ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
                    ImGui::DragFloat(("##freqs"+std::to_string(i)).c_str(), &rule.freqs[i], 0.002, 0.0, 10.0, "%.2f");
                    ImGui::SameLine();
                    ColorLabel("##freqsclr"+std::to_string(i), GetTypeColor(i), ImVec2(60.0*INTERFACE_SCALE, 18.0*INTERFACE_SCALE));
                }

                if (ImGui::Button("Reset", buttonMedium)) {
                    for (uint i = 0; i < rule.types; i++) rule.freqs[i] = 1.0;
                }

                CollapsingEnd;
            }

            CollapsingEnd;
        }

        CollapsingHeader("Settings") {
            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::DragInt("Simulation size", &params.width, 10.0, 100, 10000);
            params.height = params.width;
            ImGui::SetNextItemWidth(100.0*INTERFACE_SCALE);
            ImGui::DragInt("Number of particles", &params.particles, 10.0, 0, 100000);

            if (ImGui::Button("Restart", buttonMedium)) start();

            CollapsingEnd;
        }

        rule.clamp();
        params.clamp();
        
        CollapsingHeader("Build info") {
            ImGui::BulletText(VERSION);

            #ifdef OPTIMIZATIONS_ON
            ImGui::BulletText("Optimizations enabled");
            #else
            ImGui::BulletText("Optimizations disabled (debug build)");
            #endif

            #ifdef POSTPROCESSING
            ImGui::BulletText("Postprocessing enabled");
            ImGui::BulletText("Framebuffer resolution reducing: x%.1f", FRAMEBUFFER_REDUCING);
            #else
            ImGui::BulletText("Postprocessing disabled");
            #endif

            CollapsingEnd;
        }
        
        SmallOffset();

        ImGui::Text("Copyright (c) 2024 Megospc");
        
        ImGui::End();

        ImGui::PopFont();

        framecount++;

        uint cursecond = time(NULL);

        if (cursecond != lastsecond) {
            sps = stepcount;
            fps = framecount;

            stepcount = 0;
            framecount = 0;

            lastsecond = cursecond;
        }
    }

    void Destroy() {
        cleanup();

        GUI::Destroy();

        delete window;
    }

    void Begin() {
        GUI::Begin(frame);
    }
}