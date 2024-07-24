#pragma once

#include "../defines.h"
#include "../../thirdparty/include/glad/glad.h"

#include <fstream>
#include <string>

class Shader
{
    private:
    u32 ID;

    public:
    Shader(const char *vertPath, const char *fragPath);
    std::string ReadFileSource(const char *filePath);

    // getter methods
    inline u32 GetID() const { return ID; }

    void MakeActive();

    // clang-format off
    
    // sending uniform variables to the shaders
    inline void SetBool(const char *name, bool val) const
    {
        glUniform1i(glGetUniformLocation(ID, name), (i32) val);
    }

    inline void SetInt(const char *name, i32 val) const
    {
        glUniform1i(glGetUniformLocation(ID, name), val);
    }
    
    inline void SetFloat(const char *name, f32 val) const
    {
        glUniform1f(glGetUniformLocation(ID, name), val);
    }
    // clang-format on

    ~Shader();
};