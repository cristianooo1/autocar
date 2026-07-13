#pragma once
#include "raylib-cpp.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>

class Obstacle
{
public:
    Obstacle(int type, raylib::Vector2 position);
    void Update();
    void Draw();
    int GetType();

    raylib::Rectangle obst_rectangle;
    int obst_type;
    raylib::Vector2 obst_position;
    raylib::Color obst_color;

private:
    int ff;
};