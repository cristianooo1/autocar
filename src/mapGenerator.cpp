#include "mapGenerator.hpp"

MapGenerator::MapGenerator(int width, int height, int rule1, int rule2, int fillprob)
    : map_width{width},
      map_height{height},
      r1_cutoff{rule1},
      r2_cutoff{rule2},
      fillProb{fillprob}
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
    for (idy = 1; idy < map_height - 1; idy++)
    {
        for (idx = 1; idx < map_width - 1; idx++)
        {
            grid1[idy * map_width + idx] = grid2[idy * map_width + idx];
        }
    }
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
