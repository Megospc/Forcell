set(OPTIMIZATIONS ON) # Enable compiler optimizations

cmake_minimum_required(VERSION 3.1)

project(Forcell VERSION 1.3.0)

set(EXECUTABLE "Forcell")

set(CMAKE_CXX_STANDARD 17)

if (${OPTIMIZATIONS})
    add_compile_options(-Ofast)
else()
    add_compile_options(-Og)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)
add_subdirectory(nfd)

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
)

target_link_libraries(${EXECUTABLE} PRIVATE glfw)
target_link_libraries(${EXECUTABLE} PRIVATE nfd)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(CMAKE_CXX_FLAGS "-mwindows -static")
endif()

if (${OPTIMIZATIONS})
    target_compile_definitions(${EXECUTABLE} PUBLIC OPTIMIZATIONS_ON)
    target_compile_definitions(${EXECUTABLE} PUBLIC NDEBUG)
endif()