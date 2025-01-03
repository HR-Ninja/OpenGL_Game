#pragma once

#include "OpenGL.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Shader.hpp"
#include "Texture.hpp"

class SpriteRenderer {

public: 
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer() = default;

	void DrawSprite(glm::vec2 position, const Texture2D& texture, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	unsigned int quadVAO;

	void initRenderData();
};