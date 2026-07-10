#pragma once
#include "raylib-cpp.hpp"

class Car
{
public:
    Car();
    ~Car();
    void Draw();
    void Update();
    void Move();

private:
    raylib::Rectangle car_rectangle;
    raylib::Vector2 car_dimensions;
    raylib::Vector2 car_position;

    raylib::Rectangle car_origin;

    float speed;
};