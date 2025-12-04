#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertCode, fragCode;
    std::ifstream vFile, fFile;

    vFile.open(vertexPath);
    fFile.open(fragmentPath);

    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();

    vFile.close();
    fFile.close();

    vertCode = vStream.str();
    fragCode = fStream.str();

    const char* vSource = vertCode.c_str();
    const char* fSource = fragCode.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vSource, nullptr);
    glCompileShader(vertex);

    GLint success;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(vertex, 512, nullptr, info);
        std::cerr << "Vertex Shader Compilation Failed:\n" << info << std::endl;
    }

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fSource, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(fragment, 512, nullptr, info);
        std::cerr << "Fragment Shader Compilation Failed:\n" << info << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(ID, 512, nullptr, info);
        std::cerr << "Shader Linking Failed:\n" << info << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}