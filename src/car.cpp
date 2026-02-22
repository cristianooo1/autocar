#include "car.h"

void Car::initVariables()
{
    this->moving = false;
    this->carWidth = 60.f;
    this->carHeight = 120.f;
    this->vel = 1.f;
}

void Car::initPhysics()
{
    this->velocityMax = 10.f;
    this->velocityMin = 1.f;
    this->acceleration = 3.f;
    this->drag = 0.93f;
}

Car::Car()
{
    /*
    This is the constructor
    Sets up the rectangle that is the car
    Initializes variables
    */

    initVariables();
    initPhysics();

    shape.setSize(sf::Vector2f(carWidth, carHeight));
    shape.setOrigin(sf::Vector2f(carWidth / 2, 2 * carHeight / 3));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(sf::Vector2f(100.f, 100.f));
}

Car::~Car()
{
    //
}

void Car::move(const float dir_x, const float dir_y)
{
    // acceleration
    this->velocity.x += dir_x * this->acceleration;
    this->velocity.y += dir_y * this->acceleration;

    // limit velocity
    if (std::abs(this->velocity.x) > this->velocityMax)
        this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1.f : 1.f);

    if (std::abs(this->velocity.y) > this->velocityMax)
        this->velocity.y = this->velocityMax * ((this->velocity.y < 0) ? -1.f : 1.f);
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

void Car::updatePhysics()
{
    // deceleration
    this->velocity *= this->drag;

    // limit deceleration
    if (std::abs(this->velocity.x) < this->velocityMin)
        this->velocity.x = 0.f;

    if (std::abs(this->velocity.y) < this->velocityMin)
        this->velocity.y = 0.f;

    this->shape.move(this->velocity);
}

void Car::updateMovement()
{
    this->moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        // this->moveOffset(sf::Vector2f(0.f, -vel));
        this->move(0.f, -1.f);
        this->moving = true;
        std::cout << "W is pressed" << std::endl;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // this->moveOffset(sf::Vector2f(0.f, vel));
        this->move(0.f, 1.f);
        this->moving = true;
        std::cout << "S is pressed" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // LEFT
    {
        // this->moveOffset(sf::Vector2f(-vel, 0.f));
        this->move(-1.f, 0.f);
        this->moving = true;
        std::cout << "A is pressed" << std::endl;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // RIGHT
    {
        // this->moveOffset(sf::Vector2f(vel, 0.f));
        this->move(1.f, 0.f);
        this->moving = true;
        std::cout << "D is pressed" << std::endl;
    }
}

void Car::update()
{
    this->updateMovement();
    this->updatePhysics();
}

void Car::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}
