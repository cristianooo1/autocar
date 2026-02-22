#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Car
{
public:
    Car();
    virtual ~Car();

    // modifiers
    void resetVelocity();
    void setPosition(const float x, const float y);

    // functions
    void move(const float dir_x, const float dir_y);

    sf::Vector2f getSize() const;
    const sf::Vector2f getPosition() const;
    const sf::FloatRect getGlobalBounds() const;

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
    int iteration;

    // physics
    sf::Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;

    void initVariables();
    void initPhysics();
};
