#include "car.hpp"
#include <iostream>
#include <string>

Car::Car()
{
    car_rectangle.SetSize(
        raylib::Vector2(50.0f, 50.0f));

    car_rectangle.SetPosition(
        raylib::Vector2(50.0f, 50.0f));

    car_position = raylib::Vector2{50.0f, 50.0f};

    this->speed = 10.0;
}

Car::~Car()
{
}

void Car::Draw()
{
    car_rectangle.Draw(raylib::Color::Blue());
    car_rectangle.SetPosition(this->car_position);
}

void Car::Update()
{
    if (IsKeyDown(KEY_RIGHT))
    {
        car_position.x += speed;
        std::cout << "KEY_RIGHT pressed" << "\n";
        std::cout << car_position.x << "\n";
    }
    if (IsKeyDown(KEY_LEFT))
    {
        car_position.x -= speed;
        std::cout << "KEY_LEFT pressed" << "\n";
    }
    if (IsKeyDown(KEY_UP))
    {
        car_position.y -= speed;
        std::cout << "KEY_UP pressed" << "\n";
    }
    if (IsKeyDown(KEY_DOWN))
    {
        car_position.y += speed;
        std::cout << "KEY_DOWN pressed" << "\n";
    }
}