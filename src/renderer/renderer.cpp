#include "renderer.h"

bool CheckOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();

    while(glErr != GL_NO_ERROR)
    {

        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}