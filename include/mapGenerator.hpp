#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numbers>
#include <random> // for std::mt19937 and std::random_device

#include "raylib-cpp.hpp"

// cellular automata cave generation

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

    raylib::Vector2 midPoint(Vertex start, Vertex end)
    {
        float x1 = start.x;
        float y1 = start.y;
        float x2 = end.x;
        float y2 = end.y;
        return {
            (x1 + ((x2 - x1) / 2.0f)) * _scale,
            (y1 + ((y2 - y1) / 2.0f)) * _scale};
    };

    void getCorner(int x, int y, std::vector<Corner> &corners)
    {
        const Vertex A{x, y};
        const Vertex B{x + 1, y};
        const Vertex C{x + 1, y + 1};
        const Vertex D{x, y + 1};

        corners.push_back(Corner{.position = A, .verticalEdge = D, .horizontalEdge = B});
        corners.push_back(Corner{.position = B, .verticalEdge = C, .horizontalEdge = A});
        corners.push_back(Corner{.position = C, .verticalEdge = B, .horizontalEdge = D});
        corners.push_back(Corner{.position = D, .verticalEdge = A, .horizontalEdge = C});
    };

    // marching squares approach
    // https://chrisakroyd.com/blog/marching-squares/
    void getBoundaryEdges(const std::vector<int> &grid, std::vector<Line> &_boundaryLines)
    {
        int idx, idy;

        for (idy = 0; idy < map_height - 1; idy++)
        {
            for (idx = 0; idx < map_width - 1; idx++)
            {
                std::vector<Corner> cornerss;
                std::vector<Corner> above;
                std::vector<Corner> below;

                int x = idx;
                int y = idy;
                getCorner(x, y, cornerss);

                for (const auto &corner : cornerss)
                {
                    const Vertex pos = corner.position;
                    if (grid[pos.y * map_width + pos.x] != 0)
                    {
                        above.push_back(corner);
                    }
                    else
                    {
                        below.push_back(corner);
                    }
                }

                // case 0 and 15: nothing
                // cases 1,2,4,7,8,11,13,14:

                if (above.size() == 1 || below.size() == 1)
                {
                    Corner cornerr;
                    if (above.size() == 1)
                        cornerr = above[0];
                    else
                    {
                        cornerr = below[0];
                    }

                    _boundaryLines.push_back(Line{.start = midPoint(cornerr.position, cornerr.verticalEdge),
                                                  .end = midPoint(cornerr.position, cornerr.horizontalEdge)});
                }

                if (above.size() == 2)
                {
                    Corner corner1;
                    Corner corner2;
                    corner1 = above[0];
                    corner2 = above[1];

                    int x1 = corner1.position.x;
                    int y1 = corner1.position.y;
                    int x2 = corner2.position.x;
                    int y2 = corner2.position.y;

                    if (x1 == x2 && y1 != y2)
                    {
                        // cases 6 and 9:
                        _boundaryLines.push_back(Line{
                            .start = midPoint({x1, y1}, corner1.horizontalEdge),
                            .end = midPoint({x2, y2}, corner2.horizontalEdge)});
                    }
                    else if (x1 != x2 && y1 == y2)
                    {
                        // cases 3 and 12:
                        _boundaryLines.push_back(Line{
                            .start = midPoint({x1, y1}, corner1.verticalEdge),
                            .end = midPoint({x2, y2}, corner2.verticalEdge)});
                    }
                    else if (x1 != x2 && y1 != y2)
                    {
                        // cases 5 and 10:
                        _boundaryLines.push_back(Line{
                            .start = midPoint({x1, y1}, corner1.horizontalEdge),
                            .end = midPoint({x2, y2}, corner2.verticalEdge)});
                        _boundaryLines.push_back(Line{
                            .start = midPoint({x1, y1}, corner1.verticalEdge),
                            .end = midPoint({x2, y2}, corner2.horizontalEdge)});
                    }
                }
            }
        }
    };

    // void removeBoundaryDuplicates(const std::vector<Line> &_boundaryLines, std::vector<Line> &_newBoundary)
    // {

    //     for (auto idx = 1; idx < _boundaryLines.size(); idx++)
    //     {
    //         const int dx1 = _boundaryLines[idx].start.x - _boundaryLines[idx - 1].start.x;
    //         const int dy1 = _boundaryLines[idx].start.y - _boundaryLines[idx - 1].start.y;

    //         const int dx2 = _boundaryLines[idx].end.x - _boundaryLines[idx].start.x;
    //         const int dy2 = _boundaryLines[idx].end.y - _boundaryLines[idx].start.y;

    //         float m1 = std::sqrt(dx1 * dx1 + dy1 * dy1);
    //         float m2 = std::sqrt(dx2 * dx2 + dy2 * dy2);

    //         // in rad
    //         float theta = std::acos((dx1 * dx2 + dy1 * dy2) / (m1 * m2));

    //         if (theta < 0.175f)
    //         {
    //             raylib::Vector2 Start = _boundaryLines[idx - 1].start;
    //             raylib::Vector2 End = _boundaryLines[idx].end;
    //             _newBoundary.push_back(Line{.start = Start, .end = End});
    //         }
    //     }
    // };

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
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> nr{0, 100};
};