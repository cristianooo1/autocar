#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Car
{
public:
    Car();
    virtual ~Car();

    // Functions
    void move(const float dir_x, const float dir_y);
    void moveOffset(sf::Vector2f velocity);
    void moveAbs(float x, float y);

    sf::Vector2f getSize() const;
    sf::Vector2f getPos() const;
    sf::FloatRect getGBounds() const;

    void updatePhysics();
    void updateMovement();

    void update();
    void render(sf::RenderTarget &target);

private:
    sf::RectangleShape shape;
    float carWidth;
    float carHeight;
    float vel;
    bool moving;

    // physics
    sf::Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;

    void initVariables();
    void initPhysics();
};
