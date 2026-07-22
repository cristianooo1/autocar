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

    Game game(16, 9);
    int display = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    ToggleBorderlessWindowed();

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
