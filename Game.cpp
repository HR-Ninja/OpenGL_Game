#include "Game.hpp"


SpriteRenderer* Renderer;


Game::Game(uint32 width, uint32 height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

void Game::Init()
{
	ResourceManager::LoadShader("Resources/Shaders/sprite.vert", "Resources/Shaders/sprite.frag", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls

    Shader s = ResourceManager::GetShader("sprite");

    Renderer = new SpriteRenderer(s);
    // load textures
    ResourceManager::LoadTexture("Resources/Assets/test_sprite.png", true, "face");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
   Renderer->DrawSprite(glm::vec2(200.0f, 200.0f), ResourceManager::GetTexture("face"), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

