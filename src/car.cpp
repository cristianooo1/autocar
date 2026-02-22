#include "car.h"

void Car::initVariables()
{
    this->moving = false;
    this->carWidth = 100.f;
    this->carHeight = 100.f;
    this->vel = 1.f;
    this->iteration = 0;
}

void Car::initPhysics()
{
    this->velocityMax = 12.f;
    this->velocityMin = 1.f;
    this->acceleration = 2.f;
    this->drag = 0.95f;
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

void Car::setPosition(const float x, const float y)
{
    this->shape.setPosition(sf::Vector2f(x, y));
}

void Car::resetVelocity()
{
    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
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

sf::Vector2f Car::getSize() const
{
    return this->shape.getSize();
}

const sf::Vector2f Car::getPosition() const
{
    return this->shape.getPosition();
}

const sf::FloatRect Car::getGlobalBounds() const
{
    return this->shape.getGlobalBounds();
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
        this->move(0.f, -1.f);
        this->moving = true;
        std::cout << "W is pressed" << std::endl;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->move(0.f, 1.f);
        this->moving = true;
        std::cout << "S is pressed" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // LEFT
    {
        this->move(-1.f, 0.f);
        this->moving = true;
        std::cout << "A is pressed" << std::endl;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // RIGHT
    {
        this->move(1.f, 0.f);
        this->moving = true;
        std::cout << "D is pressed" << std::endl;
    }
}

void Car::update()
{
    this->updateMovement();
    this->updatePhysics();

    // iteration++;
    // if (iteration == 100)
    // {
    //     std::cout << "curr pos_x=" << this->getPos().x << " pos_y=" << this->getPos().y << std::endl;
    //     std::cout << "curr g_x=" << this->getGlobalBounds().position.x << " g_y=" << this->getGlobalBounds().position.y << std::endl;
    //     iteration = 0;
    // }
}

void Car::render(sf::RenderTarget &target)
{
    target.draw(this->shape);

    // view origin of car
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(2.f);
    circle.setPosition(this->shape.getPosition());
    target.draw(circle);
}
