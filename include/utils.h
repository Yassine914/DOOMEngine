#include "../thirdparty/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace renderer {

void ErrorCallback(int error, const char *description);
bool CheckOpenGLError();

string readShaderSource(const char *filePath);
void printShaderLog(GLuint shader);
void printProgramLog(int program);

GLuint CreateShaderProgram();

} // namespace renderer