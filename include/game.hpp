#pragma once
#include "car.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

private:
    float dt;
    Car car;
};