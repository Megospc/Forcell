cmake -B build -G "Unix Makefiles"
cmake --build build
cp ./build/Forcell ./Forcell
./Forcell