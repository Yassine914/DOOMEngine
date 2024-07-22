#include "../include/renderer.h"

#include <iostream>

Renderer::Renderer(GLFWwindow *window)
{
    Renderer::version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(Renderer::version == 0)
    {
        // TODO: setup logging.
        // ErrorCallback(2, "failed to load OpenGL.");

        return;
    }

    // setup vsync
    if(Renderer::VSyncEnabled()) glfwSwapInterval(1);
}

std::string Renderer::ReadShaderSource(const char *filePath)
{
    std::cout << "shader source: " << filePath << std::endl;
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    std::string line = "";

    while(!fileStream.eof())
    {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint Renderer::CreateShaderProgram()
{
    GLint vertCompiled, fragCompiled, linked;

    std::string vShaderStr = Renderer::ReadShaderSource(Renderer::GetVShaderPath());
    std::string fShaderStr = Renderer::ReadShaderSource(Renderer::GetFShaderPath());

    const char *vShaderSrc = vShaderStr.c_str();
    const char *fShaderSrc = fShaderStr.c_str();

    // create empty shader objects
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // link shaders with the src files
    glShaderSource(vShader, 1, &vShaderSrc, NULL);
    glShaderSource(fShader, 1, &fShaderSrc, NULL);

    // compile vertex shader.
    glCompileShader(vShader);

    // Renderer::CheckOpenGLError(); // TODO: implement logging.
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(vShader);
    }

    // compile fragment shader.
    glCompileShader(fShader);

    // Renderer::CheckOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(fShader);
    }

    // create the full program (with vert and frag shader)
    GLuint vfProgram = glCreateProgram();

    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);

    // Renderer::CheckOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(vfProgram);
    }

    return vfProgram;
}

void Renderer::InitializeShaders()
{
    std::cout << "heelloo from the shader source!";
    Renderer::renderProgram = Renderer::CreateShaderProgram();
    std::cout << "should've rendered the shaders properly.." << std::endl;

    // TODO: create vertex array objects
    //       and vertex buffer objects
}