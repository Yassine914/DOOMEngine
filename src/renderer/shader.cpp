#include "shader.h"

// clang-format off
Shader::Shader(const char *vertPath, const char *fragPath)
    : rendererID{0}, vertPath{vertPath}, fragPath{fragPath}
{
    std::string vShaderStr = Shader::ReadFileSource(vertPath);
    std::string fShaderStr = Shader::ReadFileSource(fragPath);

    const char *vShaderSrc = vShaderStr.c_str();
    const char *fShaderSrc = fShaderStr.c_str();

    // create empty shader objects
    i32 vShaderID = glCreateShader(GL_VERTEX_SHADER);
    i32 fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // link shaders with the src files
    glShaderSource(vShaderID, 1, &vShaderSrc, NULL);
    glShaderSource(fShaderID, 1, &fShaderSrc, NULL);

    // compile vertex shader.
    glCompileShader(vShaderID);

    GLint vertCompiled, fragCompiled, linked;

    // Renderer::CheckOpenGLError(); // TODO: implement logging.
    glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(vShader);
    }

    // compile fragment shader.
    glCompileShader(fShaderID);

    // Renderer::CheckOpenGLError();
    glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(fShader);
    }

    rendererID = glCreateProgram();

    glAttachShader(rendererID, vShaderID);
    glAttachShader(rendererID, fShaderID);

    glLinkProgram(rendererID);

    // Renderer::CheckOpenGLError();
    glGetProgramiv(rendererID, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        // TODO: log error.
        // Renderer::PrintProgramLog(vfProgram);
    }

    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);
}

// clang-format on

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

void Shader::Bind() const
{
    glUseProgram(rendererID);
}

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}