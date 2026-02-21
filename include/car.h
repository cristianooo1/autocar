#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Car
{
public:
    Car();
    virtual ~Car();

    // Functions
    void updateMovement();
    void update();
    void render(sf::RenderTarget &target);

    void moveOffset(sf::Vector2f velocity);
    void moveAbs(float x, float y);

    sf::Vector2f getSize() const;
    sf::Vector2f getPos() const;
    sf::FloatRect getGBounds() const;

    // void clampBoundaries(int windowWidth, int windowHeight);

private:
    sf::RectangleShape shape;
    float carWidth = 60.f;
    float carHeight = 120.f;
    float vel = 1.f;
};
