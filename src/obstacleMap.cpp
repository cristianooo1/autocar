#include "obstacleMap.h"

ObstacleMap::ObstacleMap()
{
    // initialize obstacle map
    this->obstacleSize = 0;
}

ObstacleMap::ObstacleMap(unsigned width, unsigned height, unsigned obstacle_size)
{
    // initialize obstacle map
    this->obstacleSize = obstacle_size;

    this->obstacles.resize(width);
    for (int i = 0; i < this->obstacles.size(); i++)
    {
        this->obstacles[i].resize(height, nullptr);
    }
}

ObstacleMap::~ObstacleMap()
{
    for (int i = 0; i < this->obstacles.size(); i++)
    {
        for (int k = 0; k < this->obstacles[i].size(); k++)
        {
            delete this->obstacles[i][k];
            this->obstacles[i][k] = nullptr;
        }
    }
}

void ObstacleMap::addObstacle(unsigned x, unsigned y)
{
    //
}

void ObstacleMap::removeObstacle(unsigned x, unsigned y)
{
    //
}

void ObstacleMap::update()
{
    //
}

void ObstacleMap::render(sf::RenderTarget &target)
{
    //
}