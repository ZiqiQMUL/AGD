#pragma once
#include "Entity.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/GraphicsComponent.h"


class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) {
		addComponent(std::make_shared<ColliderComponent>());
	}
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		// III.C (1/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, gc);

		// VIII.C (1/2) Set the top left and bottom right corners of the bounding box for this entity.
		dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))
			->init(
				dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition(), 
				dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSize()
			);
	}

	int getHealth() const { return potionHealth; }

protected:
	const int potionHealth = 10;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG) {
		addComponent(std::make_shared<ColliderComponent>());
	}
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		// III.C (2/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, gc);

		// VIII.C (2/2) Set the top left and bottom right corners of the bounding box for this entity.
		dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))
			->init(
				dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition(), 
				dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSize()
			);
	}

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded = 15;
};