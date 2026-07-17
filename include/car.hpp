#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>

#include "raylib-cpp.hpp"
#include "transform2D.hpp"
#include "boundingBox2D.hpp"

class Car
{
public:
    Car(raylib::Vector2 dimensions, raylib::Vector2 origin, raylib::Vector2 position);
    ~Car();
    void Draw();
    void Update();

    void SetThrottle(int direction, float dt);
    void SetSteering(int direction, float dt);

    raylib::Vector2 GetCarPosition();
    std::vector<raylib::Vector2> GetCarBoundaries();

private:
    Transform2D _carTransform;
    BoundingBox2D _carBB;
    Rectangle _car_draw_rec;

    float car_speed;
    float car_throttle;
    float car_brake;
    float car_max_speed;

    int car_direction;

    float car_steering_angle;
    float car_steering_angle_speed;
    float car_max_steering_angle;
    float car_steering_brake;
};