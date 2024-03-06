#pragma once
#include "Entity.h"
#include "../../include/components/PositionComponent.h"//1c 7.0
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/GraphicsComponent.h"

//update position to 1c 6.1
class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) 
	{
		addComponent(std::make_shared<BoxColliderComponent>());
	}
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> graphiComp) override
	{
		// III.C (1/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, graphiComp); //III.C (1/2)
		// VIII.C (1/2) Set the top left and bottom right corners of the bounding box for this entity.
		dynamic_cast<BoxColliderComponent*>(getComponent(ComponentID::COLLIDER))
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
	Log() : Entity(EntityType::LOG) 
	{
		addComponent(std::make_shared<BoxColliderComponent>());
	}
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> graphicsComp) override
	{
		// III.C (2/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, graphicsComp);///III.C 2/2

		// VIII.C (2/2) Set the top left and bottom right corners of the bounding box for this entity.
		dynamic_cast<BoxColliderComponent*>(getComponent(ComponentID::COLLIDER))
			->init(
				dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition(),
				dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSize()
			);
	}

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded = 15;
	std::shared_ptr<BoxColliderComponent> collider;
};
