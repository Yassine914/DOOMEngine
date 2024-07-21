#include <fstream>
#include <iostream>
#include <string>

#include "../include/utils.h"

using namespace std;

namespace renderer {

void ErrorCallback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void printShaderLog(GLuint shader) // take ID of shader and print log
{
    int len = 0;
    int chWritten = 0;
    char *log;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    if(len > 0)
    {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWritten, log);
        std::cout << "Shader Info Log: " << log << std::endl;
        free(log);
    }
}

void printProgramLog(int program) // take program ID and print log
{
    int len = 0;
    int chWritten = 0;
    char *log;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

    if(len > 0)
    {
        log = (char *)malloc(len);
        glGetProgramInfoLog(program, len, &chWritten, log);
        std::cout << "Program Info Log: " << log << std::endl;
        free(log);
    }
}

bool CheckOpenGLError() // OpenGL error checking
{
    bool foundError = false;
    int glErr = glGetError();

    while(glErr != GL_NO_ERROR)
    {
        std::cout << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}

string readShaderSource(const char *filePath) // read shader glsl code from .glsl file
{
    string content;                         // storing file contents.
    ifstream fileStream(filePath, ios::in); // input file stream
    string line = "";

    while(!fileStream.eof())
    {
        getline(fileStream, line);   // load line into line
        content.append(line + "\n"); // add line to content.
    }

    fileStream.close();
    return content;
}

GLuint CreateShaderProgram()
{
    GLint vertCompiled, fragCompiled, linked;

    // Vertex Shader defenition (GLSL code) as arrays of strings
    string vShaderStr = readShaderSource("src/shaders/vertShader.glsl"); // vertex shader to init vertices' positions
    // Fragment Shader defenition (after rasterization pipline process)
    string fShaderStr =
        readShaderSource("src/shaders/fragShader.glsl"); // fragment shader to give each fragment(pixel) an RGBA value

    const char *vShaderSource = vShaderStr.c_str();
    const char *fShaderSource = fShaderStr.c_str();

    // creating empty shader objects
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); // glCreateShader(type) returns ID of object created
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // linking the shaders with sources and compiling them
    glShaderSource(vShader, 1, &vShaderSource, NULL); // loading the glsl code from the strings
    glShaderSource(fShader, 1, &fShaderSource, NULL); // into the empty shader objects

    glCompileShader(vShader); // compile vShader and check for errors
    renderer::CheckOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        cout << "vertex compilation failed" << endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader); // compile fShader and check for errors
    renderer::CheckOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
    {
        cout << "fragment compilation failed" << endl;
        printShaderLog(fShader);
    }

    // Creating the program and linking shaders
    GLuint vfProgram = glCreateProgram(); // an OpenGL program contains a series of compiled shaders
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram); // link program and check for errors
    CheckOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        cout << "linking failed" << endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

} // namespace renderer