#include <iostream>
#include <string>

#include "game.hpp"
#include "projectConfig.hpp"

#include "mapGenerator.hpp"

int main(int argc, char *argv[])
{

    std::string window_title = "main window";

    raylib::Window window(ProjectConfig::WINDOW_WIDTH, ProjectConfig::WINDOW_HEIGHT, window_title);
    SetTargetFPS(60);
    raylib::Color background = raylib::Color::SkyBlue();

    // Game game(window.GetWidth(), window.GetHeight());
    Game game(80, 80);

    // MAIN GAME LOOP
    // 1. event handling
    // 2. update positions
    // 3. drawing objects
    while (!window.ShouldClose())
    {

        game.HandleInput();

        game.Update();

        window.BeginDrawing();
        window.ClearBackground(background);
        game.Draw();

        window.EndDrawing();
    }

    return 0;
}
