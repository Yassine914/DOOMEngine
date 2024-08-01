#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "../../thirdparty/include/glad/glad.h"
#include "../../thirdparty/include/glm/glm.hpp"

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

    bool CheckOpenGLError();
    std::string GetProgramLog(i32 id);

    public:
    Shader() {}
    Shader(const char *vertPath, const char *fragPath);

    void Generate(const char *vertPath, const char *fragPath);

    inline u32 GetID() const { return rendererID; }
    void MakeActive() const;

    // --------------------- SHADER UNIFORMS ------------------
    inline i32 GetUniformLocation(const std::string &name)
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

    inline void SetUniformBool(const std::string &name, bool val) { glUniform1i(GetUniformLocation(name), (i32)val); }
    inline void SetUniformInt(const std::string &name, i32 val) { glUniform1i(GetUniformLocation(name), val); }
    inline void SetUniformFloat(const std::string &name, f32 val) { glUniform1f(GetUniformLocation(name), val); }

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

    ~Shader();
};