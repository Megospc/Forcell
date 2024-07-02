# Forcell
Forcell is a particle life simulation with new features and GPU computing via OpenCL.

Version: 1.2.0 (02.07.2024)

## Features
+ Multi-threaded computing on CPU
+ Supporting Ubuntu and Windows

## Screenshots
<img src="images/screen1.png" width="600">
<img src="images/screen2.png" width="600">

## How To Run
### What You Need
For Windows:
+ MinGW-W64
+ CMake
+ GNU Make

For Ubuntu, these packages:
+ gcc
+ cmake
+ libgtk-3-dev
+ make

## Steps
1. Download zip-archive with source code.
2. Extract the archive.
3. Open `CMakeLists.txt` in Notepad and configure the settings.
4. (Only for windows) Open `run.bat` and edit compiler and GNU Make paths if needed.
5. Open `run.bat` file (`run.sh` for Ubuntu) in terminal.
6. Wait for compilation to complete.
7. The Forcell's window should open.
8. Then you can open `Forcell.exe` (`Forcell` for Ubuntu) to run it again.

## Dependicies
There are these libraries used in this project:
+ [Dear ImGui](https://github.com/ocornut/imgui)
+ [GLFW 3.4](https://github.com/glfw/glfw)
+ [GLAD](https://github.com/dav1dde/glad-web)
+ [NativeFileDialog Extended](https://github.com/btzy/nativefiledialog-extended)
+ [STB](https://github.com/nothings/stb)
+ [vecpp](https://github.com/Megospc/vecpp)