#include "mapGenerator.hpp"

MapGenerator::MapGenerator(int width, int height, float scale, int rule1, int rule2, int fillprob, int nr_generations)
    /*
    CELLULAR AUTOMATA CAVE GENERATION
    https://www.roguebasin.com/index.php/Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels
    */
    : map_width{width},
      map_height{height},
      _scale{scale},
      r1_cutoff{rule1},
      r2_cutoff{rule2},
      fillProb{fillprob},
      generations{nr_generations}
{
}

MapGenerator::~MapGenerator()
{
}

int MapGenerator::pickRand()
{
    if (this->nr(mt) < this->fillProb)
        return 1;
    else
        return 0;
}

void MapGenerator::initMap()
{
    int idx;
    int idy;
    grid1.resize(map_width * map_height);
    grid2.resize(map_width * map_height);

    // initialize map interior with random noise
    for (idy = 1; idy < map_height - 1; idy++)
    {
        for (idx = 1; idx < map_width - 1; idx++)
        {
            grid1[idy * map_width + idx] = pickRand();
        }
    }

    // initialize write-buffer
    for (idy = 0; idy < map_height; idy++)
    {
        for (idx = 0; idx < map_width; idx++)
        {
            grid2[idy * map_width + idx] = 1;
        }
    }

    // add borders=walls to primary read-buffer map
    for (idy = 0; idy < map_height; idy++)
    {
        grid1[idy * map_width] = 1;
        grid1[idy * map_width + map_width - 1] = 1;
    }

    for (idx = 0; idx < map_width; idx++)
    {
        grid1[idx] = 1;
        grid1[(map_height - 1) * map_width + idx] = 1;
    }

    // DEBUGGING
    // for (idy = 0; idy < map_height; idy++)
    // {
    //     for (idx = 0; idx < map_width; idx++)
    //     {
    //         std::cout << grid2[idy * map_width + idx] << " ";
    //     }
    //     std::cout << "\n";
    // }
}

void MapGenerator::generationStep()
{
    int idx, idy, ii, jj;

    // only iterate through map interior, exterior is already WALL=1
    for (idy = 1; idy < map_height - 1; idy++)
    {
        for (idx = 1; idx < map_width - 1; idx++)
        {
            int count_r1 = 0;
            int count_r2 = 0;

            // iterate through 3x3 neighborhood grid for radius 1
            for (ii = -1; ii <= 1; ii++)
            {
                for (jj = -1; jj <= 1; jj++)
                {
                    if (grid1[(idy + ii) * map_width + (idx + jj)] != 0)
                    {
                        count_r1++;
                    }
                }
            }

            // iterate through 5x5 neighborhood grid for radius 2
            for (ii = idy - 2; ii <= idy + 2; ii++)
            {
                for (jj = idx - 2; jj <= idx + 2; jj++)
                {
                    // skip corners
                    if (std::abs(ii - idy) == 2 && std::abs(jj - idx) == 2)
                    {
                        continue;
                    }

                    // skip if coordinates are outside map boundary
                    if (ii < 0 || jj < 0 || ii >= map_height || jj >= map_width)
                    {
                        continue;
                    }

                    if (grid1[ii * map_width + jj] != 0)
                    {
                        count_r2++;
                    }
                }
            }

            // convert to walls/floors based on rules
            // update the write buffer with the next state
            if (count_r1 >= r1_cutoff || count_r2 <= r2_cutoff)
            {
                grid2[idy * map_width + idx] = 1;
            }
            else
            {
                grid2[idy * map_width + idx] = 0;
            }
        }
    }

    // update the read buffer with the calculated state
    std::swap(grid1, grid2);
}

void MapGenerator::printMap()
{
    for (int idy = 0; idy < map_height; idy++)
    {
        for (int idx = 0; idx < map_width; idx++)
        {
            std::cout << grid1[idy * map_width + idx] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<int> MapGenerator::generate2DGrid()
{
    initMap();
    for (int i = 0; i < generations; i++)
    {
        generationStep();
    }
    printMap();
    return grid1;
}

raylib::Vector2 MapGenerator::getMidPoint(MapGenerator::Vertex start, MapGenerator::Vertex end, const float &scale)
{
    float x1 = start.x;
    float y1 = start.y;
    float x2 = end.x;
    float y2 = end.y;
    return {
        (x1 + ((x2 - x1) / 2.0f)) * scale,
        (y1 + ((y2 - y1) / 2.0f)) * scale};
};

void MapGenerator::getCorner(int x, int y, std::vector<MapGenerator::Corner> &corners)
{
    const MapGenerator::Vertex A{x, y};
    const MapGenerator::Vertex B{x + 1, y};
    const MapGenerator::Vertex C{x + 1, y + 1};
    const MapGenerator::Vertex D{x, y + 1};

    corners.push_back(MapGenerator::Corner{.position = A, .verticalEdge = D, .horizontalEdge = B});
    corners.push_back(MapGenerator::Corner{.position = B, .verticalEdge = C, .horizontalEdge = A});
    corners.push_back(MapGenerator::Corner{.position = C, .verticalEdge = B, .horizontalEdge = D});
    corners.push_back(MapGenerator::Corner{.position = D, .verticalEdge = A, .horizontalEdge = C});
};

void MapGenerator::getBoundaryEdges(const std::vector<int> &grid, std::vector<MapGenerator::Line> &_boundaryLines)
{
    /*
    marching squares approach
    https://chrisakroyd.com/blog/marching-squares/
    */

    int idx, idy;

    for (idy = 1; idy < map_height - 2; idy++)
    {
        for (idx = 1; idx < map_width - 2; idx++)
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

                _boundaryLines.push_back(Line{.start = getMidPoint(cornerr.position, cornerr.verticalEdge, this->_scale),
                                              .end = getMidPoint(cornerr.position, cornerr.horizontalEdge, this->_scale)});
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
                        .start = getMidPoint({x1, y1}, corner1.horizontalEdge, this->_scale),
                        .end = getMidPoint({x2, y2}, corner2.horizontalEdge, this->_scale)});
                }
                else if (x1 != x2 && y1 == y2)
                {
                    // cases 3 and 12:
                    _boundaryLines.push_back(Line{
                        .start = getMidPoint({x1, y1}, corner1.verticalEdge, this->_scale),
                        .end = getMidPoint({x2, y2}, corner2.verticalEdge, this->_scale)});
                }
                else if (x1 != x2 && y1 != y2)
                {
                    // cases 5 and 10:
                    _boundaryLines.push_back(Line{
                        .start = getMidPoint({x1, y1}, corner1.horizontalEdge, this->_scale),
                        .end = getMidPoint({x2, y2}, corner2.verticalEdge, this->_scale)});
                    _boundaryLines.push_back(Line{
                        .start = getMidPoint({x1, y1}, corner1.verticalEdge, this->_scale),
                        .end = getMidPoint({x2, y2}, corner2.horizontalEdge, this->_scale)});
                }
            }
        }
    }

    // TOP
    _boundaryLines.push_back(MapGenerator::Line{
        .start = {0, 0},
        .end = {map_width * _scale, 0},
    });
    // BOTTOM
    _boundaryLines.push_back(MapGenerator::Line{
        .start = {0, map_height * _scale},
        .end = {map_width * _scale, map_height * _scale},
    });
    // LEFT
    _boundaryLines.push_back(MapGenerator::Line{
        .start = {0, 0},
        .end = {0, map_height * _scale},
    });
    // RIGHT
    _boundaryLines.push_back(MapGenerator::Line{
        .start = {map_width * _scale, 0},
        .end = {map_width * _scale, map_height * _scale},
    });
};
