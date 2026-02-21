#include "game.h"

void GameObj::initWindow()
{
    unsigned int cellY = 25;
    unsigned int cellX = 24;
    unsigned int windowSize = 25 * 24;

    this->window.create(sf::VideoMode(
                            {cellY * cellX, cellY * cellX}),
                        "autocar",
                        sf::Style::Titlebar);
}

void GameObj::initPlayer()
{
    this->car = new Car();
}

GameObj::GameObj()
{
    this->initWindow();
    this->initPlayer();
}

GameObj::~GameObj()
{
    delete this->car;
}

void GameObj::updateCar()
{
    this->car->update();
    this->updateCarBoundaries(25 * 24, 25 * 24);
}

void GameObj::updateCarBoundaries(int windowWidth, int windowHeight)
{
    /*
    this->car->getSize().x = carWidth
    this->car->getSize().y = carHeight
    */

    // left wall
    if (this->car->getGBounds().position.x < 0)
        this->car->moveAbs(this->car->getSize().x / 2, this->car->getPos().y);

    // right wall
    if (this->car->getGBounds().position.x + this->car->getSize().x > windowWidth)
        this->car->moveAbs(windowWidth - this->car->getSize().x / 2, this->car->getPos().y);

    // top wall
    if (this->car->getGBounds().position.y < 0)
        this->car->moveAbs(this->car->getPos().x, 2 * this->car->getSize().y / 3);

    // bottom wall
    if (this->car->getGBounds().position.y + this->car->getSize().y > windowHeight)
        this->car->moveAbs(this->car->getPos().x, windowHeight - this->car->getSize().y / 3);
}

void GameObj::update()
{
    // polling window events
    while (const std::optional event = this->window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            this->window.close();
    }
    this->updateCar();
}

void GameObj::renderCar()
{
    this->car->render(this->window);
}

void GameObj::render()
{
    this->window.clear(sf::Color::Green);

    // render game
    this->renderCar();

    window.display();
}

const sf::RenderWindow &GameObj::getWindow() const
{
    return this->window;
}