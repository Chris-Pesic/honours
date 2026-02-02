#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class baseGrid {
public:
	baseGrid();
	~baseGrid();

	void Create(float size, int divisions);
	void Render(GLuint shader, const glm::mat4& view, const glm::mat4& projection);

private:
	GLuint VAO;
	GLuint VBO;
	int vertexCount;
};