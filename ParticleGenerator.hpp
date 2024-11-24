#pragma once

#include "OpenGL.hpp"
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"

struct Particle {
    glm::vec2 m_position, m_velocity;
    glm::vec4 m_color;
    float m_life;

    Particle() : m_position(0.0f), m_velocity(0.0f), m_color(1.0f), m_life(0.0f) { }
};

class ParticleGenerator
{
public:
    // constructor
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
    // update all particles
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // render all particles
    void Draw();
private:
    // state
    std::vector<Particle> m_particles;
    unsigned int m_amount;
    // render state
    Shader m_shader;
    Texture2D m_texture;
    unsigned int m_VAO;
    // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    unsigned int firstUnusedParticle();
    // respawns particle
    void respawnParticle(Particle& particle, const GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};