#include "texture.h"

#include "../../thirdparty/include/stb_image.h"

// clang-format off
Texture::Texture(const std::string &path, std::string name /* = ""*/)
    :filePath{path}, name{name}, localBuffer{nullptr}, 
     width{0}, height{0}, bpp{0}
{
    SetFilters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    SetWrap(GL_CLAMP_TO_EDGE);
}

void Texture::Load()
{
    LOGINIT_COUT();
    
    stbi_set_flip_vertically_on_load(true);
    localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    if(localBuffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        Log(LOG_ERROR, FILE_INFO) << "couldn't load texture\n";
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    if(localBuffer)
        stbi_image_free(localBuffer);
}

template<typename T>
void Texture::SetFilters(const T &filterMag, const T &filterMin)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
}

template<typename T>
void Texture::SetFilters(const T &filter)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

template<typename T>
void Texture::SetWrap(const T &wrap)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
}

template<typename T>
void Texture::SetWrap(const T &wrapS, const T &wrapT)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

// clang-format on
void Texture::MakeActive(u32 slot /*= 0*/) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::MakeInactive() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}
