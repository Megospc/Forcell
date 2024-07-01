// Some classes and functions that help with OpenGL

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "Definitions.h"

#ifdef NDEBUG
#define GL_DEBUG_MARKER(name) 
#else
#define GL_DEBUG_MARKER(name) GL::GetError(name)
#endif

namespace GL {
    void onerror(int id, cstr message) {
        Error("GLFW Error " << id << ": " << message);
    }

    bool Init() {
        glfwSetErrorCallback(&onerror);

        if (glfwInit() != GL_TRUE) {
            Error("Couldn't init GLFW");
                    
            return false;
        }

        return true;
    }

    bool GetError(cstr marker = NULL) {
        GLenum err = glGetError();

        if (err == GL_NO_ERROR) return true;

        char* message;

        if (err == GL_INVALID_ENUM) message = (char*)"Invalid Enum";
        if (err == GL_INVALID_VALUE) message = (char*)"Invalid Value";
        if (err == GL_INVALID_OPERATION) message = (char*)"Invalid Operation";
        if (err == GL_OUT_OF_MEMORY) message = (char*)"Out Of Memory";
        if (err == GL_INVALID_FRAMEBUFFER_OPERATION) message = (char*)"Invalid Framebuffer Operation";

        if (marker == NULL) Error("GL: " << message);
        else Error("GL " << marker << ": " << message);

        return false;
    }

    bool GetError(string marker) {
        return GetError(marker.c_str());
    }

    class Window {
        public:
            Window(cstr title, uint width, uint height, bool resize = false) {
                glfwWindowHint(GLFW_RESIZABLE, resize ? GLFW_TRUE:GLFW_FALSE);

                create(title, width, height, NULL, NULL);
            }

            Window(cstr title) { // Full screen
                glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

                GLFWmonitor* monitor = glfwGetPrimaryMonitor();

                const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

                create(title, vidmode->width, vidmode->height, monitor, NULL);
            }

            ~Window() {
                if (!ok) return;
                
                use();
                
                glfwDestroyWindow(glwindow);
            }
            
            bool isOk() {
                return ok;
            }

            void icon(GLFWimage* images, uint count = 1) {
                if (!ok) return;

                glfwSetWindowIcon(glwindow, count, images);
            }
            
            void use() {
                if (!ok) return;
                
                glfwMakeContextCurrent(glwindow);
            }
            
            void begin(void (*callback)(void)) {
                if (!ok) return;
                
                while (!glfwWindowShouldClose(glwindow)) {
                    callback();
                    
                    glfwPollEvents();

                    glfwSwapBuffers(glwindow);
                }
            }

            GLFWwindow* getWindow() {
                return glwindow;
            }

            void close() {
                glfwSetWindowShouldClose(glwindow, GLFW_TRUE);
            }

            uint getWidth() {
                if (!ok) return 0;

                updateSize();

                return width;
            }

            uint getHeight() {
                if (!ok) return 0;

                updateSize();

                return height;
            }
            
        private:
            bool ok;
            
            GLFWwindow* glwindow;

            int width;
            int height;

            void updateSize() {
                glfwGetWindowSize(glwindow, &width, &height);
            }

            void create(cstr title, uint width, uint height, GLFWmonitor* monitor, GLFWwindow* share) {
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                
                glwindow = glfwCreateWindow(width, height, title, monitor, share);
                
                if (glwindow == nullptr) {
                    Error("Couldn't create window");
                    
                    goto unsuccess;
                }
                
                glfwMakeContextCurrent(glwindow);

                glfwSwapInterval(1);

                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    Error("Couldn't init GLAD");
                    
                    goto unsuccess;
                }

                this->width = width;
                this->height = height;

                ok = true;

                return;
                
                unsuccess:
                    ok = false;
            }
    };

    class Shader {
        public:
            Shader(cstr source, int type, string name = "unnamed") {
                id = glCreateShader(type);

                GL_DEBUG_MARKER("shader "+name+" created");

                glShaderSource(id, 1, &source, NULL);

                GL_DEBUG_MARKER("shader "+name+" source");
                
                glCompileShader(id);

                GL_DEBUG_MARKER("shader "+name+" compiled");
                
                int success;
                char log[512];
                
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                
                if (success) ok = true;
                else {
                    glGetShaderInfoLog(id, 512, NULL, log);
                    
                    Error("Shader " << name << " error:");

                    Error(log);

                    glDeleteShader(id);
                    
                    ok = false;
                }

                GL_DEBUG_MARKER("shader "+name+" checked");
            }

            ~Shader() {
                if (!ok) return;
                
                glDeleteShader(id);

                GL_DEBUG_MARKER("shader deleted");
            }
            
            uint getID() {
                return id;
            }
            
            bool isOk() {
                return ok;
            }
            
        private:
            bool ok;
            
            uint id;
    };

    class Program {
        public:
            Program(cstr vertexSource, cstr fragmentSource, string name = "unnamed") {
                Shader* vertex = new Shader(vertexSource, GL_VERTEX_SHADER, name+"-vertex");
                Shader* fragment = new Shader(fragmentSource, GL_FRAGMENT_SHADER, name+"-fragment");

                id = glCreateProgram();

                GL_DEBUG_MARKER("program "+name+" created");
                
                if (!vertex->getID() || !fragment->isOk()) {
                    ok = false;
                    
                    return;
                }
                
                glAttachShader(id, vertex->getID());
                glAttachShader(id, fragment->getID());

                GL_DEBUG_MARKER("program "+name+" attached");

                glLinkProgram(id);

                GL_DEBUG_MARKER("program "+name+" linked");
                
                int success;
                char log[512];
                
                glGetProgramiv(id, GL_LINK_STATUS, &success);
                
                if (success) ok = true;
                else {
                    glGetProgramInfoLog(id, 512, NULL, log);

                    Error("Program " << name << " error:");
                    
                    Error(log);

                    glDeleteProgram(id);
                    
                    ok = false;
                }

                GL_DEBUG_MARKER("program "+name+" checked");

                delete vertex;
                delete fragment;
            }

            ~Program() {
                if (!ok) return;
                
                glDeleteProgram(id);
            }

            uint uniform(const char* name) {
                return glGetUniformLocation(id, name);
            }
            
            uint getID() {
                return id;
            }
            
            bool isOk() {
                return ok;
            }

            void use() {
                if (!ok) return;
                
                glUseProgram(id);
            }
            
        private:
            bool ok;
            
            uint id;
    };

    class VertexArray {
        public:
            VertexArray() {
                glGenVertexArrays(1, &id);
                
                ok = true;
            }

            ~VertexArray() {
                if (!ok) return;
                
                glDeleteVertexArrays(1, &id);
            }
            
            void bind() {
                if (!ok) return;
                
                glBindVertexArray(id);
            }
            
            void unbind() {
                glBindVertexArray(0);
            }
            
            uint getID() {
                return id;
            }
            
            bool isOk() {
                return ok;
            }
            
        private:
            bool ok;
            
            uint id;
    };

    class AttribBuffer {
        public:
            AttribBuffer() {
                glGenBuffers(1, &id);
                
                ok = true;
            }

            ~AttribBuffer() {
                if (!ok) return;
                
                glDeleteBuffers(1, &id);
            }
            
            void bind(int target = GL_ARRAY_BUFFER) {
                if (!ok) return;
                
                glBindBuffer(target, id);
                
                lastTarget = target;
            }
            
            void unbind() {
                if (!lastTarget) return;
                
                glBindBuffer(lastTarget, 0);

                lastTarget = 0;
            }

            void setLocation(uint location) {
                this->location = location;
            }
            
            void enable(uint vsize, int type, uint tsize, uint64_t offset = 0, uint stride = 0, uint divisor = 0) {
                if (!ok) return;
                
                glVertexAttribPointer(location, vsize, type, GL_FALSE, stride > 0 ? stride:vsize*tsize, (void*)offset);
                glVertexAttribDivisor(location, divisor);
                glEnableVertexAttribArray(location);
            }
            
            void disable() {
                if (!ok) return;
                
                glDisableVertexAttribArray(location);
            }

            void data(void* data, uint size, int usage) {
                if (!ok) return;
                if (!lastTarget) return;

                glBufferData(lastTarget, size, data, usage);
            }
            
            uint getLocation() {
                return location;
            }
            
            uint getID() {
                return id;
            }
            
            bool isOk() {
                return ok;
            }
            
        private:
            bool ok;
            
            uint id;
            
            uint location;
            
            int lastTarget;
    };

    class Texture2D {
        public:
            Texture2D() {
                glGenTextures(1, &id);
                
                ok = true;
            }

            ~Texture2D() {
                if (!ok) return;

                glDeleteTextures(1, &id);
            }

            void filter(int filter) {
                if (!ok) return;
                if (!lastTarget) return;

                glTexParameteri(lastTarget, GL_TEXTURE_MAG_FILTER, filter);
                glTexParameteri(lastTarget, GL_TEXTURE_MIN_FILTER, filter);
            }

            void wrap(int wrap) {
                if (!ok) return;
                if (!lastTarget) return;

                glTexParameteri(lastTarget, GL_TEXTURE_WRAP_S, wrap);
                glTexParameteri(lastTarget, GL_TEXTURE_WRAP_R, wrap);
            }

            void data(void* data, uint width, uint height, int iformat, int oformat, int type, uint level = 0, uint border = 0) {
                if (!ok) return;
                if (!lastTarget) return;

                glTexImage2D(lastTarget, level, oformat, width, height, border, iformat, type, data);
            }
            
            void bind(int texture = GL_TEXTURE0, int target = GL_TEXTURE_2D) {
                if (!ok) return;
                
                glActiveTexture(texture);
                glBindTexture(target, id);
                
                lastTarget = target;
            }
            
            void unbind() {
                if (!lastTarget) return;
                
                glBindTexture(lastTarget, 0);

                lastTarget = 0;
            }

            void border(color color) {
                if (!lastTarget) return;

                GLfloat data[4];

                data[0] = color.r;
                data[1] = color.g;
                data[2] = color.b;
                data[3] = color.a;

                glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, data);
            }

            uint getID() {
                return id;
            }
            
            bool isOk() {
                return ok;
            }

        private:
            bool ok;
            
            uint id;

            int lastTarget;
    };

    class Renderbuffer {
        public:
            Renderbuffer() {
                glGenRenderbuffers(1, &id);
            }

            ~Renderbuffer() {
                glDeleteRenderbuffers(1, &id);
            }

            void storage(int format, uint width, uint height) {
                glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
            }

            void bind() {
                glBindRenderbuffer(GL_RENDERBUFFER, id);
            }
            
            void unbind() {
                glBindRenderbuffer(GL_RENDERBUFFER, 0);
            }

            uint getID() {
                return id;
            }

            bool isOk() {
                return true;
            }
        
        private:
            uint id;
    };

    class Framebuffer {
        public:
            Framebuffer() {
                glGenFramebuffers(1, &id);
            }

            ~Framebuffer() {
                glDeleteFramebuffers(1, &id);
            }

            void texture(GL::Texture2D* texture, uint attach = GL_COLOR_ATTACHMENT0) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, attach, GL_TEXTURE_2D, texture->getID(), 0);
            }

            void renderbuffer(Renderbuffer* buffer) {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer->getID());
            }

            void bind() {
                glBindFramebuffer(GL_FRAMEBUFFER, id);
            }
            
            void unbind() {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
 
            uint getID() {
                return id;
            }

            bool isOk() {
                return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
            }
        
        private:
            uint id;
    };

    void EnableBlending(int s, int d) {
        glEnable(GL_BLEND);
        
        glBlendFunc(s, d);
    }

    void DisableBlending() {
        glDisable(GL_BLEND);
    }

    void Clear(float r, float g, float b, float a = 1.0) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Destroy() {
        glfwTerminate();
    }
}