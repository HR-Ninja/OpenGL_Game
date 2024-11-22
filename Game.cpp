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

	HandleCollisions();

	if (Ball->m_position.y >= Settings::g_window.SCREEN_HEIGHT)
	{
		State = GAME_MENU;
	}
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

void Game::HandleCollisions()
{
	for (GameObject& box : Levels[Level].Bricks)
	{
		if (box.m_destroyed)
		{
			continue;
		}

		Collision collision = CheckCollisions(*Ball, box);

		if (std::get<0>(collision))
		{
			if (!box.m_isSolid)
			{
				box.m_destroyed = true;
			}

			Direction dir = std::get<1>(collision);
			glm::vec2 diff_vector = std::get<2>(collision);


			if (dir == LEFT || dir == RIGHT) // horizontal collision
			{
				Ball->m_velocity.x = -Ball->m_velocity.x;

				float penetration = Ball->m_radius - std::abs(diff_vector.x);
				if (dir == LEFT)
					Ball->m_position += penetration;
				else
					Ball->m_position -= penetration;
			}
			else // verticle collision
			{
				Ball->m_velocity.y = -Ball->m_velocity.y;

				float penetration = Ball->m_radius - std::abs(diff_vector.y);
				if (dir == UP)
					Ball->m_position.y -= penetration; // move ball back up
				else
					Ball->m_position.y += penetration;
			}
		}
	}
}

Direction Game::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};

	float max = 0.0f;

	uint32_t bestMatch = -1;

	for (uint32_t i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			bestMatch = i;
		}
	}

	return (Direction) bestMatch;
}


// Circle collision
Collision Game::CheckCollisions(BallObject& one, GameObject& two)
{
	glm::vec2 circleCentre = one.m_position + one.m_radius;
	glm::vec2 halfExtents = glm::vec2(two.m_size.x / 2, two.m_size.y / 2);
	glm::vec2 boxCentre = two.m_position + halfExtents;

	glm::vec2 difference = circleCentre - boxCentre;
	glm::vec2 clampedDiff = glm::clamp(difference, -halfExtents, halfExtents);

	glm::vec2 closest = boxCentre + clampedDiff;

	difference = closest - circleCentre;

	if (glm::length(difference) < one.m_radius)
	{
		return std::make_tuple(true, VectorDirection(difference), difference);
	}
	else
	{
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
	}

}



// Box collision
//bool Game::CheckCollisions(GameObject& one, GameObject& two)
//{
//	bool collisionX = (one.m_position.x + one.m_size.x) >= two.m_position.x && (two.m_position.x + two.m_size.x) >= one.m_position.x;
//	bool collisionY = (one.m_position.y + one.m_size.y) >= two.m_position.y && (two.m_position.y + two.m_size.y) >= one.m_position.y;
//
//	return collisionX && collisionY;
//}



