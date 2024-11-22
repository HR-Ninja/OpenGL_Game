#include "BallObject.hpp"

BallObject::BallObject()
	: GameObject(), m_radius(12.5f), m_stuck(true)
{
}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite) 
	: GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3{1} , velocity), m_radius(radius), m_stuck(true)
{

}

glm::vec2 BallObject::Move(float dt)
{
    uint32_t& width = Settings::g_window.SCREEN_WIDTH;

	if (m_stuck)
	{
		return m_position;
	}

	m_position += m_velocity * dt;

    if (m_position.x <= 0.0f)
    {
        m_velocity.x = -m_velocity.x;
        m_position.x = 0.0f;
    }
    else if (m_position.x + m_size.x >= width)
    {
        m_velocity.x = -m_velocity.x;
        m_position.x = width - m_size.x;
    }
    if (m_position.y <= 0.0f)
    {
        m_velocity.y = -m_velocity.y;
        m_position.y = 0.0f;
    }

	return m_position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    m_position = position;
    m_velocity = velocity;
    m_stuck = true;
}
