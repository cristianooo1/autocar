#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "car.h"
#include "entity.h"
#include "entityManager.h"

class GameObj
{
public:
    GameObj();
    virtual ~GameObj();

    // Functions
    void updateCar();
    void updateCarBoundaries(int windowWidth, int windowHeight);
    void renderCar();

    void renderEntities();
    void updateEntities();

    void update();
    void render();
    const sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow window;
    Car *car;

    void initWindow();
    void initPlayer();
    void initVariables();

    unsigned int nr_entities;
    void initEntities(unsigned int nrEntities);
};
