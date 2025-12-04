#include "baseGrid.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

baseGrid::baseGrid() : VAO(0), VBO(0), vertexCount(0) {}

baseGrid::~baseGrid() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

void baseGrid::Create(float size, int divisions) {
    std::vector<glm::vec3> lines;

    float half = size * 0.5f;
    float step = size / divisions;

    for (int i = 0; i <= divisions; i++) {
        float z = -half + i * step;
        lines.emplace_back(-half, 0.0f, z);
        lines.emplace_back(half, 0.0f, z);
    }

    for (int i = 0; i <= divisions; i++) {
        float x = -half + i * step;
        lines.emplace_back(x, 0.0f, -half);
        lines.emplace_back(x, 0.0f, half);
    }

    vertexCount = lines.size();
    std::cout << "Grid vertices: " << vertexCount << std::endl;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(glm::vec3), lines.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindVertexArray(0);
}

void baseGrid::Render(GLuint shader, const glm::mat4& view, const glm::mat4& projection)
{
    glUseProgram(shader);

    glUniformMatrix4fv(glGetUniformLocation(shader, "view"),
        1, GL_FALSE, glm::value_ptr(view));

    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"),
        1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertexCount);
    glBindVertexArray(0);
}