#pragma once

#define FONT_PATH "assets/Reef/Reef.ttf"

#define ZOOM_STEP 1.01
#define MAX_ZOOM 100.0
#define MIN_ZOOM -30.0
#define CAMERA_STEP 0.1

#include "GUI.h"
#include "Input.h"
#include "Simulation.h"
#include "Render.h"
#include "Files.h"

#define CollapsingHeader(name) ImGui::Separator();if (ImGui::TreeNodeEx(name))
#define CollapsingEnd ImGui::TreePop()

namespace Interface {
    GL::Window* window = nullptr;

    ImFont* fontMedium[4];

    bool escaping = false;
    bool pause = false;
    bool rendering = true;
    bool glowing = false;
    bool fullscreen = false;
    bool confignoupdate = false;
    bool postproc = false;

    Simulation::Simulation* simulation = nullptr;
    Render::Render* render = nullptr;

    Simulation::Params params;
    Simulation::Rule rule;

    uint fps = 60, sps = 60;
    uint lastsecond;
    uint framecount = 0, stepcount = 0;
    int stepsperframe = 1;
    int threadcount = 1;
    uint windowwidth = 1600;
    uint windowheight = 900;

    vec2 camera;
    float zoomsteps;
    float wheelsensitivity = 20.0;
    int interfacescale = 1;
    int ppReducing = 3.0;

    float Scale(float size, int scale = interfacescale) {
        return size*POW(2.0, scale);
    }

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
        zoomsteps += y*wheelsensitivity;

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

    void recreateRender() {
        if (simulation == nullptr) return;

        if (render != nullptr) delete render;
        
        render = new Render::Render(window, simulation, postproc);
    }

    void start() {
        cleanup();

        params.rule = &rule;
        params.seed = seed();

        simulation = new Simulation::Simulation(params);
        render = new Render::Render(window, simulation, postproc);
    }

    void updateFullscreen() {
        window->fullscreen(fullscreen, windowwidth, windowheight);
    }

    void keyboard(ImGuiKey key, int action) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (key == ImGuiKey_Minus) zoomsteps -= 10.0;
            if (key == ImGuiKey_Equal) zoomsteps += 10.0;

            SCLAMP(zoomsteps, MIN_ZOOM, MAX_ZOOM);

            if (!mousedown) {
                if (key == ImGuiKey_LeftArrow) camera.x += CAMERA_STEP/zoom();
                if (key == ImGuiKey_RightArrow) camera.x -= CAMERA_STEP/zoom();
                if (key == ImGuiKey_DownArrow) camera.y += CAMERA_STEP/zoom();
                if (key == ImGuiKey_UpArrow) camera.y -= CAMERA_STEP/zoom();
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

    string scalestr(int scale) {
        switch (scale) {
            case 0: return "x1";
            case 1: return "x2";
            case 2: return "x4";
        }

        return "x2";
    }

    int strscale(string str) {
        if (str == "x1") return 0;
        if (str == "x2") return 1;
        if (str == "x4") return 2;

        return 1;
    }

    void SaveConfig() {
        string str = "";

        if (fullscreen) str += KeyVal("fullscreen", "");
        if (glowing) str += KeyVal("glowing", "");
        if (postproc) str += KeyVal("postprocessing", "");

        str += KeyVal("threads", threadcount);
        str += KeyVal("wheel", wheelsensitivity);
        str += KeyVal("width", window->getWidth());
        str += KeyVal("height", window->getHeight());
        str += KeyVal("interface", scalestr(interfacescale));
        str += KeyVal("pp-reducing", ppReducing);

        File::Data data;

        data.data = (char*)str.c_str();
        data.length = str.length();

        File::Write("config.txt", data);
    }

    void LoadConfig() {
        File::Data data = File::Read("config.txt", true);

        if (data.length == -1) return;

        glowing = false;
        fullscreen = false;
        confignoupdate = false;
        postproc = false;

        string str = data.data;

        string line = "";

        for (uint i = 0; i < str.length(); i++) {
            char c = str[i];

            if (c == '\n') {
                KeyVal data(line);

                if (data.key == "fullscreen") fullscreen = true;
                if (data.key == "glowing") glowing = true;
                if (data.key == "postprocessing") postproc = true;

                if (data.key == "noupdate") confignoupdate = true;

                if (data.key == "threads") threadcount = stoi(data.val);
                if (data.key == "wheel") wheelsensitivity = stof(data.val);
                if (data.key == "pp-reducing") ppReducing = stoi(data.val);
                if (data.key == "width") windowwidth = stoi(data.val);
                if (data.key == "height") windowheight = stoi(data.val);
                if (data.key == "interface") interfacescale = strscale(data.val);

                line = "";
            } else line += c;
        }
    }

    void StyleRescale() {
        GUI::style->FrameRounding = Scale(5.0);
        GUI::style->GrabRounding = Scale(5.0);
        GUI::style->WindowRounding = Scale(5.0);
    }

    bool Init() {
        LoadConfig();

        window = new GL::Window("Forcell", windowwidth, windowheight, true);

        updateFullscreen();

        GUI::INI("assets/imgui.ini");

        if (!window->isOk()) return false;

        if (!GUI::Init(window)) return false;

        for (uint i = 0; i < 3; i++) {
            fontMedium[i] = GUI::LoadTTF(FONT_PATH, Scale(16.0, i));
        }

        Input::Window(window);
        Input::Keyboard(keyboard);
        Input::MouseMove(mousemove);
        Input::MouseButton(mousebtn);
        Input::MouseWheel(mousewheel);

        StyleRescale();

        start();

        zoomsteps = 0.0;
        camera = vec2(0.0, 0.0);

        lastsecond = time(NULL);

        threadcount = Simulation::GetThreads();

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

    void SmallOffset(string id) {
        ImGui::InvisibleButton(("smalloffset"+id).c_str(), ImVec2(10.0, Scale(8.0)));
    }

    void RuleTable(cstr id, float* ptr, float min, float max, float speed, cstr fmt) {
        if (ImGui::BeginTable(
            id,
            rule.types+2,
            ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY,
            ImVec2(Scale(180.0), Scale(140.0))
        )) {
            ImGui::TableSetupScrollFreeze(1, 1);
            
            for (int j = -1; j < rule.types; j++) {
                ImGui::TableNextRow();

                if (j >= 0) {
                    ImGui::TableSetColumnIndex(0);

                    ColorLabel(string("##rownames")+id+std::to_string(j), GetTypeColor(j), ImVec2(Scale(28.0), Scale(18.0)));

                    for (uint i = 0; i < rule.types; i++) {
                        ImGui::TableSetColumnIndex(i+1);

                        ImGui::SetNextItemWidth(Scale(30.0));
                        ImGui::DragFloat((string("##")+id+std::to_string(i)+"-"+std::to_string(j)).c_str(), &ptr[i+j*10], speed, min, max, fmt);
                    }
                } else {
                    for (uint i = 0; i < rule.types; i++) {
                        ImGui::TableSetColumnIndex(i+1);

                        ColorLabel(string("##columnnames")+id+std::to_string(i), GetTypeColor(i), ImVec2(Scale(28.0), Scale(18.0)));
                    }
                }
            }

            ImGui::EndTable();
        }
    }
    
    void frame() {
        ImVec2 buttonTiny = ImVec2(Scale(18.0), Scale(18.0));
        ImVec2 buttonShort = ImVec2(Scale(40.0), Scale(18.0));
        ImVec2 buttonMedium = ImVec2(Scale(80.0), Scale(18.0));
        ImVec2 buttonDouble = ImVec2(Scale(160.0)+GUI::style->ItemSpacing.x, Scale(18.0));

        if (!pause) for (uint i = 0; i < stepsperframe; i++) {
            simulation->step(threadcount);

            stepcount++;
        }

        static float colorTone[3] = { 1.0, 1.0, 1.0 };

        if (rendering) {
            render->ppReducing = ppReducing;

            render->render(
                camera, zoom(),
                particlebright,
                (escaping ? vec3(0.5):vec3(1.0))*vec3(colorTone[0], colorTone[1], colorTone[2]),
                glowing,
                escaping
            );
        } else GL::Clear(0.0, 0.0, 0.0);

        if (escaping) {
            ImGui::PushFont(fontMedium[interfacescale]);

            ImGui::Begin("Quit");
            ImGui::Text("Are you sure you really wish to quit the app?");

            if (ImGui::Button("Quit", buttonMedium)) window->close();
            ImGui::SameLine();
            if (ImGui::Button("Stay", buttonMedium)) escaping = false;

            ImGui::End();

            ImGui::PopFont();

            return;
        }

        ImGui::PushFont(fontMedium[interfacescale]);

        ImGui::Begin("Forcell");

        if (ImGui::Button(pause ? "Continue":"Pause", buttonMedium)) pause = !pause;
        ImGui::SameLine();
        if (ImGui::Button("Quit", buttonMedium)) escaping = true;

        ImGui::Text("Time steps: %d", simulation->frame);

        SmallOffset("pre-headers");

        CollapsingHeader("Performance") {
            ImGui::Text("Frames per second: %d", fps);
            ImGui::Text("Steps  per second: %d", sps);

            ImGui::SetNextItemWidth(Scale(100.0));

            ImGui::SliderInt("##stepsperframe", &stepsperframe, 1, 5, stepsperframe == 1 ? "%d step per frame":"%d steps per frame");

            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::InputInt("CPU threads", &threadcount, 1, 8);

            ImGui::Checkbox("Rendering", &rendering);

            CollapsingEnd;
        }

        CollapsingHeader("Appearence") {
            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::SliderFloat("Particles opacity", &particlebright, 0.0, 1.0, "%.2f");

            if (postproc) {
                ImGui::SetNextItemWidth(Scale(120.0));
                ImGui::ColorEdit3("Color tone", colorTone);
            }

            ImGui::Checkbox("Glow effect", &glowing);
            if (ImGui::Checkbox("Fullscreen mode", &fullscreen)) updateFullscreen();
            if (ImGui::Checkbox("Post-processing", &postproc)) recreateRender();

            if (postproc) {
                ImGui::SetNextItemWidth(Scale(120.0));
                ImGui::SliderInt("##resolutionreducing", &ppReducing, 1.0, 5.0, "Resolution reducing x%d");
            }

            ImGui::Text("Interface scale:");
            if (ImGui::RadioButton("x1", &interfacescale, 0)) StyleRescale();
            ImGui::SameLine();
            if (ImGui::RadioButton("x2", &interfacescale, 1)) StyleRescale();
            ImGui::SameLine();
            if (ImGui::RadioButton("x4", &interfacescale, 2)) StyleRescale();

            CollapsingEnd;
        }

        CollapsingHeader("Camera") {
            ImGui::Text("Camera: %.0f:%.0f", -camera.x*simulation->width/2.0, -camera.y*simulation->height/2.0);
            ImGui::SameLine();
            if (ImGui::Button("Reset##resetcamera", buttonMedium)) camera = vec2(0.0, 0.0);

            ImGui::SetNextItemWidth(Scale(60.0));
            ImGui::SliderFloat("##zoom", &zoomsteps, MIN_ZOOM, MAX_ZOOM, "");
            ImGui::SameLine();
            ImGui::Text("Zoom: %.2f", zoom());
            ImGui::SameLine();
            if (ImGui::Button("Reset##resetzoom", buttonMedium)) zoomsteps = 0.0;

            ImGui::SetNextItemWidth(Scale(60.0));
            ImGui::DragFloat("Mouse wheel sensitivity", &wheelsensitivity, 0.05, 0.0, 1000.0, "%.1f");

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

            SmallOffset("rule-pre-params");

            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::InputInt("Number of types", &rule.types, 1, 1);
            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::DragFloat("Friction", &rule.friction, 0.0002, 0.0, 1.0, "%.3f");
            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::DragFloat("Attractor", &rule.attractor, 0.000001, 0.0, 1.0, "%.5f");
            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::DragFloat("Bounce force", &rule.bounceForce, 0.001, 0.0, 1.0, "%.2f");

            SmallOffset("rule-pre-forces");

            CollapsingHeader("Forces") {
                RuleTable("forcetable", rule.forces, -1.0, 1.0, 0.001, "%.2f");

                CollapsingEnd;

                SmallOffset("rule-after-forces");
            }

            CollapsingHeader("Max. interaction distances") {
                RuleTable("zonetable", rule.zones, 0.0, 10000.0, 1.0, "%.0f");

                CollapsingEnd;

                SmallOffset("rule-after-zones");
            }

            CollapsingHeader("Frequencies") {
                for (uint i = 0; i < rule.types; i++) {
                    ImGui::SetNextItemWidth(Scale(100.0));
                    ImGui::DragFloat(("##freqs"+std::to_string(i)).c_str(), &rule.freqs[i], 0.002, 0.0, 10.0, "%.2f");
                    ImGui::SameLine();
                    ColorLabel("##freqsclr"+std::to_string(i), GetTypeColor(i), ImVec2(Scale(60.0), Scale(18.0)));
                }

                if (ImGui::Button("Reset", buttonMedium)) {
                    for (uint i = 0; i < rule.types; i++) rule.freqs[i] = 1.0;
                }

                CollapsingEnd;
            }

            CollapsingEnd;
        }

        CollapsingHeader("Settings") {
            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::DragInt("Simulation size", &params.width, 10.0, 100, 10000);
            params.height = params.width;
            ImGui::SetNextItemWidth(Scale(100.0));
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

            CollapsingEnd;
        }
        
        SmallOffset("pre-copyright");

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
        if (!confignoupdate) SaveConfig();

        cleanup();

        GUI::Destroy();

        delete window;
    }

    void Begin() {
        GUI::Begin(frame);
    }
}