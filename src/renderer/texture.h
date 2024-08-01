#pragma once

#include "renderer.h"
#include <string>

#include "../core/defines.h"
#include "../core/logger.h"

class Texture
{
    private:
    u32 rendererID;
    std::string filePath;
    u8 *localBuffer;
    i32 width, height, bpp; // bits per pixel

    public:
    Texture(const std::string &path);

    ///__________________ SETTERS __________________________
    template <typename T> void SetFilters(const T &texMag, const T &texMin);
    template <typename T> void SetFilters(const T &filter);
    template <typename T> void SetWrap(const T &wrap);
    template <typename T> void SetWrap(const T &wrapS, const T &wrapT);

    ///__________________ GETTERS __________________________
    inline i32 GetWidth() const { return width; }
    inline i32 GetHeight() const { return height; }

    void MakeActive(u32 slot = 0) const;
    void MakeInactive() const;

    ~Texture();
};