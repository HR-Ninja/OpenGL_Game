#pragma once

#include <vector>
#include "GameObject.hpp"
#include "ResourceManager.hpp"


class GameLevel
{
public:

    enum TileState {
        EMPTY,
        SOLID,
        DESTROYABLE
    };

    // level state
    std::vector<GameObject> Bricks;

    // constructor
    GameLevel() = default;

    // loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

    // render level
    void Draw(SpriteRenderer& renderer);

    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();

private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData,
        unsigned int levelWidth, unsigned int levelHeight);
};