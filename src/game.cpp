#include "game.hpp"
#include <iostream>

Game::Game()
{
}

// destructor ?
Game::~Game()
{
}

void Game::Draw()
{
    car.Draw();
}

void Game::Update()
{
    car.UpdatePosition();
}

void Game::HandleInput()
{
    this->dt = GetFrameTime();
    // std::cout << "dt from game: " << dt << "\n";

    // LINEAR SPEED
    if (IsKeyDown(KEY_UP))
    {
        car.SetThrottle(-1, dt);
        std::cout << "KEY_UP " << "\n";
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        car.SetThrottle(1, dt);
        std::cout << "KEY_DOWN " << "\n";
    }
    else
    {
        car.SetThrottle(0, dt);
        // std::cout << "NOTHING up/down " << "\n";
    }

    // ANGULAR ROTATION
    if (IsKeyDown(KEY_LEFT))
    {
        car.SetSteering(-1, dt);
        std::cout << "KEY_LEFT " << "\n";
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        car.SetSteering(1, dt);
        std::cout << "KEY_RIGHT " << "\n";
    }
    car.SetSteering(0, dt);
    // std::cout << "always " << "\n";
}
