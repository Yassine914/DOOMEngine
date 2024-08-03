#pragma once

#include "renderer.h"

#include <string>

class Texture
{
    private:
    std::string filePath;
    u8 *localBuffer;
    i32 width, height, bpp; // bits per pixel

    public:
    u32 ID;
    std::string name;

    public:
    Texture(const std::string &path, const std::string &name);

    void Bind(u32 slot = 0) const;
    void Unbind() const;

    inline i32 GetWidth() const { return width; }
    inline i32 GetHeight() const { return height; }

    ~Texture();
};