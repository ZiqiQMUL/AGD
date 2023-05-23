#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"
#include <iostream>


Entity::Entity() :
	id(0),
	type(EntityType::UNDEFINED),
	// X.B (1/2) Add the initialization the deleted flag to false
	deleted(false)
{
	addComponent(std::make_shared<PositionComponent>());
}

Entity::Entity(EntityType et) :
	id(0),
	type(et),
	// X.B (2/2) Add the initialization the deleted flag to false
	deleted(false)
{
	addComponent(std::make_shared<PositionComponent>());
}

Entity::~Entity()
{
}

void Entity::init(const std::string& initFile, std::shared_ptr<GraphicsComponent> gc)
{
	addComponent(gc);
	auto graphics = dynamic_cast<GraphicsComponent*>(getComponent(ComponentID::GRAPHICS));
	auto pos = dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION));
	graphics->init(initFile);
	graphics->setPosition(pos->getPosition().x, pos->getPosition().y);
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

const Component* Entity::getComponent(ComponentID _ID)const
{
	return components.at(_ID).get();
}

Component* Entity::getComponent(ComponentID _ID)
{
	return components[_ID].get();
}

void Entity::addComponent(std::shared_ptr<Component> _CompPtr)
{
	auto id = _CompPtr->getID();
	components[id] = _CompPtr;
	compSet.turnOnBit(static_cast<uint32_t>(id));
}

bool Entity::hasComponent(Bitmask _Mask)
{
	return compSet.contains(_Mask);
}