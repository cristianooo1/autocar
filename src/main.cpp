#include <SFML/Graphics.hpp>
#include <iostream>

class Car
{
public:
    Car()
    {
        shape.setSize(sf::Vector2f(carWidth, carHeight));
        shape.setOrigin(sf::Vector2f(carWidth / 2, 2 * carHeight / 3));
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(sf::Vector2f(100.f, 100.f));
    }

    void moveOffset(sf::Vector2f velocity)
    {
        shape.move(velocity);
        this->vel = velocity.x;
    }

    void moveAbs(float x, float y)
    {
        shape.setPosition(sf::Vector2f(x, y));
    }

    sf::Vector2f getPos() const
    {
        return shape.getPosition();
        // return shape.getGlobalBounds();
    }

    sf::FloatRect getGBounds() const
    {
        return shape.getGlobalBounds();
    }

    void clampBoundaries(int windowWidth, int windowHeight)
    {
        // left wall
        if (getGBounds().position.x < 0)
            moveAbs(carWidth / 2, getPos().y);

        // right wall
        if (getGBounds().position.x + carWidth > windowWidth)
            moveAbs(windowWidth - carWidth / 2, getPos().y);

        // top wall
        if (getGBounds().position.y < 0)
            moveAbs(getPos().x, 2 * carHeight / 3);

        // bottom wall
        if (getGBounds().position.y + carHeight > windowHeight)
            moveAbs(getPos().x, windowHeight - carHeight / 3);
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(shape);
    }

private:
    // sf::CircleShape shape;
    sf::RectangleShape shape;
    float carWidth = 60.f;
    float carHeight = 120.f;
    float vel = 2.f;
};

void wasdMove(Car &cr, sf::Vector2f(vel))
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        cr.moveOffset(sf::Vector2f(0.f, -vel.y));
        std::cout << "W is pressed" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        cr.moveOffset(sf::Vector2f(-vel.x, 0.f));
        std::cout << "A is pressed" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        cr.moveOffset(sf::Vector2f(0.f, vel.y));
        std::cout << "S is pressed" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        cr.moveOffset(sf::Vector2f(+vel.x, 0.f));
        std::cout << "D is pressed" << std::endl;
    }
}

int main()
{
    unsigned int cellY = 25;
    unsigned int cellX = 24;
    unsigned int windowSize = 25 * 24;

    int iteration = 0;

    sf::RenderWindow window(sf::VideoMode({cellY * cellX, cellY * cellX}), "autocar", sf::Style::Titlebar);

    Car car;
    sf::Vector2f velocity(1.f, 1.f);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            wasdMove(car, velocity);
        }

        window.clear(sf::Color::Green);
        car.render(window);
        car.clampBoundaries(windowSize, windowSize);

        iteration++;
        if (iteration == 500)
        {
            float currX = car.getPos().x;
            float currY = car.getPos().y;
            std::cout << "curr car pos x=" << currX << " and pos y=" << currY << std::endl;

            float gx = car.getGBounds().position.x;
            float gy = car.getGBounds().position.y;
            std::cout << "curr car pos gx=" << gx << " and pos gy=" << gy << std::endl;

            iteration = 0;
        }
        window.display();
        // std::cout << "window size x " << window.getSize().x << "and y " << window.getSize().y << std::endl;
    }

    return 0;
}