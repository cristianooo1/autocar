#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numbers>
#include <random> // for std::mt19937 and std::random_device
#include <algorithm>

#include "raylib-cpp.hpp"
#include "mapGenerator.hpp"

class RayCasting
{
public:
    struct Polygon
    {
        float theta{0.0f};
        float ox{0.0f};
        float oy{0.0f};
    };

    struct RayCast
    {
        int rayCast{0};
        int rayCastUnique{0};
    };

    RayCasting();
    ~RayCasting();

    void calculateVisibilityPolygon(float ox, float oy, float radius, std::vector<MapGenerator::Line> &_edges);
    void Draw(raylib::Vector2 source);

    RayCasting::RayCast getNumberRays();

private:
    std::vector<Polygon> vectorPolygons;
    RayCast raysCasted;
};