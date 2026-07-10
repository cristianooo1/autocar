#pragma once
#include "raylib-cpp.hpp"

class Car
{
public:
    Car();
    ~Car();
    void Draw();
    void UpdatePosition();

    void SetThrottle(float newThrottle);

private:
    raylib::Rectangle car_rectangle;
    raylib::Vector2 car_dimensions;
    raylib::Vector2 car_position;

    raylib::Rectangle car_origin;

    float steering_angle;
    float throttle;
};