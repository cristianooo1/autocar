#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "car.h"

class GameObj
{
public:
    GameObj();
    virtual ~GameObj();

    // Functions
    void updateCar();
    void updateCarBoundaries(int windowWidth, int windowHeight);
    void update();
    void renderCar();
    void render();
    const sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow window;
    // const std::optional<sf::Event> ev;
    // sf::Event ev;
    Car *car;

    void initWindow();
    void initPlayer();
};
