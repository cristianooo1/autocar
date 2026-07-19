#include "game.hpp"

const float CAR_WIDTH{50.0f};
const float CAR_HEIGHT{90.0f};

Game::Game(int mapWidth, int mapHeight)
    : _mapGenerator(mapWidth, mapHeight, 40.0f, 5, 2, 60, 3),
      _car({50.0f, 90.0f},
           {CAR_WIDTH / 2, CAR_HEIGHT * 2 / 3},
           {10.0f, 10.0f})
{
    this->game_window_width = mapWidth;
    this->game_window_height = mapHeight;

    // obstacles = CreateObstacles();

    // GENERATE MAP
    this->grid2D = _mapGenerator.generate2DGrid();
    // this->_boundaries will be a vector with all the edges/lines of the map
    _mapGenerator.getBoundaryEdges(this->grid2D, this->_boundaries);
    // this->_boundaries.push_back(MapGenerator::Line{
    //     .start = {0, 0},
    //     .end = {static_cast<float>(ProjectConfig::WINDOW_WIDTH), 0},

    // });
}

Game::~Game()
{
}

void Game::Draw()
{
    // DrawLineEx({0, 0}, {static_cast<float>(ProjectConfig::WINDOW_WIDTH), 0}, 3.0f, raylib::Color::Green());

    // MAP DRAW
    int idx = 0;
    for (const MapGenerator::Line &line : _boundaries)

    {

        DrawLineEx(line.start, line.end, 3.0f, raylib::Color::Pink());
        // DrawCircleLinesV(line.start, 30.0f, raylib::Color::Black());
        // DrawText(TextFormat("s:%i", idx), line.start.x - 20, line.start.y - 20, 20, RED);

        // DrawCircleLinesV(line.end, 10.0f, raylib::Color::White());
        // DrawText(TextFormat("e:%i", idx), line.end.x + 20, line.end.y + 20, 20, RED);
        idx++;
    }
    idx = 0;

    // CAR DRAW
    _car.Draw();

    // OBSTACLE DRAW
    // for (auto &obstacle : obstacles)
    // {
    //     obstacle.Draw();
    // }

    // RAY CASTING DRAW
    if (this->IsMousePressed)
    {
        _lidar.calculateVisibilityPolygon(_car.GetCarPosition().x, _car.GetCarPosition().y, 1000.0f, _boundaries);
        _lidar.Draw(_car.GetCarPosition());
        int total_rays = _lidar.getNumberRays().rayCast;
        int unique_rays = _lidar.getNumberRays().rayCastUnique;
        std::cout << "total_rays: " << total_rays << " unique_rays: " << unique_rays << "\n";
    }
}

void Game::Update()
{
    _car.Update();
    // raylib::Vector2 coll_point = CheckCollision();
    // DrawCircleV({coll_point.x, coll_point.y}, 2.0f, raylib::Color::Red());
    // std::cout << "coll x: " << coll_point.x << " y: " << coll_point.y << "\n";

    // std::cout << "CAR_POS:x: " << car.GetCarPosition().x << " y: " << car.GetCarPosition().y << "\n";
    // std::cout << "CAR_BOUND:TLx: "
    //           << car.GetCarBoundaries().x
    //           << " TLy: "
    //           << car.GetCarBoundaries().y
    //           << " BRx: "
    //           << car.GetCarBoundaries().z
    //           << " BRy: "
    //           << car.GetCarBoundaries().w
    //           << "\n";
}

void Game::HandleInput()
{
    this->dt = GetFrameTime();
    // std::cout << "dt from game: " << dt << "\n";

    // LINEAR SPEED
    if (IsKeyDown(KEY_UP))
    {
        _car.SetThrottle(-1, dt);
        std::cout << "KEY_UP " << "\n";
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        _car.SetThrottle(1, dt);
        std::cout << "KEY_DOWN " << "\n";
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
        std::cout << "KEY_LEFT " << "\n";
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        _car.SetSteering(1, dt);
        std::cout << "KEY_RIGHT " << "\n";
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

raylib::Vector2 Game::CheckCollision()
{
    raylib::Vector2 coll;
    CheckCollisionLines({_car.GetCarBoundaries()[0].x, _car.GetCarBoundaries()[0].y},
                        {_car.GetCarBoundaries()[1].x, _car.GetCarBoundaries()[1].y},
                        {400.0f, 200.0f},
                        {440.0f, 200.0f},
                        &coll);

    return coll;
}
