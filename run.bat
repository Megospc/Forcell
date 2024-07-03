cmake -B build -G "MinGW Makefiles" -D "CMAKE_C_COMPILER=gcc" -D "CMAKE_CXX_COMPILER=g++" -D "CMAKE_MAKE_PROGRAM=make"
cmake --build build
xcopy .\build\Forcell.exe .\ /Y
start ./Forcell.exe