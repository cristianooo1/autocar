#pragma once
#include <iostream>
#include <random> // for std::mt19937 and std::random_device
#include <cmath>

#include "car.hpp"
#include "obstacle.hpp"
#include "transform2D.hpp"
#include "mapGenerator.hpp"
#include "projectConfig.hpp"

class Game
{
public:
    Game(int mapWidth, int mapHeight);
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

private:
    MapGenerator _mapGenerator;
    Car _car;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();

    // instantiate 32-bit Mersenne Twister
    // for random number generation
    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> obstaclePos{0, 1};
    float dt;

    raylib::Vector2 CheckCollision();
};