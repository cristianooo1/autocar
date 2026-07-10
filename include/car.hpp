#pragma once
#include "raylib-cpp.hpp"

class Car
{
public:
    Car();
    ~Car();
    void Draw();
    void Update();

private:
    raylib::Rectangle car_rectangle;
    raylib::Vector2 car_position;

    float speed;
};