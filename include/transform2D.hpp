#pragma once
#include "raylib-cpp.hpp"

struct Transform2D
{
    raylib::Vector2 position{0.0f, 0.0f};
    float orientationDeg{0.0f};
    float scale{1.0f};

    float deg2rad(float orientation_deg);
};