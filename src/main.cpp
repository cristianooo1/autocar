#include <SFML/Graphics.hpp>
#include <iostream>


class Car
{
    public:
        Car() 
        { 
            shape.setRadius(50.f); 
            shape.setFillColor(sf::Color::Black); 
            shape.setPosition(sf::Vector2f(x, y)); 
        } 
        
        void movev(const sf::Vector2f& velocity) 
        { 
            shape.move(velocity); 
        } 

        void render(sf::RenderWindow& window)
        {
            window.draw(shape);
        }
        
    private:
        sf::CircleShape shape;
        float x = 50.f; 
        float y = 50.f;

};


int main()
{
    unsigned int cellY = 25;
    unsigned int cellX = 24;
    

    sf::RenderWindow window(sf::VideoMode({cellY*cellX, cellY*cellX}), "autocar", sf::Style::Titlebar);


    Car car;
    sf::Vector2f velocity(10.f, 10.f);


    while (window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close(); 



            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                {
                    car.movev(sf::Vector2f(0.f, -velocity.y));
                    std::cout << "W is pressed" << std::endl;
                }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                {
                    car.movev(sf::Vector2f(-velocity.x, 0.f));
                    std::cout << "A is pressed" << std::endl;
                }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                {
                    car.movev(sf::Vector2f(0.f, velocity.y));
                    std::cout << "S is pressed" << std::endl;
                }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {
                    car.movev(sf::Vector2f(+velocity.x, 0.f));
                    std::cout << "D is pressed" << std::endl;
                }



        }

        window.clear(sf::Color::Green);
        car.render(window);
        window.display();
        std::cout << "window size x " << window.getSize().x << "and y " << window.getSize().y << std::endl;

    }

    return 0;
}