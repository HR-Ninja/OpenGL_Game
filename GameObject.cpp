#include "GameObject.hpp"


GameObject::GameObject() : 
	m_position(0.0f, 0.0f), m_size(1.0f, 1.0f), m_velocity(0.0f), m_color(1.0f), m_rotation(0.0f), m_sprite(), m_isSolid(false), m_destroyed(false) {

}



GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity) : 
	m_position(pos), m_size(size), m_velocity(velocity), m_color(color), m_rotation(0.0f), m_sprite(sprite), m_isSolid(false), m_destroyed(false) {

}


void GameObject::Draw(SpriteRenderer& renderer) {
	renderer.DrawSprite(m_position, m_sprite, m_size, m_rotation, m_color);
}