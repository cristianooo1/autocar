#include "game.hpp"

Game::Game()
{

    obstacles = CreateObstacles();
}

// destructor ?
Game::~Game()
{
}

void Game::Draw()
{
    car.Draw();

    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }
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
        // std::cout << "NOTHING up/dow`n " << "\n";
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

std::vector<Obstacle> Game::CreateObstacles()
{
    std::vector<Obstacle> obstacles;
    for (int count{1}; count < 100; count++)
    {

        float x = Lerp(0.0f, 800.0f, obstaclePos(mt));
        float y = Lerp(0.0f, 450.0f, obstaclePos(mt));

        int test = static_cast<int>(std::round(x));
        std::cout << x << ", " << y << "\n";

        if (test % 2 == 0)
            obstacles.push_back(Obstacle(1, {x, y}));
        else
            obstacles.push_back(Obstacle(2, {x, y}));
    }

    return obstacles;
}
