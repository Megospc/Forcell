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

    GLFWimage ToGLFW(Data img) {
        GLFWimage result;

        result.width = img.width;
        result.height = img.height;
        result.pixels = img.data;

        return result;
    }
}