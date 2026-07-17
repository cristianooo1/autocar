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
    MapGenerator(int width, int height, int rule1, int rule2, int fillprob);
    ~MapGenerator();

    int pickRand();

    void initMap();

    void generationStep();

    void printMap();

private:
    int map_width{};
    int map_height{};
    int r1_cutoff{5};
    int r2_cutoff{2};
    int fillProb{40};

    int length = map_width * map_height;

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