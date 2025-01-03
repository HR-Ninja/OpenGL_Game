#include "GameLevel.hpp"
#include "Profiler.hpp"
#include <fstream>
#include <sstream>

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / height;

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (tileData[y][x] == SOLID) // solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size,
                    ResourceManager::GetTexture("block_solid"),
                    glm::vec3(0.8f, 0.8f, 0.7f)
                );
                obj.m_isSolid = true;
                Bricks.push_back(obj);
            }
            else if (tileData[y][x] > SOLID)
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                Bricks.push_back(
                    GameObject(pos, size, ResourceManager::GetTexture("block"), color)
                    );
            }
        }
    }


}

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    PROFILE_FUNCTION();
	Bricks.clear();

	unsigned int tileCode;
	GameLevel level;

    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;

    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            init(tileData, levelWidth, levelHeight);
    }

}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : Bricks)
        if (!tile.m_destroyed)
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : Bricks)
        if (!tile.m_isSolid && !tile.m_destroyed)
            return false;
    return true;
}

