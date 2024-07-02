# SETTINGS
set(WINDOW_WIDTH 1600) # Initial window width
set(WINDOW_HEIGHT 900) # Initial window height
set(INTERFACE_SCALING 2.0) # Interface scaling

set(POST_PROCESSING ON)

set(FRAMEBUFFER_RESOLUTION_REDUCING 1.0) # Reducing of framebuffer resolution
# (for slow GPU, only if post-processing enabled)
# 1.0 - don't reduce, 2.0 - reduce by 2 times, etc

set(COMPUTING_TYPE "CPU")
# CPU = Use CPU to compute
# GPU = Use OpenCL to compute on GPU (COMING SOON)

set(OPTIMIZATIONS ON) # Enable compiler optimizations






# MAIN CODE
cmake_minimum_required(VERSION 3.1)

project(Forcell VERSION 1.2.0)

set(EXECUTABLE "Forcell")

set(CMAKE_CXX_STANDARD 17)

if (${OPTIMIZATIONS})
    set(CMAKE_CXX_FLAGS "-Ofast")
else()
    set(CMAKE_CXX_FLAGS "-Og")
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

# Adding definitions
if (${FULL_SCREEN})
    target_compile_definitions(${EXECUTABLE} PUBLIC FULLSCREEN)
endif()

target_compile_definitions(${EXECUTABLE} PUBLIC WINDOW_WIDTH=${WINDOW_WIDTH})
target_compile_definitions(${EXECUTABLE} PUBLIC WINDOW_HEIGHT=${WINDOW_HEIGHT})
target_compile_definitions(${EXECUTABLE} PUBLIC INTERFACE_SCALE=${INTERFACE_SCALING})
target_compile_definitions(${EXECUTABLE} PUBLIC WHEEL_STEP=${WHEEL_SENSITIVITY})

if (${POST_PROCESSING})
    target_compile_definitions(${EXECUTABLE} PUBLIC POSTPROCESSING)
    target_compile_definitions(${EXECUTABLE} PUBLIC FRAMEBUFFER_REDUCING=${FRAMEBUFFER_RESOLUTION_REDUCING})
endif()

if ("${COMPUTING_TYPE}" STREQUAL "CPU")
    target_compile_definitions(${EXECUTABLE} PUBLIC SIMULATION_THREADS=${THREADS_COUNT})
endif()

if (${OPTIMIZATIONS})
    target_compile_definitions(${EXECUTABLE} PUBLIC OPTIMIZATIONS_ON)
    target_compile_definitions(${EXECUTABLE} PUBLIC NDEBUG)
endif()