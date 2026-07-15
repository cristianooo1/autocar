#include <iostream>
#include <string>

#include "game.hpp"

int main(int argc, char *argv[])
{
    const int window_width = 800;
    const int window_height = 450;
    std::string window_title = "main window";

    raylib::Window window(window_width, window_height, window_title);
    SetTargetFPS(60);
    raylib::Color background = raylib::Color::SkyBlue();

    Game game;

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
