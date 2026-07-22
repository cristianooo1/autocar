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
        // px and py: HIT POINTS = coordinates of intersection point
        // where ray hit the wall
        float theta{0.0f};
        float px{0.0f};
        float py{0.0f};
        float distance{0.0f};
    };

    struct RayCast
    {
        int rayCast{0};
        int rayCastUnique{0};
        int rayLidar{0};
    };

    struct LidarRay
    {
        bool hit{false};
        float angle{0.0f};
        float distance{0.0f};
    };

    struct Point
    {
        float x{0.0f};
        float y{0.0f};
    };

    RayCasting();
    ~RayCasting();

    void calculateVisibilityPolygon(float ox, float oy, float radius, std::vector<MapGenerator::Line> &_edges);
    void DrawVisibilityPolygon(raylib::Vector2 source);
    void printVisibilityPolygon(int nr);

    void getLidarRays(float ox, float oy, float resolution, float maxRange, float carHeadingRad, const std::vector<MapGenerator::Line> &_edges);
    void DrawLidarRays(raylib::Vector2 source, float carHeadingRad);

    RayCasting::RayCast getNumberRays();

private:
    std::vector<Polygon> vectorPolygons;
    RayCast raysCasted;
    std::vector<LidarRay> vectorLidarRays;
};