// Simulation renderer class

#pragma once

#include "GL.h"
#include "Simulation.h"
#include "Files.h"

#ifndef FRAMEBUFFER_REDUCING
#define FRAMEBUFFER_REDUCING 1.0
#endif

#define MAX_BUFFER_RESIZE_RATE 80

namespace Render {
    GLfloat baseColors[] = {
        1.0, 0.5, 0.75, // Red-blue
        0.75, 0.5, 1.0, // Blue-purple
        0.5, 1.0, 0.6, // Green
        1.0, 0.8, 0.4, // Yellow
        0.5, 0.9, 1.0, // Sky-blue
        1.0, 0.5, 0.3, // Orange
        0.4, 0.4, 1.0, // Deep blue
        0.75, 1.0, 0.5, // Yellow-green
        1.0, 0.35, 0.3, // Red
        0.8, 0.8, 0.8 // White
    };

    GLfloat vertices[] = {
        -1.0, -1.0,
        1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0,
        -1.0, 1.0
    };

    GL::Program* loadProgram(cstr vertex, cstr fragment, cstr name) {
        File::Data vertexData = File::Read(vertex, true);
        File::Data fragmentData = File::Read(fragment, true);

        GL::Program* result = new GL::Program(vertexData.data, fragmentData.data, name);

        vertexData.destroy();
        fragmentData.destroy();

        return result;
    }

    class Render {
        public:
            Render(GL::Window* window, Simulation::Simulation* simulation) {
                this->window = window;
                this->simulation = simulation;

                GL_DEBUG_MARKER("start");

                programParticle = loadProgram(
                    "shaders/particle-vertex.glsl",
                    "shaders/particle-fragment.glsl"
                , "particle");

                if (!programParticle->isOk()) goto unsuccess;

                GL_DEBUG_MARKER("created programParticle");

                programFiller = loadProgram(
                    "shaders/filler-vertex.glsl",
                    "shaders/filler-fragment.glsl"
                , "filler");

                if (!programFiller->isOk()) goto unsuccess;

                GL_DEBUG_MARKER("created programFiller");

                #ifdef POSTPROCESSING
                programRender = loadProgram(
                    "shaders/filltex-vertex.glsl",
                    "shaders/render-fragment.glsl"
                , "render");

                if (!programRender->isOk()) goto unsuccess;

                GL_DEBUG_MARKER("created programRender");

                programPost1 = loadProgram(
                    "shaders/filltex-vertex.glsl",
                    "shaders/post1-fragment.glsl"
                , "render");

                if (!programPost1->isOk()) goto unsuccess;

                GL_DEBUG_MARKER("created programPost1");

                programPost2 = loadProgram(
                    "shaders/filltex-vertex.glsl",
                    "shaders/post2-fragment.glsl"
                , "render");

                if (!programPost2->isOk()) goto unsuccess;

                GL_DEBUG_MARKER("created programPost2");

                renderTexture1 = new GL::Texture2D();
                renderTexture2 = new GL::Texture2D();
                #endif

                particleVAO = new GL::VertexArray();
                quadVAO = new GL::VertexArray();

                vertexBuffer = new GL::AttribBuffer();
                positionBuffer = new GL::AttribBuffer();
                sizeBuffer = new GL::AttribBuffer();
                typeBuffer = new GL::AttribBuffer();
                quadVertexBuffer = new GL::AttribBuffer();

                GL_DEBUG_MARKER("created objects");

                particleVAO->bind();

                vertexBuffer->bind();
                vertexBuffer->setLocation(0);
                vertexBuffer->enable(2, GL_FLOAT, sizeof(GLfloat));
                vertexBuffer->data(vertices, sizeof(vertices), GL_STATIC_DRAW);
                vertexBuffer->unbind();

                positionBuffer->bind();
                positionBuffer->setLocation(1);
                positionBuffer->enable(2, GL_FLOAT, sizeof(float), 0, sizeof(Simulation::Particle), 1);
                positionBuffer->unbind();

                sizeBuffer->bind();
                sizeBuffer->setLocation(2);
                sizeBuffer->enable(1, GL_FLOAT, sizeof(float), sizeof(vec2)*2, sizeof(Simulation::Particle), 1);
                sizeBuffer->unbind();

                typeBuffer->bind();
                typeBuffer->setLocation(3);
                typeBuffer->enable(1, GL_INT, sizeof(int), sizeof(vec2)*2+sizeof(float), sizeof(Simulation::Particle), 1);
                typeBuffer->unbind();

                particleVAO->unbind();

                GL_DEBUG_MARKER("particleVAO ready");

                quadVAO->bind();

                quadVertexBuffer->bind();
                quadVertexBuffer->setLocation(0);
                quadVertexBuffer->enable(2, GL_FLOAT, sizeof(GLfloat));
                quadVertexBuffer->data(vertices, sizeof(vertices), GL_STATIC_DRAW);
                quadVertexBuffer->unbind();

                quadVAO->unbind();

                GL_DEBUG_MARKER("quadVAO ready");

                programParticle->use();
                glUniform3fv(programParticle->uniform("uBaseColors"), 10*3, baseColors);
                glUniform2f(programParticle->uniform("uSimSize"), simulation->width, simulation->height);

                GL_DEBUG_MARKER("ready");

                frame = 0;

                ok = true;
                return;

                unsuccess:
                    ok = false;
            }

            ~Render() {
                delete programParticle;
                delete programFiller;

                delete particleVAO;
                delete quadVAO;

                delete vertexBuffer;
                delete positionBuffer;
                delete sizeBuffer;
                delete typeBuffer;
                delete quadVertexBuffer;

                #ifdef POSTPROCESSING
                ppCleanup();

                delete programPost1;
                delete programPost2;
                delete programRender;
                delete renderTexture1;
                delete renderTexture2;
                #endif
            }

            void render(vec2 camera, float zoom, float particlebright, vec3 clrmul, bool glowing, bool strongblur) {
                if (!ok) return;

                uint ww = window->getWidth();
                uint wh = window->getHeight();

                #ifdef POSTPROCESSING
                ppCreate(); // Check for framebuffer resizing

                framebuffer1->bind();

                float scrw = ppWidth;
                float scrh = ppHeight;
                #else
                float scrw = ww;
                float scrh = wh;
                #endif

                // Calculate viewport
                float simRatio = simulation->width/simulation->height;
                float scrRatio = scrw/scrh;

                vec2 vstart = ((vec2(-1.0, -1.0)+camera)*vec2(simRatio/scrRatio, 1.0)*zoom+1.0)/2.0;
                vec2 vend = ((vec2(1.0, 1.0)+camera)*vec2(simRatio/scrRatio, 1.0)*zoom+1.0)/2.0;

                vstart *= vec2(scrw, scrh);
                vend *= vec2(scrw, scrh);

                vend -= vstart;

                glViewport(vstart.x, vstart.y, vend.x, vend.y);
                
                if (glowing) {
                    GL::Clear(0.2, 0.2, 0.2);
                    fill(0.0, 0.0, 0.0);
                    GL::EnableBlending(GL_SRC_ALPHA, GL_ONE);
                } else {
                    GL::Clear(0.0, 0.0, 0.0);
                    fill(0.0, 0.0, 0.2);
                    GL::EnableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    clrmul *= 1.2;
                }

                particleVAO->bind();

                programParticle->use();
                glUniform1f(programParticle->uniform("uBright"), particlebright);

                positionBuffer->bind();
                positionBuffer->data(simulation->particles, sizeof(Simulation::Particle)*simulation->particlesCount, GL_DYNAMIC_DRAW);
                positionBuffer->unbind();

                sizeBuffer->bind();
                sizeBuffer->data(simulation->particles, sizeof(Simulation::Particle)*simulation->particlesCount, GL_DYNAMIC_DRAW);
                sizeBuffer->unbind();

                typeBuffer->bind();
                typeBuffer->data(simulation->particles, sizeof(Simulation::Particle)*simulation->particlesCount, GL_DYNAMIC_DRAW);
                typeBuffer->unbind();

                glDrawArraysInstanced(GL_TRIANGLES, 0, 6, simulation->particlesCount);

                particleVAO->unbind();

                if (glowing) GL::DisableBlending();

                #ifdef POSTPROCESSING
                framebuffer1->unbind();

                glViewport(0, 0, ppWidth, ppHeight);

                float blur1 = 1.0/600.0;
                float blur2 = strongblur ? 1.0/300.0 : 0.0;

                // Post processing 1
                framebuffer2->bind();
                programPost1->use();
                glUniform2f(programPost1->uniform("uBlur"), blur1/scrRatio, blur1);
                drawquad();
                framebuffer2->unbind();

                // Post processing 2
                framebuffer1->bind();
                programPost2->use();
                glUniform3f(programPost2->uniform("uColorMul"), clrmul.x, clrmul.y, clrmul.z);
                glUniform2f(programPost2->uniform("uBlur"), blur2, blur2/scrRatio);
                drawquad();
                framebuffer1->unbind();

                // Rendering from framebuffer

                glViewport(0, 0, ww, wh);

                programRender->use();
                drawquad();
                #endif

                GL_DEBUG_MARKER("frame "+std::to_string(frame));

                frame++;
            }
        
        private:
            bool ok;

            Simulation::Simulation* simulation;

            GL::Window* window;

            GL::VertexArray* particleVAO;
            GL::VertexArray* quadVAO;

            GL::Program* programParticle;
            GL::Program* programFiller;

            GL::AttribBuffer* vertexBuffer;
            GL::AttribBuffer* positionBuffer;
            GL::AttribBuffer* sizeBuffer;
            GL::AttribBuffer* typeBuffer;
            GL::AttribBuffer* quadVertexBuffer;

            uint frame;

            void drawquad() {
                quadVAO->bind();

                glDrawArrays(GL_TRIANGLES, 0, 6);

                quadVAO->unbind();
            }

            void fill(float r, float g, float b) { // Fill viewport with color
                programFiller->use();
                glUniform4f(programFiller->uniform("uColor"), r, g, b, 1.0);

                drawquad();
            }

            #ifdef POSTPROCESSING
            GL::Program* programRender;
            GL::Program* programPost1;
            GL::Program* programPost2;

            GL::Framebuffer* framebuffer1 = nullptr;
            GL::Renderbuffer* renderbuffer1 = nullptr;
            GL::Texture2D* renderTexture1;
            GL::Framebuffer* framebuffer2 = nullptr;
            GL::Renderbuffer* renderbuffer2 = nullptr;
            GL::Texture2D* renderTexture2;

            // pp = PostProcessing

            uint ppLastUpdate = 0;
            uint ppWidth = 0;
            uint ppHeight = 0;

            void ppCleanup() {
                if (renderbuffer1 != nullptr) delete renderbuffer1;
                if (framebuffer1 != nullptr) delete framebuffer1;
                if (renderbuffer2 != nullptr) delete renderbuffer2;
                if (framebuffer2 != nullptr) delete framebuffer2;
            }

            void initFramebuffer(GL::Framebuffer** fbuf, GL::Renderbuffer** rbuf, GL::Texture2D* rtex, uint width, uint height, int texid = GL_TEXTURE0) {
                *rbuf = new GL::Renderbuffer();
                *fbuf = new GL::Framebuffer();

                rtex->bind(texid);
                rtex->wrap(GL_CLAMP_TO_EDGE);
                rtex->filter(GL_LINEAR);
                rtex->data(NULL, width, height, GL_RGBA, GL_RGBA, GL_FLOAT);

                GL_DEBUG_MARKER("rtex inited");

                (*rbuf)->bind();
                GL_DEBUG_MARKER("rbuf binded");

                (*rbuf)->storage(GL_DEPTH24_STENCIL8, width, height);

                GL_DEBUG_MARKER("rbuf inited");

                (*fbuf)->bind();
                (*fbuf)->texture(rtex);
                (*fbuf)->renderbuffer(*rbuf);
                (*fbuf)->unbind();

                GL_DEBUG_MARKER("fbuf inited");
            }

            void ppCreate() { //  Create (recreate) framebuffer
                uint width = (float)window->getWidth()/FRAMEBUFFER_REDUCING;
                uint height = (float)window->getHeight()/FRAMEBUFFER_REDUCING;

                if (framebuffer1 == nullptr || renderbuffer1 == nullptr || framebuffer2 == nullptr || renderbuffer2 == nullptr) goto required; // Skip tests if required

                if (ppWidth == width && ppHeight == height) return; // No need to resize
                if (frame-ppLastUpdate < MAX_BUFFER_RESIZE_RATE) return; // Resizing too frequently

                required:

                ppCleanup();

                GL_DEBUG_MARKER("start resize framebuffer");

                initFramebuffer(&framebuffer1, &renderbuffer1, renderTexture1, width, height, GL_TEXTURE0);
                GL_DEBUG_MARKER("framebuffer1 inited");
                initFramebuffer(&framebuffer2, &renderbuffer2, renderTexture2, width, height, GL_TEXTURE1);
                GL_DEBUG_MARKER("framebuffer2 inited");

                programPost1->use();
                glUniform1i(programPost1->uniform("uTexture"), 0);
                programPost2->use();
                glUniform1i(programPost2->uniform("uTexture"), 1);
                programRender->use();
                glUniform1i(programRender->uniform("uTexture"), 0);

                ppWidth = width;
                ppHeight = height;

                ppLastUpdate = frame;
            }
            #endif
    };
}