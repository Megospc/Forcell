// Some GUI functions

#pragma once

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include "Definitions.h"
#include "Logger.h"
#include "Files.h"
#include "GL.h"

namespace GUI {
    ImGuiIO* io;

    GL::Window* window;

    ImGuiContext* ctx;

    ImGuiStyle* style;

    vec4 ImLerp(vec4 a, vec4 b, float t) {
        return a+(b-a)*t;
    }

    vec4 GetColor(ImGuiCol_ col) {
        ImVec4 v = style->Colors[col];

        return vec4(v.x, v.y, v.z, v.w);
    }

    void SetColor(ImGuiCol_ col, vec4 v) {
        style->Colors[col] = ImVec4(v.x, v.y, v.z, v.w);
    }

    void Style(vec3 base) {
        SetColor(ImGuiCol_Text,                   vec4(1.00, 1.00, 1.00, 1.00));
        SetColor(ImGuiCol_TextDisabled,           vec4(0.50, 0.50, 0.50, 1.00));
        SetColor(ImGuiCol_WindowBg,               vec4(0.06, 0.06, 0.06, 0.94));
        SetColor(ImGuiCol_ChildBg,                vec4(0.00, 0.00, 0.00, 0.00));
        SetColor(ImGuiCol_PopupBg,                vec4(0.08, 0.08, 0.08, 0.94));
        SetColor(ImGuiCol_Border,                 vec4(base*0.1+0.4,     0.50));
        SetColor(ImGuiCol_BorderShadow,           vec4(0.00, 0.00, 0.00, 0.00));
        SetColor(ImGuiCol_FrameBg,                vec4(base,             0.34));
        SetColor(ImGuiCol_FrameBgHovered,         vec4(base,             0.40));
        SetColor(ImGuiCol_FrameBgActive,          vec4(base,             0.57));
        SetColor(ImGuiCol_TitleBg,                vec4(0.06, 0.06, 0.06, 1.00));
        SetColor(ImGuiCol_TitleBgActive,          vec4(base/2.0,         1.00));
        SetColor(ImGuiCol_TitleBgCollapsed,       vec4(base/4.0,         0.51));
        SetColor(ImGuiCol_MenuBarBg,              vec4(0.14, 0.14, 0.14, 1.00));
        SetColor(ImGuiCol_ScrollbarBg,            vec4(0.02, 0.02, 0.02, 0.53));
        SetColor(ImGuiCol_ScrollbarGrab,          vec4(0.31, 0.31, 0.31, 1.00));
        SetColor(ImGuiCol_ScrollbarGrabHovered,   vec4(0.41, 0.41, 0.41, 1.00));
        SetColor(ImGuiCol_ScrollbarGrabActive,    vec4(0.51, 0.51, 0.51, 1.00));
        SetColor(ImGuiCol_CheckMark,              vec4(base*1.2,             1.00));
        SetColor(ImGuiCol_SliderGrab,             vec4(base*0.9,         1.00));
        SetColor(ImGuiCol_SliderGrabActive,       vec4(base,             1.00));
        SetColor(ImGuiCol_Button,                 vec4(base,             0.40));
        SetColor(ImGuiCol_ButtonHovered,          vec4(base,             1.00));
        SetColor(ImGuiCol_ButtonActive,           vec4(base*0.8,         1.00));
        SetColor(ImGuiCol_Header,                 vec4(base,             0.31));
        SetColor(ImGuiCol_HeaderHovered,          vec4(base,             0.80));
        SetColor(ImGuiCol_HeaderActive,           vec4(base,             1.00));
        SetColor(ImGuiCol_Separator,              GetColor(ImGuiCol_Border));
        SetColor(ImGuiCol_TabHovered,             GetColor(ImGuiCol_HeaderHovered));
        SetColor(ImGuiCol_SeparatorHovered,       vec4(base*0.6,         0.78));
        SetColor(ImGuiCol_SeparatorActive,        vec4(base*0.6,         1.00));
        SetColor(ImGuiCol_ResizeGrip,             vec4(base,             0.20));
        SetColor(ImGuiCol_ResizeGripHovered,      vec4(base,             0.67));
        SetColor(ImGuiCol_ResizeGripActive,       vec4(base,             0.95));
        SetColor(ImGuiCol_Tab,                    ImLerp(GetColor(ImGuiCol_Header),       GetColor(ImGuiCol_TitleBgActive), 0.80));
        SetColor(ImGuiCol_TabActive,              ImLerp(GetColor(ImGuiCol_HeaderActive), GetColor(ImGuiCol_TitleBgActive), 0.60));
        SetColor(ImGuiCol_TabUnfocused,           ImLerp(GetColor(ImGuiCol_Tab),          GetColor(ImGuiCol_TitleBg),       0.80));
        SetColor(ImGuiCol_TabUnfocusedActive,     ImLerp(GetColor(ImGuiCol_TabActive),    GetColor(ImGuiCol_TitleBg),       0.40));
        SetColor(ImGuiCol_PlotLines,              vec4(0.61, 0.61, 0.61, 1.00));
        SetColor(ImGuiCol_PlotLinesHovered,       vec4(1.00, 0.43, 0.35, 1.00));
        SetColor(ImGuiCol_PlotHistogram,          vec4(0.90, 0.70, 0.00, 1.00));
        SetColor(ImGuiCol_PlotHistogramHovered,   vec4(1.00, 0.60, 0.00, 1.00));
        SetColor(ImGuiCol_TableHeaderBg,          vec4(base*0.01+0.19,   1.00));
        SetColor(ImGuiCol_TableBorderStrong,      vec4(base*0.04+0.50,   1.00));
        SetColor(ImGuiCol_TableBorderLight,       vec4(base*0.02+0.23,   1.00));
        SetColor(ImGuiCol_TableRowBg,             vec4(0.00, 0.00, 0.00, 0.00));
        SetColor(ImGuiCol_TableRowBgAlt,          vec4(1.00, 1.00, 1.00, 0.06));
        SetColor(ImGuiCol_TextSelectedBg,         vec4(base,             0.35));
        SetColor(ImGuiCol_DragDropTarget,         vec4(1.00, 1.00, 0.00, 0.90));
        SetColor(ImGuiCol_NavHighlight,           vec4(base,              1.00));
        SetColor(ImGuiCol_NavWindowingHighlight,  vec4(1.00, 1.00, 1.00, 0.70));
        SetColor(ImGuiCol_NavWindowingDimBg,      vec4(0.80, 0.80, 0.80, 0.20));
        SetColor(ImGuiCol_ModalWindowDimBg,       vec4(0.80, 0.80, 0.80, 0.35));
    }

    ImWchar fontranges[] = {
        0x0020, 0x0080
    };

    bool Init(GL::Window* glwindow) {
        IMGUI_CHECKVERSION();

        ctx = ImGui::CreateContext();

        ImGui::SetCurrentContext(ctx);

        window = glwindow;

        io = &ImGui::GetIO();

        if (io == NULL) {
            Error("Couldn't init ImGUIO");

            return false;
        }

        style = &ImGui::GetStyle();

        ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);

        ImGui_ImplOpenGL3_Init("#version 130");

        return true;
    }

    void Destroy() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext();
    }

    void (*framefn)(void);
    void (*called)(void) = NULL;

    void frameCallback() {
        if (called) {
            called();
            
            called = NULL;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        framefn();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Begin(void (*callback)(void)) {
        framefn = callback;

        window->begin(frameCallback);
    }

    void Call(void (*callback)(void)) {
        called = callback;
    }

    ImFont* LoadTTF(cstr path, uint size) {
        return io->Fonts->AddFontFromFileTTF(path, size, NULL, fontranges);
    }

    void INI(cstr path) {
        File::Data data = File::Read(path);

        File::Write("imgui.ini", data);

        data.destroy();
    }
}