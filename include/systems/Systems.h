#pragma once
#include "../utils/Bitmask.h"
#include "../entities/Entity.h"
class Game;

class System
{
protected:
    Bitmask componentMask;

public:
    virtual void update(Game* game, std::shared_ptr<Entity> entity, float elapsed) {
        if (validate(entity)) {
            updateComponents(game, entity, elapsed);
        }
    }
    virtual void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) = 0;
    bool validate(std::shared_ptr<Entity> entity) const { return entity->hasComponent(componentMask); }

protected:
    void addComponentToMask(ComponentID component) {
        componentMask.turnOnBit(static_cast<int>(component));
    }

    template <typename ComponentType>
    ComponentType* getComponentAndCheck(Entity* entity, ComponentID componentID) {
        auto component = dynamic_cast<ComponentType*>(entity->getComponent(componentID));
        if (component == nullptr) {
            throw std::exception("Null Component");
        }
        return component;
    }
};

class TTLSystem : public System {
public:
    TTLSystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};

class InputSystem : public System
{
public:
    InputSystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};

class MovementSystem : public System
{
public:
    MovementSystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};

class GraphicsSystem : public System
{
public:
    GraphicsSystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};

class ColliderSystem : public System
{
public:
    ColliderSystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};

class GameplaySystem : public System
{
public:
    GameplaySystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};

class PrintDebugSystem : public System
{
public:
    PrintDebugSystem();
    void updateComponents(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};
