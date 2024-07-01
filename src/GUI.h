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

    bool Init(GL::Window* glwindow, bool dark = true) {
        IMGUI_CHECKVERSION();

        ctx = ImGui::CreateContext();

        ImGui::SetCurrentContext(ctx);

        window = glwindow;

        io = &ImGui::GetIO();

        if (io == NULL) {
            Error("Couldn't init ImGUIO");

            return false;
        }

        io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // Setup style
        if (dark) ImGui::StyleColorsDark();
        else ImGui::StyleColorsLight();

        style = &ImGui::GetStyle();

        style->FrameRounding = 10.0;
        style->GrabRounding = 10.0;
        style->WindowRounding = 10.0;

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

    void frameCallback() {
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

    ImFont* LoadTTF(cstr path, uint size) {
        return io->Fonts->AddFontFromFileTTF(path, size);
    }

    void INI(cstr path) {
        File::Data data = File::Read(path);

        File::Write("imgui.ini", data);

        data.destroy();
    }
}