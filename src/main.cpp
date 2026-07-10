// #include "raylib-cpp.hpp"
#include <iostream>
#include <string>

#include "car.hpp"

int main(int argc, char *argv[])
{
    const int window_width = 800;
    const int window_height = 450;
    std::string window_title = "main window";

    raylib::Window window(window_width, window_width, window_title);
    SetTargetFPS(60);
    raylib::Color background = raylib::Color::SkyBlue();

    Car car1;
    while (!window.ShouldClose())
    {
        car1.Update();
        window.BeginDrawing();

        window.ClearBackground(background);

        car1.Draw();

        window.EndDrawing();
    }

    return 0;
}
