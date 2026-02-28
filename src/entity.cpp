#include "entity.h"

void Entity::initVariables()
{
    this->entityWidth = 100.f;
    this->entityHeight = 100.f;
}

Entity::Entity(std::string name)
{
    /*
    This is the constructor
    Sets up the rectangle that is the entity
    Initializes variables
    */
    this->entity_name = name;

    initVariables();

    entity.setSize(sf::Vector2f(this->entityWidth, this->entityHeight));
    entity.setFillColor(sf::Color::Red);
    entity.setPosition(sf::Vector2f(100.f, 100.f));
}

Entity::~Entity()
{
    //
}

void Entity::setPosition(const float x, const float y)
{
    this->entity.setPosition(sf::Vector2f(x, y));
}

sf::FloatRect Entity::getGlobalBounds() const
{
    return this->entity.getGlobalBounds();
}

sf::Vector2f Entity::getPosition() const
{
    return this->entity.getPosition();
}

void Entity::update()
{
    //
}

void Entity::render(sf::RenderTarget &target)
{
    target.draw(this->entity);

    // view origin of entity
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Yellow);
    circle.setRadius(5.f);
    circle.setPosition(this->entity.getPosition());
    target.draw(circle);
}