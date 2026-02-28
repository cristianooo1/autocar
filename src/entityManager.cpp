#include "entityManager.h"

EntityManager &EntityManager::Instance()
{
    static EntityManager *instance = new EntityManager();
    return *instance;
}

std::shared_ptr<Entity> EntityManager::CreateEntity(std::string name)
{
    // create new entity
    std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(name);

    // store entity in our container collection
    this->entities.insert(std::make_pair(name, newEntity));

    // return this new entity to the client
    return newEntity;
}

std::shared_ptr<Entity> EntityManager::GetEntity(std::string name)
{
    return this->entities[name];
}

int EntityManager::GetEntityCount()
{
    return this->entities.size();
}

void EntityManager::renderAll(sf::RenderTarget &target)
{
    for (auto it = this->entities.begin(); it != this->entities.end(); it++)
    {
        // std::string entityName = it->first;
        it->second->render(target);
    }
}

void EntityManager::updateEntities()
{
    for (int i = 0; i < this->GetEntityCount(); i++)
    {
        std::shared_ptr<Entity> ent = EntityManager::Instance().GetEntity("tree_test" + std::to_string(i));
        float x = ent->getPosition().x;
        float y = ent->getPosition().y;

        if (x <= 400.f)
        {
            ent->setPosition(x + 1.f, y);
        }
    }
}
