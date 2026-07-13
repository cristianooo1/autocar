#include "obstacle.hpp"

Obstacle::Obstacle(int type, raylib::Vector2 position)
{
    this->obst_type = type;
    this->obst_position = position;

    switch (type)
    {
    case 1:
        obst_rectangle.SetSize(10.0f, 10.0f);
        obst_color = raylib::Color::Yellow();
        break;
    case 2:
        obst_rectangle.SetSize(40.0f, 40.0f);
        obst_color = raylib::Color::Green();
        break;
    default:
        obst_rectangle.SetSize(10.0f, 10.0f);
        break;
    }
}

void Obstacle::Update()
{
}

void Obstacle::Draw()
{
    obst_rectangle.SetPosition(obst_position);
    obst_rectangle.Draw(obst_color);
}

int Obstacle::GetType()
{
    return obst_type;
}
