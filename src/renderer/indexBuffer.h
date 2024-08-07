#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include <glad/glad.h>

#include <vector>

class IndexBuffer
{
    private:
    u32 ID;
    u32 count; // vertices count

    bool initialized;

    public:
    IndexBuffer();
    IndexBuffer(const u32 *data, u32 count);

    void Initialize(const u32 *data, u32 count);

    inline void Bind() const
    {
        LOGINIT_COUT();
        if(!initialized)
        {
            Log(LOG_ERROR) << "tried to bind an uninitialized buffer\n";
            return;
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void Unbind() const;

    inline u32 GetCount() const { return count; }
    inline u32 GetID() const { return ID; }

    inline void Delete() { glDeleteBuffers(1, &ID); }

    ~IndexBuffer();
};
