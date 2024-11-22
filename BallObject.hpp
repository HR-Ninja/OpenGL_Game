#pragma once

#include "OpenGL.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"

class BallObject : public GameObject {
public:
	float m_radius;
	bool m_stuck;

	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(float dt);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};