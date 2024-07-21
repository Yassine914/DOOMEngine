#include "defines.h"
#include <string>

void ErrorCallback(u32 error, const char *description);
bool CheckOpenGLError();

std::string readShaderSource(const char *filePath);
