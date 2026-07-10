#include "car.hpp"
#include <iostream>
#include <string>

Car::Car()
{
    car_dimensions = raylib::Vector2(50.0f, 100.0f);
    car_rectangle.SetSize(car_dimensions);

    car_origin.SetSize(10.0f, 10.0f);

    car_position = raylib::Vector2{100.0f, 100.0f};

    this->throttle = 0.0;
}

Car::~Car()
{
}

void Car::Draw()
{
    car_rectangle.SetPosition(this->car_position);
    car_origin.SetPosition(this->car_position);

    car_rectangle.Draw(raylib::Vector2(car_dimensions.x / 2 - 5,
                                       car_dimensions.y / 2 - 5),
                       0.0f,
                       raylib::Color::Blue());

    car_origin.Draw(raylib::Vector2(0, 0),
                    0.0f,
                    raylib::Color::Red());

    // std::cout << car_rectangle.x << " and " << car_rectangle.y << "\n";
}

void Car::SetThrottle(float newThrottle)
{
    this->throttle = newThrottle;
}

void Car::UpdatePosition()
{
    car_position.y -= throttle;
}