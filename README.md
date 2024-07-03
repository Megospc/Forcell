<h1 align="center">🧲 Forcell 🧬</h1>
Forcell is a particle life simulation with new features and GPU computing via OpenCL.

Version: 1.3.0 (03.07.2024)

## ✨ Features
+ Multi-threaded computing on CPU
+ Supporting Ubuntu and Windows
+ Fullscreen mode
+ Create random rules with one click

## 📸 Screenshots
<img src="images/screen1.png" width="600">
<img src="images/screen2.png" width="600">
<img src="images/screen3.png" width="600">

<video src="https://github.com/Megospc/Forcell/assets/97227980/30c19aab-7b5b-4229-ad5a-ef3bfe80a514"></video>

## ▶️ How To Run
### 🔧 What You Need
For Windows:
+ MinGW-W64
+ CMake
+ GNU Make

For Ubuntu, these packages:
+ gcc
+ cmake
+ libgtk-3-dev
+ make

If GPU-computing enabled, the OpenCL SDK is required for both OS.

### 📄 Steps
1. Download zip-archive with source code.
2. Extract the archive.
3. (Only for windows) Open `run.bat` and edit compiler and GNU Make paths if needed.
4. Open `run.bat` file (`run.sh` for Ubuntu) in terminal.
5. Wait for compilation to complete.
6. The Forcell's window should open.
7. Then you can open `Forcell.exe` (`Forcell` for Ubuntu) to run it again.

## 💿 Pre-compiled Binaries
(Only for x64 processors)
You can download pre-compiled binaries in [releases](https://github.com/Megospc/Forcell/releases).

## ⚙️ System Requirements
+ OpenGL 3.3 compatible GPU
+ OpenCL 1.0 compatible GPU (only if GPU-computing enabled)

## 😃 Dependicies
There are these libraries used in this project:
+ [Dear ImGui](https://github.com/ocornut/imgui)
+ [GLFW 3.4](https://github.com/glfw/glfw)
+ [GLAD](https://github.com/dav1dde/glad-web)
+ [NativeFileDialog Extended](https://github.com/btzy/nativefiledialog-extended)
+ [STB](https://github.com/nothings/stb)
+ [vecpp](https://github.com/Megospc/vecpp)

## 🐞 Bug Reporting
If you find any error, please [create](https://github.com/Megospc/Forcell/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=) an Issue about it.