#include "Game.hpp"
#include "Profiler.hpp"
#include "BallObject.hpp"


SpriteRenderer* Renderer;
GameObject* Player;
BallObject* Ball;

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

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
	ResourceManager::LoadTexture("Resources/Assets/test_sprite.png", true, "face");

	GameLevel one; 
	one.Load("Resources/Assets/one.lvl", this->Width, this->Height / 2);
	
	Levels.push_back(one);

	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));


	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
		-BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
		ResourceManager::GetTexture("face"));
}

void Game::Update(float dt)
{
	Ball->Move(dt);
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->m_position.x >= 0.0f)
				Player->m_position.x -= velocity;
			if (Ball->m_stuck)
				Ball->m_position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->m_position.x <= this->Width - Player->m_size.x)
				Player->m_position.x += velocity;
			if (Ball->m_stuck)
				Ball->m_position.x += velocity;
		}

		if (this->Keys[GLFW_KEY_SPACE])
			Ball->m_stuck = false;
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

		Ball->Draw(*Renderer);
	}
}

