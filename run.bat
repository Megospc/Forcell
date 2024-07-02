cmake -B build -G "MinGW Makefiles" -D "CMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe" -D "CMAKE_CXX_COMPILER=C:\msys64\ucrt64\bin\g++.exe" -D "CMAKE_MAKE_PROGRAM=C:\Program Files (x86)\GnuWin32\bin\make.exe"
cmake --build build
xcopy .\build\Forcell.exe .\ /Y
start ./Forcell.exe