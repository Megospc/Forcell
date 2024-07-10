#pragma once

#define FONT_PATH "assets/Reef/Reef.ttf"

#define ZOOM_STEP 1.01
#define MAX_ZOOM 150.0
#define MIN_ZOOM -30.0
#define CAMERA_STEP 0.1

#include "GUI.h"
#include "Input.h"
#include "Simulation.h"
#include "Render.h"
#include "Files.h"
#include "Images.h"
#include "Saver.h"

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
    bool rulemetawindow = false;
    bool rulesavewindow = false;

    bool windowperformance = false;
    bool windowappearance = false;
    bool windowcamera = false;
    bool windowmousetool = false;
    bool windowrule = false;
    bool windowsettings = false;
    bool windowbuildinfo = false;

    Simulation::Simulation* simulation = nullptr;
    Render::Render* render = nullptr;

    Simulation::Params params;
    Simulation::Rule rule;

    string creatorname = "";

    uint fps = 60, sps = 60;
    uint lastsecond;
    uint framecount = 0, stepcount = 0;
    int stepsperframe = 1;
    int threadcount = 1;
    uint windowwidth = 1600;
    uint windowheight = 900;
    int mousetool = 1;

    vec2 camera;
    float zoomsteps;
    float wheelsensitivity = 20.0;
    int interfacescale = 1;
    int ppReducing = 3.0;

    float speedup = 1.0;

    float Scale(float size, int scale = interfacescale) {
        if (scale == 0) return size;
        if (scale == 1) return size*1.5;
        if (scale == 2) return size*2;
        if (scale == 3) return size*4;

        return size;
    }

    float particleopacity = 1.0;
    float connectionopacity = 1.0;
    float particlesize = 1.0;
    float particleglow = 1.0;
    float particlehole = 1.0;
    float connectionwidth = 1.0;

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

    vec2 mousesim() {
        return (getsimpos(mousepos)+1.0-camera)/2.0*simsize();
    }

    void updatemouse() {
        mousepos = (Input::GetMouse()/scrsize()*2.0-1.0)*vec2(1.0, -1.0);
    }

    void updatecamera() {
        camera = scamera+(getsimpos(mousepos)-smouse);
    }

    void mousemove(float x, float y) {
        updatemouse();

        if (mousedown && mousetool == 1) updatecamera();
    }

    void mousestart() {
        updatemouse();

        mousedown = true;
        scamera = camera;
        smouse = getsimpos(mousepos);
    }

    void mouseend() {
        updatemouse();

        if (mousetool == 1) updatecamera();

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

    bool keyshift = false;

    void keyboard(ImGuiKey key, int action) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (key == ImGuiKey_Minus) zoomsteps -= 10.0;
            if (key == ImGuiKey_Equal) zoomsteps += 10.0;

            SCLAMP(zoomsteps, MIN_ZOOM, MAX_ZOOM);

            if (!mousedown) {
                float step = keyshift ? CAMERA_STEP/10.0:CAMERA_STEP/zoom();

                if (key == ImGuiKey_LeftArrow) camera.x += step;
                if (key == ImGuiKey_RightArrow) camera.x -= step;
                if (key == ImGuiKey_DownArrow) camera.y += step;
                if (key == ImGuiKey_UpArrow) camera.y -= step;
            }
            
            if (key == ImGuiKey_S) stepsperframe--;
            if (key == ImGuiKey_F) stepsperframe++;
            SCLAMP(stepsperframe, 1, 5);
        }

        if (action == GLFW_PRESS) {
            if (key == ImGuiKey_Escape) escaping = true;

            if (key == ImGuiKey_Space || key == ImGuiKey_P) pause = !pause;

            if (key == ImGuiKey_O || key == ImGuiKey_I) camera = vec2(0.0, 0.0);
            if (key == ImGuiKey_O || key == ImGuiKey_0) zoomsteps = 0.0;

            if (key == ImGuiKey_R) start();

            if (key == ImGuiKey_N) {
                rule.random(seed());

                start();
            }

            if (key == ImGuiKey_F11) {
                fullscreen = !fullscreen;

                updateFullscreen();
            }

            if (key == ImGuiKey_LeftShift) keyshift = true;

            if (key == ImGuiKey_1) mousetool = 1;
            if (key == ImGuiKey_2) mousetool = 2;
        }

        if (action == GLFW_RELEASE) {
            if (key == ImGuiKey_LeftShift) keyshift = false;
        }
    }

    string scalestr(int scale) {
        switch (scale) {
            case 0: return "x1";
            case 1: return "x1.5";
            case 2: return "x2";
            case 3: return "x4";
        }

        return "x1.5";
    }

    int strscale(string str) {
        if (str == "x1") return 0;
        if (str == "x1.5") return 1;
        if (str == "x2") return 2;
        if (str == "x4") return 3;

        return 1;
    }

    void SaveConfig() {
        string str = "";

        if (fullscreen) str += KeyVal("fullscreen", "");
        if (glowing) str += KeyVal("glowing", "");
        if (postproc) str += KeyVal("postprocessing", "");
        
        if (windowperformance) str += KeyVal("window-performance", "");
        if (windowappearance) str += KeyVal("window-appearance", "");
        if (windowcamera) str += KeyVal("window-camera", "");
        if (windowmousetool) str += KeyVal("window-mousetool", "");
        if (windowrule) str += KeyVal("window-rule", "");
        if (windowsettings) str += KeyVal("window-settings", "");
        if (windowbuildinfo) str += KeyVal("window-buildinfo", "");

        if (creatorname.length() > 0) str += KeyVal("creator", creatorname);

        str += KeyVal("threads", threadcount);
        str += KeyVal("wheel", wheelsensitivity);
        str += KeyVal("width", windowwidth);
        str += KeyVal("height", windowheight);
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

        windowperformance = false;
        windowappearance = false;
        windowcamera = false;
        windowmousetool = false;
        windowrule = false;
        windowsettings = false;
        windowbuildinfo = false;

        creatorname = "";

        string str = data.data;

        string line = "";

        for (uint i = 0; i < str.length(); i++) {
            char c = str[i];

            if (c == '\n') {
                KeyVal data(line);
                
                if (data.key == "fullscreen") fullscreen = true;
                if (data.key == "glowing") {glowing = true;Log(8888);}
                if (data.key == "postprocessing") postproc = true;

                if (data.key == "window-performance") windowperformance = true;
                if (data.key == "window-appearance") windowappearance = true;
                if (data.key == "window-camera") windowcamera = true;
                if (data.key == "window-mousetool") windowmousetool = true;
                if (data.key == "window-rule") windowrule = true;
                if (data.key == "window-settings") windowsettings = true;
                if (data.key == "window-buildinfo") windowbuildinfo = true;

                if (data.key == "noupdate") confignoupdate = true;

                if (data.key == "threads") threadcount = stoi(data.val);
                if (data.key == "wheel") wheelsensitivity = stof(data.val);
                if (data.key == "pp-reducing") ppReducing = stoi(data.val);
                if (data.key == "width") windowwidth = stoi(data.val);
                if (data.key == "height") windowheight = stoi(data.val);
                if (data.key == "interface") interfacescale = strscale(data.val);

                if (data.key == "creator") creatorname = data.val;

                line = "";
            } else {
                if (c != '\r') line += c;
            }
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

        if (!window->isOk()) return false;

        if (!GUI::Init(window)) return false;

        { // Load icon
            Img::Data raw = Img::Load("assets/icon.png");

            Img::Data squared = Img::Square(raw);

            GLFWimage image = Img::ToGLFW(squared);

            window->icon(&image);

            squared.destroy();
            raw.destroy();
        }

        for (uint i = 0; i < 4; i++) {
            fontMedium[i] = GUI::LoadTTF(FONT_PATH, Scale(16.0, i));
        }

        Input::Window(window);
        Input::Keyboard(keyboard);
        Input::MouseMove(mousemove);
        Input::MouseButton(mousebtn);
        Input::MouseWheel(mousewheel);

        StyleRescale();

        rule.types = 6;
        rule.random(seed());

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

    void DragFloat(cstr label, float* v, float speed, float min, float max, cstr fmt = "%.2f") {
        ImGui::DragFloat(label, v, speed, min, max, fmt);
        SCLAMP(*v, min, max);
    }
    void DragInt(cstr label, int* v, float speed, int min, int max, cstr fmt = "%d") {
        ImGui::DragInt(label, v, speed, min, max, fmt);
        SCLAMP(*v, min, max);
    }

    ImVec2 TableSize() {
        return ImVec2(
            ImGui::GetWindowContentRegionMax().x-50.0,
            Scale(150.0)
        );
    }

    void RuleTable(cstr id, float* ptr, float min, float max, float speed, cstr fmt, bool forces = false) {
        if (ImGui::BeginTable(
            id,
            rule.types+2,
            ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY,
            TableSize()
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

                        if (forces) {
                            float v = CLAMPMAX(ptr[i+j*10], 1.0);

                            float r = v < 0.0 ? -v : v/3.0;
                            float g = v > 0.0 ? v : -v/3.0;
                            float b = ABS(v)/3.0;

                            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(r, g, b, 0.7));
                            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(r, g, b, 0.8));
                            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(r, g, b, 1.0));
                        }

                        DragFloat((string("##")+id+std::to_string(i)+"-"+std::to_string(j)).c_str(), &ptr[i+j*10], speed, min, max, fmt);

                        if (forces) ImGui::PopStyleColor(3);
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

    void KeyHint(string key, float offset = 0.0) {
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x-Scale(15.0+offset));
        ImGui::TextColored(ImVec4(1.0, 1.0, 1.0, 0.3), key.c_str());
    }

    void WarnText(cstr text) {
        ImGui::TextColored(ImVec4(1.0, 1.0, 0.2, 1.0), text);
    }
    
    void frame() {
        ImVec2 buttonTiny = ImVec2(Scale(18.0), Scale(18.0));
        ImVec2 buttonShort = ImVec2(Scale(40.0), Scale(18.0));
        ImVec2 buttonMedium = ImVec2(Scale(80.0), Scale(18.0));
        ImVec2 buttonDouble = ImVec2(Scale(160.0)+GUI::style->ItemSpacing.x, Scale(18.0));

        static float shoveforce = 100.0;
        static float shoveradius = 100.0;

        if (!pause) for (uint i = 0; i < stepsperframe; i++) {
            if (mousetool == 2 && mousedown) {
                vec2 pos = mousesim();

                simulation->shove(pos.x, pos.y, shoveradius, shoveforce);
            }

            simulation->step(threadcount, speedup);

            stepcount++;
        }

        static float colorTone[3] = { 1.0, 1.0, 1.0 };

        if (rendering) {
            render->ppReducing = ppReducing;

            render->render(
                camera, zoom(),
                particleopacity,
                particlesize,
                particleglow,
                particlehole,
                connectionopacity,
                connectionwidth,
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

        if (rulemetawindow) {
            ImGui::Begin("Rule metadata", &rulemetawindow);

            ImGui::Text("Name: %s", rule.name);
            ImGui::Text("Creator: %s", rule.creator);
            ImGui::Text("Last update: %s", rule.lastupdate);

            SmallOffset("rule-metadata-preok");

            if (ImGui::Button("OK", buttonMedium)) rulemetawindow = false;

            ImGui::End();
        }

        if (rulesavewindow) {
            ImGui::Begin("Saving rule", &rulemetawindow);

            ImGui::Text("Name: ");
            ImGui::SetNextItemWidth(Scale(120.0));
            ImGui::InputText("##rulename", rule.name, 256);
            ImGui::Text("Creator: ");
            ImGui::SetNextItemWidth(Scale(120.0));
            ImGui::InputText("##rulecreator", rule.creator, 256);

            SmallOffset("rule-save-prebtn");

            if (ImGui::Button("Save", buttonMedium)) {
                creatorname = string(rule.creator);

                Saver::Save(&rule);

                rulesavewindow = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", buttonMedium)) rulesavewindow = false;

            ImGui::End();
        }

        ImGui::Begin("Forcell");

        if (ImGui::Button(pause ? "Continue":"Pause", buttonMedium)) pause = !pause;
        ImGui::SameLine();
        if (ImGui::Button("Quit", buttonMedium)) escaping = true;
        KeyHint("[space]", 20.0);

        ImGui::Text("Time steps: %d", simulation->frame);

        SmallOffset("pre-headers");

        ImGui::Checkbox("Performance", &windowperformance);
        ImGui::Checkbox("Appearance", &windowappearance);
        ImGui::Checkbox("Camera", &windowcamera);
        ImGui::Checkbox("Mouse tool", &windowmousetool);
        ImGui::Checkbox("Rule", &windowrule);
        ImGui::Checkbox("Settings", &windowsettings);
        ImGui::Checkbox("Build info", &windowbuildinfo);
        
        SmallOffset("pre-copyright");

        ImGui::Text("Copyright (c) 2024 Megospc");
        
        ImGui::End();

        if (windowperformance) {
            ImGui::Begin("Performance", &windowperformance);

            ImGui::Text("Frames per second: %d", fps);
            ImGui::Text("Steps  per second: %d", sps);
            
            KeyHint("[D]");

            ImGui::SetNextItemWidth(Scale(100.0));

            ImGui::SliderInt("##stepsperframe", &stepsperframe, 1, 5, stepsperframe == 1 ? "%d step per frame":"%d steps per frame");
            KeyHint("[S][F]", 10.0);
            
            SmallOffset("pre-threads");

            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::InputInt("CPU threads", &threadcount, 1, 8);
            SCLAMP(threadcount, 1, MAX_SIMULATION_THREADS);

            SmallOffset("pre-speedup");

            ImGui::SetNextItemWidth(Scale(50.0));
            DragFloat("Speed-up", &speedup, 0.0005, 1.0, 2.0, "x%.1f");
            ImGui::SameLine();
            WarnText("unrecommended");

            ImGui::End();
        }

        if (windowappearance) {
            ImGui::Begin("Appearance", &windowappearance);

            ImGui::Checkbox("Rendering", &rendering);

            if (rendering) {
                ImGui::SetNextItemWidth(Scale(100.0));
                ImGui::SliderFloat("Particle opacity", &particleopacity, 0.0, 1.0, "%.2f");
                ImGui::SetNextItemWidth(Scale(100.0));
                ImGui::SliderFloat("Particle glowing", &particleglow, 0.0, 1.0, "%.2f");
                ImGui::SetNextItemWidth(Scale(100.0));
                ImGui::SliderFloat("Particle size", &particlesize, 0.2, 1.0, "%.2f");
                ImGui::SetNextItemWidth(Scale(100.0));
                ImGui::SliderFloat("Particle hole", &particlehole, 0.0, 1.0, "%.2f");
                ImGui::SetNextItemWidth(Scale(100.0));
                ImGui::SliderFloat("Connection opacity", &connectionopacity, 0.0, 1.0, "%.2f");
                ImGui::SetNextItemWidth(Scale(100.0));
                ImGui::SliderFloat("Connection width", &connectionwidth, 0.0, 1.0, "%.2f");

                ImGui::Checkbox("Addition effect", &glowing);
                if (ImGui::Checkbox("Post-processing", &postproc)) recreateRender();

                if (postproc) {
                    ImGui::SetNextItemWidth(Scale(120.0));
                    ImGui::SliderInt("##resolutionreducing", &ppReducing, 1.0, 5.0, "Resolution reducing x%d");

                    ImGui::SetNextItemWidth(Scale(120.0));
                    ImGui::ColorEdit3("Color tone", colorTone);
                }
            }

            ImGui::Text("Interface scale:");
            if (ImGui::RadioButton("x1", &interfacescale, 0)) StyleRescale();
            ImGui::SameLine();
            if (ImGui::RadioButton("x1.5", &interfacescale, 1)) StyleRescale();
            ImGui::SameLine();
            if (ImGui::RadioButton("x2", &interfacescale, 2)) StyleRescale();
            ImGui::SameLine();
            if (ImGui::RadioButton("x4", &interfacescale, 3)) StyleRescale();

            if (ImGui::Checkbox("Fullscreen mode", &fullscreen)) updateFullscreen();
            KeyHint("[F11]", 10.0);

            ImGui::End();
        }

        if (windowcamera) {
            ImGui::Begin("Camera", &windowcamera);

            ImGui::Text("Camera: %.0f:%.0f", -camera.x*simulation->width/2.0, -camera.y*simulation->height/2.0);
            ImGui::SameLine(ImGui::GetWindowWidth()-buttonMedium.x-GUI::style->ItemSpacing.x);
            if (ImGui::Button("Reset##resetcamera", buttonMedium)) camera = vec2(0.0, 0.0);

            ImGui::SetNextItemWidth(Scale(60.0));
            ImGui::SliderFloat("##zoom", &zoomsteps, MIN_ZOOM, MAX_ZOOM, "");
            ImGui::SameLine();
            ImGui::Text("Zoom: %.2f", zoom());
            ImGui::SameLine(ImGui::GetWindowWidth()-buttonMedium.x-GUI::style->ItemSpacing.x);
            if (ImGui::Button("Reset##resetzoom", buttonMedium)) zoomsteps = 0.0;

            ImGui::SetNextItemWidth(Scale(60.0));
            DragFloat("Mouse wheel sensitivity", &wheelsensitivity, 0.05, 0.0, 1000.0, "%.1f");

            if (ImGui::Button("Go to center", buttonMedium)) camera = vec2(0.0, 0.0), zoomsteps = 0.0;
            KeyHint("[O]");

            ImGui::End();
        }

        if (windowmousetool) {
            ImGui::Begin("Mouse tool", &windowmousetool);

            ImGui::RadioButton("Move camera", &mousetool, 1);
            KeyHint("[1]");
            ImGui::RadioButton("Shove out", &mousetool, 2);
            KeyHint("[2]");

            if (mousetool == 2) {
                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Radius", &shoveradius, 0.1, 0.0, 10000.0, "%.0f");
                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Force", &shoveforce, 0.1, 0.0, 1000.0, "%.1f");
            }

            ImGui::End();
        }

        if (windowrule) {
            ImGui::Begin("Rule", &windowrule);

            if (ImGui::Button("Export", buttonMedium)) {
                writeStringToChar(rule.creator, creatorname);
                rulesavewindow = true;
            }

            ImGui::SameLine();

            if (ImGui::Button("Import", buttonMedium)) {
                Saver::Open(&rule);
                rulemetawindow = true;
                start();
            }

            if (ImGui::Button("Randomize", buttonDouble)) {
                rule.random(seed());
                start();
            }
            KeyHint("[N]");

            SmallOffset("rule-pre-params");

            ImGui::SetNextItemWidth(Scale(100.0));
            ImGui::InputInt("Number of types", &rule.types, 1, 1);
            ImGui::SetNextItemWidth(Scale(100.0));
            DragFloat("Friction", &rule.friction, 0.0002, 0.0, 1.0, "%.3f");
            ImGui::SetNextItemWidth(Scale(100.0));
            DragFloat("Attractor", &rule.attractor, 0.000001, 0.0, 1.0, "%.5f");
            ImGui::SetNextItemWidth(Scale(100.0));
            DragFloat("Bounce force", &rule.bounceForce, 0.001, 0.0, 1.0, "%.2f");
            ImGui::SetNextItemWidth(Scale(100.0));
            DragFloat("Mass spread", &rule.massSpread, 0.0003, 0.0, 1.0, "%.2f");

            SmallOffset("rule-pre-forces");

            CollapsingHeader("Force type") {
                ImGui::RadioButton("Forcell (exclusive)", &rule.forcetype, 0);
                ImGui::RadioButton("Particle life (classic)", &rule.forcetype, 2);
                ImGui::RadioButton("Constant (unstandard)", &rule.forcetype, 1);

                CollapsingEnd;
            }

            CollapsingHeader("Forces") {
                RuleTable("forcetable", rule.forces, -2.0, 2.0, 0.001, "%.2f", true);

                CollapsingEnd;

                SmallOffset("rule-after-forces");
            }

            CollapsingHeader("Interaction distances") {
                RuleTable("zonetable", rule.zones, 0.0, 10000.0, 1.0, "%.0f");

                CollapsingEnd;

                SmallOffset("rule-after-zones");
            }

            ImGui::Checkbox("Second force table", &rule.secondtable);

            if (rule.secondtable) {
                CollapsingHeader("Forces 2") {
                    RuleTable("forcetable2", rule.forces2, -4.0, 4.0, 0.001, "%.2f", true);

                    CollapsingEnd;

                    SmallOffset("rule-after-forces2");
                }

                CollapsingHeader("Interaction distances 2") {
                    RuleTable("zonetable2", rule.zones2, 0.0, 10000.0, 1.0, "%.0f");

                    CollapsingEnd;

                    SmallOffset("rule-after-zones2");
                }
            }

            CollapsingHeader("Frequencies") {
                for (uint i = 0; i < rule.types; i++) {
                    ImGui::SetNextItemWidth(Scale(100.0));
                    DragFloat(("##freqs"+std::to_string(i)).c_str(), &rule.freqs[i], 0.002, 0.0, 10.0, "%.2f");
                    ImGui::SameLine();
                    ColorLabel("##freqsclr"+std::to_string(i), GetTypeColor(i), ImVec2(Scale(60.0), Scale(18.0)));
                }

                if (ImGui::Button("Reset", buttonMedium)) {
                    for (uint i = 0; i < rule.types; i++) rule.freqs[i] = 1.0;
                }

                CollapsingEnd;
            }

            CollapsingHeader("Connections") {
                WarnText("Beta Feature: The following data will not be saved in the rule file!");

                ImGui::Checkbox("Connections", &rule.connections);

                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Attraction strength", &rule.connectionAttraction, 0.0001, 0.0, 0.1, "%.3f");
                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Replusion strength", &rule.connectionReplusion, 0.0001, 0.0, 0.1, "%.3f");
                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Connection distance", &rule.connectionDistance, 0.1, 0.0, 10000.0, "%.0f");
                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Normal length", &rule.connectionNormal, 0.1, 0.0, 10000.0, "%.0f");
                ImGui::SetNextItemWidth(Scale(60.0));
                DragFloat("Max length", &rule.connectionMax, 0.1, 0.0, 10000.0, "%.0f");

                if (ImGui::BeginTable(
                    "connectiontable",
                    5+2, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY,
                    TableSize()
                )) {
                    ImGui::TableSetupScrollFreeze(1, 1);
            
                    for (int j = -1; j < rule.types; j++) {
                        ImGui::TableNextRow();

                        if (j >= 0) {
                            ImGui::TableSetColumnIndex(0);

                            ColorLabel(string("##rownamesconnections")+std::to_string(j), GetTypeColor(j), ImVec2(Scale(28.0), Scale(18.0)));

                            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, Scale(1.0));
                            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(Scale(3.0), 0.0));

                            for (uint i = 0; i < 5; i++) {
                                ImGui::TableSetColumnIndex(i+1);

                                ImGui::InvisibleButton(
                                    (string("##connections")+std::to_string(i)+"-"+std::to_string(j)).c_str(),
                                    ImVec2(Scale(5.0), 1.0)
                                );
                                ImGui::SameLine();

                                ImGui::SetNextItemWidth(Scale(30.0));

                                for (uint k = 0; k < 2; k++) {
                                    int* ptr = &rule.connectionsPriority[j*10+i*2+k];

                                    ImVec4 clr = *ptr == -1 ? ImVec4(1.0, 1.0, 1.0, 0.2):GetTypeColor(*ptr);

                                    ImVec4 clrDefault = clr;
                                    clrDefault.w *= 0.5;
                                    ImVec4 clrActive = clrDefault;
                                    clrActive.w += 0.2;
                                    ImVec4 clrHover = clrDefault;
                                    clrHover.w += 0.4;

                                    ImGui::PushStyleColor(ImGuiCol_FrameBg, clrDefault);
                                    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, clrActive);
                                    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, clrHover);
                                    
                                    ImGui::SetNextItemWidth(Scale(15.0));
                                    DragInt((string("##connections")+std::to_string(i)+"-"+std::to_string(j)+"-"+std::to_string(k)).c_str(), ptr, 0.02, -2, rule.types, *ptr == -1 || *ptr == rule.types ? "-":"%d");
                                    ImGui::SameLine();

                                    if (*ptr == rule.types) *ptr = -1;
                                    if (*ptr == -2) *ptr = rule.types-1;

                                    ImGui::PopStyleColor(3);
                                }

                                ImGui::InvisibleButton(
                                    (string("##connections")+std::to_string(i)+"-"+std::to_string(j)).c_str(),
                                    ImVec2(Scale(5.0), 1.0)
                                );
                            }

                            ImGui::PopStyleVar(2);
                        } else {
                            for (uint i = 0; i < 5; i++) {
                                ImGui::TableSetColumnIndex(i+1);

                                ImGui::Text("Slot %d", i+1);
                            }
                        }
                    }

                    ImGui::EndTable();
                }

                if (ImGui::Button("Clear", buttonDouble)) {
                    for (uint i = 0; i < 100; i++) rule.connectionsPriority[i] = -1;
                }

                CollapsingEnd;
            }

            ImGui::End();
        }

        if (windowsettings) {
            ImGui::Begin("Settings", &windowsettings);

            ImGui::SetNextItemWidth(Scale(100.0));
            DragInt("Simulation size", &params.width, 5.0, 100, 10000);
            params.height = params.width;
            ImGui::SetNextItemWidth(Scale(100.0));
            DragInt("Number of particles", &params.particles, 5.0, 0, 100000);

            if (ImGui::Button("Restart", buttonMedium)) start();
            KeyHint("[R]");

            ImGui::End();
        }

        rule.clamp();
        params.clamp();

        if (windowbuildinfo) {
            ImGui::Begin("Build info", &windowbuildinfo);

            ImGui::BulletText(VERSION);

            #ifdef OPTIMIZATIONS_ON
            ImGui::BulletText("Optimizations enabled");
            #else
            ImGui::BulletText("Optimizations disabled (debug build)");
            #endif

            ImGui::End();
        }

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

        if (!fullscreen) {
            windowwidth = window->getWidth();
            windowheight = window->getHeight();
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