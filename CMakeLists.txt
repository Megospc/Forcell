set(OPTIMIZATIONS ON) # Enable compiler optimizations

cmake_minimum_required(VERSION 3.1)

project(Forcell VERSION 1.10.0)

set(EXECUTABLE "Forcell")

set(CMAKE_CXX_STANDARD 17)

if (${OPTIMIZATIONS})
    add_compile_options(-Ofast -Wno-unused-result)
else()
    add_compile_options(-Og -Wall -Wextra)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)

include_directories("include")

add_executable(${EXECUTABLE} 
    src/Main.cpp
    src/glad.c

    include/ImGUI/imgui.cpp
    include/ImGUI/imgui_draw.cpp
    include/ImGUI/imgui_tables.cpp
    include/ImGUI/imgui_widgets.cpp
    include/ImGUI/imgui_impl_glfw.cpp
    include/ImGUI/imgui_impl_opengl3.cpp
    include/ImGuiFileDialog/ImGuiFileDialog.cpp
)

target_link_libraries(${EXECUTABLE} PRIVATE glfw)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    if (${OPTIMIZATIONS})
        set(CMAKE_CXX_FLAGS "-mwindows -static")
    else()
        set(CMAKE_CXX_FLAGS "-static")
    endif()
endif()

if (${OPTIMIZATIONS})
    target_compile_definitions(${EXECUTABLE} PUBLIC OPTIMIZATIONS_ON)
    target_compile_definitions(${EXECUTABLE} PUBLIC NDEBUG)
endif()