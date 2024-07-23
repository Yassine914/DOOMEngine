#pragma once

#include "../defines.h"
#include "../../thirdparty/include/glad/glad.h"

#include <fstream>
#include <string>

class Shader
{
    private:
    u32 ID;
    u32 vShaderID, fShaderID;

    public:
    Shader(const char *vertPath, const char *fragPath);
    std::string ReadFileSource(const char *filePath);

    // getter methods
    inline u32 GetShaderProgramID() { return ID; }
    inline u32 GetVShaderID() { return vShaderID; }
    inline u32 GetFShaderID() { return fShaderID; }

    void Initialize();
    ~Shader();
};