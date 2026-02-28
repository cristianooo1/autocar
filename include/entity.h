#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
public:
    Entity(std::string name);
    virtual ~Entity();

    void setPosition(const float x, const float y);

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;

    virtual void update();
    virtual void render(sf::RenderTarget &target);

private:
    sf::RectangleShape entity;
    std::string entity_name;
    float entityWidth;
    float entityHeight;

    float xPos;
    float yPos;

    void initVariables();
};
