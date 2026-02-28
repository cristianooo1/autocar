
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <string>

#include "entity.h"

// this is a singleton
// makes use of the factory method pattern
class EntityManager
{
public:
    static EntityManager &Instance();

    // create new entity and add it
    // to out countainer data structure
    std::shared_ptr<Entity> CreateEntity(std::string name);

    // retrieve entity
    std::shared_ptr<Entity> GetEntity(std::string name);

    int GetEntityCount();

    void renderAll(sf::RenderTarget &target);

    void updateEntities();

private:
    EntityManager() {};
    ~EntityManager() {};

    // container structure
    std::unordered_map<std::string, std::shared_ptr<Entity>> entities;
};