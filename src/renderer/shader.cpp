#include "shader.h"

// clang-format off
Shader::Shader(const char *vertPath, const char *fragPath)
    : ID{0}, vertPath{vertPath}, fragPath{fragPath}
{
    Initialize(vertPath, fragPath);
}

// clang-format on

void Shader::Initialize(const char *vertPath, const char *fragPath)
{
    this->vertPath = vertPath;
    this->fragPath = fragPath;

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

    LOGINIT_COUT();

    glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
        Log(LOG_ERROR) << GetProgramLog(vShaderID) << "\n";

    // compile fragment shader.
    glCompileShader(fShaderID);

    glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
        Log(LOG_ERROR) << GetProgramLog(fShaderID) << "\n";

    ID = glCreateProgram();

    glAttachShader(ID, vShaderID);
    glAttachShader(ID, fShaderID);

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &linked);
    if(linked != 1)
        Log(LOG_ERROR) << GetProgramLog(ID) << "\n";

    if(CheckOpenGLError())
        Log(LOG_ERROR, FILE_INFO) << "OpenGL Error\n";

    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);

    initialized = true;
}

std::string Shader::ReadFileSource(const char *filePath)
{
    LOGINIT_COUT();

    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if(!fileStream.is_open() || fileStream.eof())
        Log(LOG_ERROR) << "SHADER: couldn't parse file with path: " << filePath << ".\n";

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
    LOGINIT_COUT();

    if(!initialized)
        Log(LOG_ERROR) << "tried to use an unitialized shader...\n";
    else
        glUseProgram(ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
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
    glDeleteProgram(ID);
}