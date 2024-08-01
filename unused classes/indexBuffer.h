#pragma once

#include "../core/defines.h"
#include "../../thirdparty/include/glad/glad.h"

class IndexBuffer
{
    private:
    u32 rendererID;
    u32 count; // vertices count

    public:
    IndexBuffer(const u32 *data, u32 count);

    void MakeActive() const;
    void MakeInactive() const;

    inline u32 GetCount() const { return count; }

    ~IndexBuffer();
};
