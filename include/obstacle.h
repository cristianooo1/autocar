#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Obstacle
{
public:
    Obstacle();
    virtual ~Obstacle();

    const sf::FloatRect getGlobalBounds() const;

    void update();
    void render(sf::RenderTarget &target);

private:
    sf::RectangleShape obstacle;
    float obstacleWidth;
    float obstacleHeight;

    void initVariables();
};
