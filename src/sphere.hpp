#pragma once
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Sphere {
public:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    int indexCount = 0;

    Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18){
        generate(radius, sectorCount, stackCount);
    }

    void Draw() const{
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    void generate(float radius, int sectors, int stacks){
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const float PI = 3.14159265359f;

        for (int i = 0; i <= stacks; ++i){
            float stackAngle = PI * 0.5f - (float)i * (PI / (float)stacks);
            float xy = radius * cosf(stackAngle);
            float z = radius * sinf(stackAngle);

            float v = (float)i / (float)stacks;
            
            for (int j = 0; j <= sectors; ++j){
                float sectorAngle = (float)j * (2.0f * PI / (float)sectors);
                float x = xy * cosf(sectorAngle);
                float y = xy * sinf(sectorAngle);

                float u = (float)j / (float)sectors;

                float len = sqrtf(x * x + y * y + z * z);
                float nx = x / len;
                float ny = y / len;
                float nz = z / len;

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                vertices.push_back(nx);
                vertices.push_back(ny);
                vertices.push_back(nz);

                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        for (int i = 0; i < stacks; ++i){
            int k1 = i * (sectors + 1);
            int k2 = k1 + sectors + 1;

            for (int j = 0; j < sectors; ++j, ++k1, ++k2){
                if (i != 0){
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if (i != (stacks - 1)){
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        indexCount = (int)indices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        GLsizei stride = 8 * sizeof(float);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
};