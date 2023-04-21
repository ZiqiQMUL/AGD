#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include <iostream>


Entity::Entity() :
	id(0),
	type(EntityType::UNDEFINED),
	// X.B (1/2) Add the initialization the deleted flag to false
	deleted(false)
{
	position = std::make_unique<PositionComponent>();
}

Entity::Entity(EntityType et) :
	id(0),
	type(et),
	// X.B (2/2) Add the initialization the deleted flag to false
	deleted(false)
{
	position = std::make_unique<PositionComponent>();
}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{
	graphics->update(game, this, elapsed);
}



void Entity::draw(Window* window)
{
	window->draw(graphics->getSprite());
}

void Entity::init(const std::string& initFile, std::shared_ptr<GraphicsComponent> gc)
{
	graphics = gc;
	graphics->init(initFile);
	graphics->setPosition(position->getPosition().x, position->getPosition().y);
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
}


const sf::Vector2f& Entity::getSpriteScale() const
{
	return graphics->getSpriteScale();
}

sf::Vector2i Entity::getTextureSize() const
{
	return graphics->getTextureSize();
}

const Vector2f& Entity::getPosition()const
{
	return position->getPosition();
}