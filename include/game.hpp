#pragma once
#include <iostream>
#include <random> // for std::mt19937 and std::random_device
#include <cmath>

#include "car.hpp"
#include "obstacle.hpp"
#include "transform2D.hpp"
#include "mapGenerator.hpp"
#include "projectConfig.hpp"
#include "rayCasting.hpp"

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
    std::vector<int> grid2D;
    std::vector<MapGenerator::Line> _boundaries;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();
    RayCasting _lidar;

    int game_window_width;
    int game_window_height;

    // instantiate 32-bit Mersenne Twister
    // for random number generation
    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> obstaclePos{0, 1};
    float dt;
    bool IsMousePressed;

    bool CheckCollision(raylib::Vector2 &collision_point);
    raylib::Vector2 collision_point{};
};