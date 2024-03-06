#include "../entities/Entity.h"
#include "../graphics/Window.h"
#include "../components/PositionComponent.h"
#include "../components/GraphicsComponent.h"
#include "../components/TTLComponent.h"
#include <iostream>


//1c 6.1 positionComp->PositionComponent

Entity::Entity() :
    id(0),
    type(EntityType::UNDEFINED),
    deleted(false)
{
    addComponent(std::make_shared<PositionComponent>());
}

Entity::Entity(EntityType et) :
    id(0),
    type(et),
    deleted(false)
{
    addComponent(std::make_shared<PositionComponent>());
}


Entity::~Entity()
{
}


void Entity::init(const std::string& TextureFile, std::shared_ptr<GraphicsComponent> GraphicsComp)
{
    addComponent(GraphicsComp);
    auto graphicsComp = dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS));
    auto positionComp = dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION));
    graphicsComp->init(TextureFile);
    graphicsComp->setPosition(positionComp->getPosition().x, positionComp->getPosition().y);
}


const sf::Vector2f& Entity::getSpriteScale() const
{
    auto graphics = dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS));
    return graphics->getSpriteScale();
}

sf::Vector2i Entity::getTextureSize() const
{
    auto graphics = dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS));
    return graphics->getTextureSize();
}

bool Entity::hasComponent(Bitmask bitmask) const
{
    return componentSet.contains(bitmask);
}

void Entity::addComponent(std::shared_ptr<Component> _ComponentPtr)
{
    auto id = _ComponentPtr->getID();
    components[id] = _ComponentPtr;
    componentSet.turnOnBit(static_cast<uint32_t>(id));
}

Component* Entity::getComponent(ComponentID id)
{
    return components[id].get();
}

const Component* Entity::getComponent(ComponentID id)const
{
    return components.at(id).get();
}