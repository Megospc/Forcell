// Working with files

#pragma once

#include <fstream>
#include <filesystem>

#include "Definitions.h"
#include "GUI.h"

namespace File {
    namespace fs = std::filesystem;

    struct Data {
        char* data;

        size_t length;

        void destroy() {
            free(data);
        }
    };

    Data Read(cstr path, bool zeroend = false) {
        FILE* file;
        size_t length;
        
        file = fopen(path, "rb");

        // Getting length:
        fseek(file, 0, SEEK_END);
        length = ftell(file)+(zeroend ? 1:0);
        rewind(file);

        char* data = MALLOC(char, length);
        size_t r = fread(data, 1, length, file);

        if (zeroend) data[length-1] = '\0';

        fclose(file);

        Data result;

        result.data = data;
        result.length = length;

        return result;
    }

    bool Write(cstr path, Data data) {
        std::ofstream stream(path);

        if (!stream) return false;

        stream.write(data.data, data.length);

        stream.close();

        return true;
    }
}