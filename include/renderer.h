#include "defines.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include <fstream>
#include <string>

class Renderer
{
    private:
    bool vsync;
    const char *vShaderPath, *fShaderPath;

    protected:
    u32 version;
    GLuint renderProgram;

    public:
    Renderer(GLFWwindow *window);

    // getters and setters
    inline void SetVSync(bool vsync) { this->vsync = vsync; }
    inline bool VSyncEnabled() { return vsync; }

    inline u32 GetVersion() { return version; }

    inline const char *GetVShaderPath() { return vShaderPath; }
    inline const char *GetFShaderPath() { return fShaderPath; }

    inline void SetVShaderPath(const char *vPath) { this->vShaderPath = vPath; };
    inline void SetFShaderPath(const char *fPath) { this->fShaderPath = fPath; };

    // TODO: printing shader log should be in logger.h
    // void PrintShaderLog(GLuint shader);
    // void PrintProgramLog(u32 program);
    // bool CheckOpenGLError();

    // shader program initializers
    std::string ReadShaderSource(const char *filePath);
    GLuint CreateShaderProgram();

    void InitializeShaders();

    ~Renderer() = default;
};