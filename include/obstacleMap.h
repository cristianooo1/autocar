#pragma once

#include "obstacle.h"

class ObstacleMap
{
public:
    ObstacleMap();
    ObstacleMap(unsigned width, unsigned height, unsigned obstacle_size);
    ~ObstacleMap();

    // functions
    void addObstacle(unsigned x, unsigned y);
    void removeObstacle(unsigned x, unsigned y);

    void update();
    void render(sf::RenderTarget &target);

private:
    std::vector<std::vector<Obstacle *>> obstacles;
    unsigned obstacleSize;
};