// Image loader using stb_image

#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include "Definitions.h"
#include "GL.h"

namespace Img {
    struct Data {
        uint8_t* data;

        uint width, height;
        uint channels;

        bool needdestroy = false;

        void destroy() {
            if (needdestroy) free(data);
            else stbi_image_free(data);
        }
    };

    Data Load(cstr path) {
        int width, height, channels;

        Data result;

        result.data = stbi_load(path, &width, &height, &channels, 0);

        result.width = width;
        result.height = height;
        result.channels = channels;

        return result;
    }

    GL::Texture2D* Texture(cstr path) {
        Data data = Load(path);

        GL::Texture2D* texture = new GL::Texture2D();

        texture->bind();
        texture->filter(GL_LINEAR);
        texture->wrap(GL_CLAMP_TO_BORDER);
        texture->border({ 0.0, 0.0, 0.0, 0.0 });
        texture->data(data.data, data.width, data.height, data.channels == 4 ? GL_RGBA:GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE);
        texture->unbind();

        data.destroy();

        return texture;
    }

    Data Square(Data img) {
        uint max = MAX(img.width, img.height);

        uint offsetX = (max-img.width)/2;
        uint offsetY = (max-img.height)/2;

        Data result;

        result.width = max;
        result.height = max;

        uint length = max*max*4;

        result.data = MALLOC(uint8_t, length);

        for (uint i = 0; i < length; i++) result.data[i] = 0;

        result.needdestroy = true;

        for (uint x = 0; x < img.width; x++) for (uint y = 0; y < img.height; y++) {
            uint i = ((x+offsetX)+(y+offsetY)*max)*4;
            uint j = (x+y*img.width)*4;

            result.data[i] = img.data[j];
            result.data[i+1] = img.data[j+1];
            result.data[i+2] = img.data[j+2];
            result.data[i+3] = img.data[j+3];
        }

        return result;
    }

    GLFWimage ToGLFW(Data img) {
        GLFWimage result;

        result.width = img.width;
        result.height = img.height;
        result.pixels = img.data;

        return result;
    }
}