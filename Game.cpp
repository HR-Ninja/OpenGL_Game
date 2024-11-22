#include "Game.hpp"
#include "Profiler.hpp"


SpriteRenderer* Renderer;
GameObject* Player;


Game::Game(uint32 width, uint32 height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height), Level(0) 
{


}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	PROFILE_FUNCTION();
	ResourceManager::LoadShader("Resources/Shaders/sprite.vert", "Resources/Shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("Resources/Assets/block.png", false, "block");
	ResourceManager::LoadTexture("Resources/Assets/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("Resources/Assets/paddle.png", true, "paddle");

	GameLevel one; one.Load("Resources/Assets/one.lvl", this->Width, this->Height / 2);
	
	Levels.push_back(one);

	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// draw level
		Levels[Level].Draw(*Renderer);
		// draw player
		Player->Draw(*Renderer);
	}
}

