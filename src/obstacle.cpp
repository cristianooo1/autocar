#include "obstacle.h"

void Obstacle::initVariables()
{
    this->obstacleWidth = 100.f;
    this->obstacleHeight = 100.f;
}

Obstacle::Obstacle()
{
    /*
    This is the constructor
    Sets up the rectangle that is the obstacle
    Initializes variables
    */

    initVariables();

    obstacle.setSize(sf::Vector2f(this->obstacleWidth, this->obstacleHeight));
    obstacle.setFillColor(sf::Color::Red);
    obstacle.setPosition(sf::Vector2f(100.f, 100.f));
}

Obstacle::~Obstacle()
{
    //
}

const sf::FloatRect Obstacle::getGlobalBounds() const
{
    return this->obstacle.getGlobalBounds();
}

void Obstacle::update()
{
    //
}

void Obstacle::render(sf::RenderTarget &target)
{
    target.draw(this->obstacle);
}