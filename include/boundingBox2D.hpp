#pragma once
#include "raylib-cpp.hpp"
#include "transform2D.hpp"
#include <array>

struct BoundingBox2D
{
    float width{};
    float height{};
    raylib::Vector2 origin{this->width / 2, this->height / 2};

    std::vector<raylib::Vector2> GetCorners(Transform2D &transform);
};