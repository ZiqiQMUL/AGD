#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../utils/Bitmask.h"
#include "../components/Components.h"
#include <map>

using EntityID = unsigned int;
enum class EntityType
{
    UNDEFINED = -1,
    PLAYER = 0,
    POTION = 1,
    LOG = 2,
    FIRE = 3
};

class Game; 
class PositionComponent;
class GraphicsComponent;
class BoxColliderComponent;
class TTLComponent;
class InputComponent;
class VelocityComponent;
class LogicComponent;

class Entity
{
public:

    // Constructors & Desctrutors
    Entity();
    Entity(EntityType et);
    ~Entity();

    // Init & update
    virtual void init(const std::string& TextureFile, std::shared_ptr<GraphicsComponent> GraphicsComp);

    // Getters & Setters
    void setID(EntityID entId) { id = entId; }
    EntityID getID() const { return id; }
    const sf::Vector2f& getSpriteScale() const;
    sf::Vector2i getTextureSize() const;
    EntityType getEntityType() const { return type; }


    // Add a bool member variable "deleted" to this class.
    bool isDeleted() const { return deleted; }
    void deleteEntity() { deleted = true; }

    //1d 2.1 Bitmask
    const Bitmask& getComponentSet() const { return componentSet; }
    void addComponent(std::shared_ptr<Component> _ComponentPtr);

    //1d 2.2 Comparing masks
    bool hasComponent(Bitmask mask) const;
    const Component* getComponent(ComponentID _ID)const;
    Component* getComponent(ComponentID _ID);


protected:

    EntityType type;
    EntityID id;

    //1d 5.1
    std::map<ComponentID, std::shared_ptr<Component>> components;

    //1d 2.1
    Bitmask componentSet;

    bool deleted;
};
