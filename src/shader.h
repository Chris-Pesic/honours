#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use() const {
        glUseProgram(ID);
    }

    void setMat4(const std::string& name, const float* value) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
    }

    void setVec3(const std::string& name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
};