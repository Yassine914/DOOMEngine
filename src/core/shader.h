#pragma once

#include "../defines.h"
#include "../../thirdparty/include/glad/glad.h"

#include <fstream>
#include <string>

class Shader
{
    protected:
    GLuint ID;

    public:
    Shader(const char *vertPath, const char *fragPath);

    std::string ReadFileSource(const char *filePath);

    void Initialize();

    ~Shader();
};