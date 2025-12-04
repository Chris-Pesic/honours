#pragma once
#include <vector>
#include <glad/glad.h>

class Sphere {
public:
    GLuint VAO, VBO, EBO;
    int indexCount;

    Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18)
    {
        generate(radius, sectorCount, stackCount);
    }

    void Draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }

private:
    void generate(float radius, int sectors, int stacks)
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const float PI = 3.14159265359f;

        for (int i = 0; i <= stacks; ++i)
        {
            float stackAngle = PI / 2 - (float)i * (PI / stacks);
            float xy = radius * cosf(stackAngle);
            float z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectors; ++j)
            {
                float sectorAngle = (float)j * (2 * PI / sectors);

                float x = xy * cosf(sectorAngle);
                float y = xy * sinf(sectorAngle);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                float length = sqrt(x * x + y * y + z * z);
                vertices.push_back(x / length);
                vertices.push_back(y / length);
                vertices.push_back(z / length);
            }
        }

        for (int i = 0; i < stacks; ++i)
        {
            int k1 = i * (sectors + 1);
            int k2 = k1 + sectors + 1;

            for (int j = 0; j < sectors; ++j, ++k1, ++k2)
            {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if (i != (stacks - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        indexCount = indices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }
};