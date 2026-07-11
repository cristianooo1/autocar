#pragma once
#include "raylib-cpp.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>

class Car
{
public:
    Car();
    ~Car();
    void Draw();
    void UpdatePosition();

    void SetThrottle(int direction, float dt);
    void SetSteering(int direction, float dt);

private:
    raylib::Rectangle car_rectangle;

    const float CAR_WIDTH = 50.0f;
    const float CAR_LENGTH = 100.0f;
    raylib::Vector2 car_dimensions;
    raylib::Vector2 car_position;

    raylib::Rectangle car_origin;
    raylib::Vector2 car_origin_pos;

    float car_speed;
    float car_throttle;
    float car_brake;
    float car_max_speed;

    int car_direction;
    float car_orientation;

    float car_steering_angle;
    float car_steering_angle_speed;
    float car_max_steering_angle;
    float car_steering_brake;
};