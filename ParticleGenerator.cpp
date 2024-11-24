#include "ParticleGenerator.hpp"



ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount) : m_shader(shader), m_texture(texture), m_amount(amount)
{
    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    m_particles.reserve(m_amount * 2);
    for (unsigned int i = 0; i < amount; ++i)
        m_particles.push_back(Particle());
}

void ParticleGenerator::Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset)
{
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(m_particles[unusedParticle], object, offset);
    }

    for (unsigned int i = 0; i < m_amount; ++i)
    {
        Particle& p = m_particles[i];
        p.m_life -= dt; // reduce life
        if (p.m_life > 0.0f)
        {	// particle is alive, thus update
            p.m_position -= p.m_velocity * dt;
            p.m_color.a -= dt * 2.5f;
        }
        else
        {
            p.m_active = false;
        }
    }
}

void ParticleGenerator::Draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    m_shader.Use();

    for (const Particle p : m_particles)
    {
        if (!p.m_active)
        {
            continue;
        }

        m_shader.SetVector2f("offset", p.m_position);
        m_shader.SetVector4f("color", p.m_color);
        m_texture.Bind();
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


unsigned int ParticleGenerator::firstUnusedParticle()
{
    static unsigned int lastUsedParticle = 0;

    for (unsigned int i = lastUsedParticle; i < m_amount; i++)
    {
        if (m_particles[i].m_life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }

    for (unsigned int i = 0; i < lastUsedParticle; i++)
    {
        if (m_particles[i].m_life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }

    lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, const GameObject& object, glm::vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.m_active = true;
    particle.m_position = object.m_position + random + offset;
    particle.m_color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.m_life = 1.0f;
    particle.m_velocity = object.m_velocity * 0.1f;
}
