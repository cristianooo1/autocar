#include "game.hpp"

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
    // if (IsKeyDown(KEY_RIGHT))
    // {
    //     car.steering = max_steering_angle_right;
    // }
    // if (IsKeyDown(KEY_LEFT))
    // {
    //     car.steering = max_steering_angle_left;
    // }
    if (IsKeyDown(KEY_UP))
    {
        car.SetThrottle(1.0f);
    }
    if (IsKeyDown(KEY_DOWN))
    {
        car.SetThrottle(-1.0f);
    }
}
