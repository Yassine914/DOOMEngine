#pragma once

#include "../core/defines.h"
#include "../../thirdparty/include/glad/glad.h"

#include <fstream>
#include <string>
#include <unordered_map>

class Shader
{
    private:
    u32 rendererID;
    std::string vertPath, fragPath;
    std::unordered_map<std::string, i32> uniformLocationCache;

    private:
    std::string ReadFileSource(const char *filePath);

    public:
    Shader(const char *vertPath, const char *fragPath);

    inline u32 GetID() const { return rendererID; }
    void MakeActive();

    // clang-format off

    inline i32 GetUniformLocation(std::string &name)
    {
        if(uniformLocationCache.find(name) != uniformLocationCache.end())
            return uniformLocationCache[name];
        
        i32 location = glGetUniformLocation(rendererID, name.c_str());

        if(location == -1)
        {
            // TODO: log error
        }

        uniformLocationCache[name] = location;

        return location;
    }

    // sending uniform variables to the shaders
    inline void SetUniformBool(std::string &name, bool val)
    {
        glUniform1i(GetUniformLocation(name), (i32) val);
    }

    inline void SetUniformInt(std::string &name, i32 val)
    {
        glUniform1i(GetUniformLocation(name), val);
    }
    
    inline void SetUniformFloat(std::string &name, f32 val)
    {
        glUniform1f(GetUniformLocation(name), val);
    }

    inline void SetUniformVec2(std::string &name, f32 v0, f32 v1)
    {
        glUniform2f(GetUniformLocation(name), v0, v1);
    }

    inline void SetUniformVec3(std::string &name, f32 v0, f32 v1, f32 v2)
    {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    inline void SetUniformVec4(std::string &name, f32 v0, f32 v1, f32 v2, f32 v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    // clang-format on

    ~Shader();
};