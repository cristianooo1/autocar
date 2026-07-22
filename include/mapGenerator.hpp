#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numbers>
#include <random> // for std::mt19937 and std::random_device

#include "raylib-cpp.hpp"

class MapGenerator
{
public:
    MapGenerator(int width, int height, float scale, int rule1, int rule2, int fillprob, int nr_generations);
    ~MapGenerator();

    int pickRand();

    void initMap();

    void generationStep();

    void printMap();

    std::vector<int> generate2DGrid();

    struct Vertex
    {
        int x;
        int y;
    };

    struct Corner
    {
        Vertex position;
        Vertex verticalEdge;
        Vertex horizontalEdge;
    };

    struct Square
    {
        Corner corner1;
        Corner corner2;
        Corner corner3;
        Corner corner4;
    };

    struct Line
    {
        raylib::Vector2 start;
        raylib::Vector2 end;
    };

    void getBoundaryEdges(const std::vector<int> &grid, std::vector<MapGenerator::Line> &_boundaryLines);

private:
    int map_width{};
    int map_height{};
    float _scale{10.0f};
    int r1_cutoff{5};
    int r2_cutoff{2};
    int fillProb{40};
    int generations{3};

    // read/write buffer with 2 grids
    // grid1: read buffer = current state of map
    // grid2: write buffer = next generation of map
    std::vector<int> grid1{};
    std::vector<int> grid2{};

    // instantiate 32-bit Mersenne Twister
    // for random number generation
    // std::mt19937 mt{std::random_device{}()};
    std::mt19937 mt{};
    std::uniform_int_distribution<> nr{0, 100};

    raylib::Vector2 getMidPoint(MapGenerator::Vertex start, MapGenerator::Vertex end, const float &scale);

    void getCorner(int x, int y, std::vector<MapGenerator::Corner> &corners);
};