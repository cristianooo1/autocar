#include "car.h"

Car::Car()
{
    shape.setSize(sf::Vector2f(carWidth, carHeight));
    shape.setOrigin(sf::Vector2f(carWidth / 2, 2 * carHeight / 3));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(sf::Vector2f(100.f, 100.f));
}

Car::~Car()
{
    //
}

void Car::updateMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->moveOffset(sf::Vector2f(0.f, -vel));
        std::cout << "W is pressed" << std::endl;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->moveOffset(sf::Vector2f(0.f, vel));
        std::cout << "S is pressed" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->moveOffset(sf::Vector2f(-vel, 0.f));
        std::cout << "A is pressed" << std::endl;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->moveOffset(sf::Vector2f(+vel, 0.f));
        std::cout << "D is pressed" << std::endl;
    }
}

void Car::update()
{
    this->updateMovement();
    // this->clampBoundaries();
}

void Car::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}

void Car::moveOffset(sf::Vector2f velocity)
{
    this->shape.move(velocity);
    // this->vel = velocity.x;
}

void Car::moveAbs(float x, float y)
{
    this->shape.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Car::getSize() const
{
    return shape.getSize();
}

sf::Vector2f Car::getPos() const
{
    return shape.getPosition();
}

sf::FloatRect Car::getGBounds() const
{
    return shape.getGlobalBounds();
}

// void Car::clampBoundaries(int windowWidth, int windowHeight)
// {
//     // left wall
//     if (getGBounds().position.x < 0)
//         moveAbs(carWidth / 2, getPos().y);

//     // right wall
//     if (getGBounds().position.x + carWidth > windowWidth)
//         moveAbs(windowWidth - carWidth / 2, getPos().y);

//     // top wall
//     if (getGBounds().position.y < 0)
//         moveAbs(getPos().x, 2 * carHeight / 3);

//     // bottom wall
//     if (getGBounds().position.y + carHeight > windowHeight)
//         moveAbs(getPos().x, windowHeight - carHeight / 3);
// }
