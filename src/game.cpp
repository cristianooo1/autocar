#include "game.hpp"

Game::Game(int mapWidth, int mapHeight)
    : _mapGenerator(
          mapWidth,
          mapHeight,
          120.0f, // scale
          6,      // rule1
          2,      // rule2
          10,     // fill probability
          4),     // number of generations
      _car(
          {ProjectConfig::CAR_WIDTH, ProjectConfig::CAR_HEIGHT},             // dimensions
          {ProjectConfig::CAR_WIDTH / 2, ProjectConfig::CAR_HEIGHT * 2 / 3}, // origin
          {100.0f, 100.0f})                                                  // position
{
    this->game_window_width = mapWidth;
    this->game_window_height = mapHeight;

    // obstacles = CreateObstacles();

    // GENERATE MAP
    this->grid2D = _mapGenerator.generate2DGrid();
    _mapGenerator.getBoundaryEdges(this->grid2D, this->_boundaries);
}

Game::~Game()
{
}

void Game::Draw()
{
    // MAP DRAW
    if (_boundaries.size() >= 1)
    {

        for (const MapGenerator::Line &line : _boundaries)
        {
            DrawLineEx(line.start, line.end, 3.0f, raylib::Color::Pink());
        }
    }

    // CAR DRAW
    _car.Draw();
    DrawText(TextFormat("%02.03f", _car.GetCarOrientationRad()), _car.GetCarPosition().x - 15, _car.GetCarPosition().y, 20, RED);
    DrawText(TextFormat("car_pos: x=%02.02f, y=%02.02f", _car.GetCarPosition().x, _car.GetCarPosition().y), 0, GetScreenHeight() - 30, 20, RED);

    // LIDAR DRAW
    if (this->IsMousePressed)
    {
        _lidar.getLidarRays(_car.GetCarPosition().x, _car.GetCarPosition().y, PI / 3.0f, 100.0f, _car.GetCarOrientationRad(), _boundaries);
        _lidar.DrawLidarRays(_car.GetCarPosition(), _car.GetCarOrientationRad());
    }

    // OBSTACLE DRAW
    // for (auto &obstacle : obstacles)
    // {
    //     obstacle.Draw();
    // }

    // COLLISION DRAW
    if (this->CheckCollision(this->collision_point))
    {
        DrawCircleV({this->collision_point.x, this->collision_point.y}, 5.0f, raylib::Color::Red());
    }
}

void Game::Update()
{
    _car.Update();
}

void Game::HandleInput()
{
    this->dt = GetFrameTime();
    // std::cout << "dt from game: " << dt << "\n";

    // LINEAR SPEED
    if (IsKeyDown(KEY_UP))
    {
        _car.SetThrottle(-1, dt);
        // std::cout << "KEY_UP " << "\n";
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        _car.SetThrottle(1, dt);
        // std::cout << "KEY_DOWN " << "\n";
    }
    else
    {
        _car.SetThrottle(0, dt);
        // std::cout << "NOTHING up/dow`n " << "\n";
    }

    // ANGULAR ROTATION
    if (IsKeyDown(KEY_LEFT))
    {
        _car.SetSteering(-1, dt);
        // std::cout << "KEY_LEFT " << "\n";
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        _car.SetSteering(1, dt);
        // std::cout << "KEY_RIGHT " << "\n";
    }
    _car.SetSteering(0, dt);
    // std::cout << "always " << "\n";

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        this->IsMousePressed = true;
    }
    else
    {
        this->IsMousePressed = false;
    }

    if (IsKeyDown(KEY_H))
    {
        _car.SetPosition(100.0f, 100.0f);
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    std::vector<Obstacle> obstacles;
    // for (int count{1}; count < 2; count++)
    // {

    //     float x = Lerp(0.0f, 800.0f, obstaclePos(mt));
    //     float y = Lerp(0.0f, 450.0f, obstaclePos(mt));

    //     int test = static_cast<int>(std::round(x));
    //     std::cout << x << ", " << y << "\n";

    //     if (test % 2 == 0)
    //         obstacles.push_back(Obstacle(1, {x, y}));
    //     else
    //         obstacles.push_back(Obstacle(2, {x, y}));
    // }

    obstacles.push_back(Obstacle(2, {400, 200}));
    return obstacles;
}

bool Game::CheckCollision(raylib::Vector2 &collision_point)
{
    for (const MapGenerator::Line &line : this->_boundaries)
    {

        if (CheckCollisionLines({_car.GetCarBoundaries()[0].x, _car.GetCarBoundaries()[0].y},
                                {_car.GetCarBoundaries()[1].x, _car.GetCarBoundaries()[1].y},
                                line.start,
                                line.end,
                                &collision_point) ||
            CheckCollisionLines({_car.GetCarBoundaries()[1].x, _car.GetCarBoundaries()[1].y},
                                {_car.GetCarBoundaries()[3].x, _car.GetCarBoundaries()[3].y},
                                line.start,
                                line.end,
                                &collision_point) ||
            CheckCollisionLines({_car.GetCarBoundaries()[3].x, _car.GetCarBoundaries()[3].y},
                                {_car.GetCarBoundaries()[2].x, _car.GetCarBoundaries()[2].y},
                                line.start,
                                line.end,
                                &collision_point) ||
            CheckCollisionLines({_car.GetCarBoundaries()[2].x, _car.GetCarBoundaries()[2].y},
                                {_car.GetCarBoundaries()[0].x, _car.GetCarBoundaries()[0].y},
                                line.start,
                                line.end,
                                &collision_point))
        {
            return true;
            break;
        }
    }
    return false;
}
