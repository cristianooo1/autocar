#include "game.h"

void GameObj::initWindow()
{
    unsigned int cellY = 25;
    unsigned int cellX = 24;
    unsigned int windowSize = 25 * 24;

    this->window.create(sf::VideoMode(
                            {cellY * cellX, cellY * cellX}),
                        "autocar",
                        sf::Style::Titlebar | sf::Style::Close);

    this->window.setFramerateLimit(60);
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
}

void GameObj::updateCarBoundaries(int windowWidth, int windowHeight)
{
    /*
    this->car->getSize().x = carWidth
    this->car->getSize().y = carHeight
    */

    // left wall
    if (this->car->getGlobalBounds().position.x < 0)
    {
        this->car->resetVelocity();
        this->car->setPosition(this->car->getSize().x / 2, this->car->getPosition().y);
        std::cout << "Detected collision with left wall" << std::endl;
    }
    // right wall
    if (this->car->getGlobalBounds().position.x + this->car->getSize().x > windowWidth)
    {
        this->car->resetVelocity();
        this->car->setPosition(windowWidth - this->car->getSize().x / 2, this->car->getPosition().y);
        std::cout << "Detected collision with right wall" << std::endl;
    }
    // top wall
    if (this->car->getGlobalBounds().position.y < 0)
    {
        this->car->resetVelocity();
        this->car->setPosition(this->car->getPosition().x, 2 * this->car->getSize().y / 3);
        std::cout << "Detected collision with top wall" << std::endl;
    }
    // bottom wall
    if (this->car->getGlobalBounds().position.y + this->car->getSize().y > windowHeight)
    {
        this->car->resetVelocity();
        this->car->setPosition(this->car->getPosition().x, windowHeight - this->car->getSize().y / 3);
        std::cout << "Detected collision with bottom wall" << std::endl;
    }
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
    this->updateCarBoundaries(this->getWindow().getSize().x, this->getWindow().getSize().x);
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