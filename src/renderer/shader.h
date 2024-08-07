#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <unordered_map>

class Shader
{
    private:
    u32 ID;
    std::string vertPath, fragPath;
    std::unordered_map<std::string, i32> uniformLocationCache;
    bool initialized;

    private:
    std::string ReadFileSource(const char *filePath);

    public:
    Shader() : initialized{false} {}

    void Initialize(const char *vertPath, const char *fragPath);

    Shader(const char *vertPath, const char *fragPath);

    inline u32 GetID() const { return ID; }
    void Bind() const;
    void Unbind() const;

    // clang-format off

    inline i32 GetUniformLocation(const std::string &name)
    {
        Bind();
        LOGINIT_COUT();

        if(!initialized)
        {
            Log(LOG_ERROR) << "tried to send a uniform without initializing the shader; uniform: " << name << "...\n";
            return -1;
        }
        
        
        if(uniformLocationCache.find(name) != uniformLocationCache.end())
            return uniformLocationCache[name];
        
        i32 location = glGetUniformLocation(ID, name.c_str());

        if(location == -1)
        {
            Log(LOG_ERROR) << "problem sending a uniform from program : " << ID << ".\n";
            Log(LOG_ERROR) << "couldn't send uniform \"" << name << "\" to the shader.\n";
            Log(LOG_ERROR) << "make sure you have the uniform set in the shader code.\n";
        }

        uniformLocationCache[name] = location;
        return location;
    }

    // sending uniform variables to the shaders
    inline void SetUniformBool(const std::string &name, bool val)
    {
        glUniform1i(GetUniformLocation(name), (i32) val);
    }

    inline void SetUniformInt(const std::string &name, i32 val)
    {
        glUniform1i(GetUniformLocation(name), val);
    }
    
    inline void SetUniformFloat(const std::string &name, f32 val)
    {
        glUniform1f(GetUniformLocation(name), val);
    }

    inline void SetUniformVec2(const std::string &name, f32 v0, f32 v1)
    {
        glUniform2f(GetUniformLocation(name), v0, v1);
    }

    inline void SetUniformVec3(const std::string &name, f32 v0, f32 v1, f32 v2)
    {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    inline void SetUniformVec4(const std::string &name, f32 v0, f32 v1, f32 v2, f32 v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    inline void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    // clang-format on

    std::string GetProgramLog(i32 id);

    ~Shader();
};
