#ifndef GAME_H
#define GAME_H

#include "OpenGL.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"

typedef uint32_t uint32;

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width, Height;
    // constructor/destructor
    Game(uint32 width, uint32 height);
    ~Game() = default;
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};

#endif