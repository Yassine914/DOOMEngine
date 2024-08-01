#include "shader.h"

Shader::Shader(const char *vertPath, const char *fragPath) : rendererID{0}, vertPath{vertPath}, fragPath{fragPath}
{
    Generate(vertPath, fragPath);
}

// clang-format on

void Shader::Generate(const char *vertPath, const char *fragPath)
{
    LOGINIT_COUT();

    if(!vertPath)
    {
        Log(LOG_ERROR, FILE_INFO) << vertPath << " couldn't load";
        return;
    }

    if(!fragPath)
    {
        Log(LOG_ERROR, FILE_INFO) << fragPath << " couldn't load";
        return;
    }

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

    glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
        Log(LOG_ERROR, FILE_INFO) << "vertex shader: " << GetProgramLog(vShaderID) << "\n";

    // compile fragment shader.
    glCompileShader(fShaderID);

    // Renderer::CheckOpenGLError();
    glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
        Log(LOG_ERROR, FILE_INFO) << "fragment shader: " << GetProgramLog(fShaderID) << "\n";

    rendererID = glCreateProgram();

    glAttachShader(rendererID, vShaderID);
    glAttachShader(rendererID, fShaderID);

    glLinkProgram(rendererID);

    // Renderer::CheckOpenGLError();
    glGetProgramiv(rendererID, GL_LINK_STATUS, &linked);
    if(linked != 1)
        Log(LOG_ERROR, FILE_INFO) << "shader program: " << GetProgramLog(rendererID) << "\n";

    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);
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

void Shader::MakeActive() const
{
    glUseProgram(rendererID);
}

// TODO: call this function for every open gl function call
bool Shader::CheckOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();

    while(glErr != GL_NO_ERROR)
    {

        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}

std::string Shader::GetProgramLog(i32 id)
{
    std::string out;
    int len = 0;
    int chWritten = 0;
    char *log;

    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);

    if(len > 0)
    {
        log = (char *)malloc(len);
        glGetProgramInfoLog(id, len, &chWritten, log);
        out = log;
        free(log);
    }

    return out;
}

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}