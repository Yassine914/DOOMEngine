#include "shader.h"

Shader::Shader(const char *vertPath, const char *fragPath)
{
    std::string vShaderStr = Shader::ReadFileSource(vertPath);
    std::string fShaderStr = Shader::ReadFileSource(fragPath);

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

    GLint vertCompiled, fragCompiled, linked;

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

    ID = glCreateProgram();

    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);

    glLinkProgram(ID);

    // Renderer::CheckOpenGLError();
    glGetProgramiv(ID, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(vfProgram);
    }
}

std::string Shader::ReadFileSource(const char *filePath)
{
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

void Shader::Initialize()
{
    glUseProgram(ID);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}