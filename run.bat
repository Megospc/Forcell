cmake -B build -G "MinGW Makefiles"
cmake --build build
xcopy .\build\Forcell.exe .\ /Y
start ./Forcell.exe