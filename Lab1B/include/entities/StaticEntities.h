#pragma once
#include "Entity.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/GraphicsComponent.h"


class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) {
		collider = std::make_shared<ColliderComponent>();
	}
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		// III.C (1/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, gc);

		// VIII.C (1/2) Set the top left and bottom right corners of the bounding box for this entity.
		collider->init(position->getPosition(), graphics->getSize());
	}

	virtual void update(Game* game, float elapsed = 1.0f) override { }
	virtual void draw(Window* window) override
	{
		Entity::draw(window);
		window->draw(collider->getDrawableRect());
	}

	int getHealth() const { return potionHealth; }
	std::shared_ptr<ColliderComponent> getColliderComp()override { return collider; }

protected:
	const int potionHealth = 10;
	std::shared_ptr<ColliderComponent> collider;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG) {
		collider = std::make_shared<ColliderComponent>();
	}
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		// III.C (2/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, gc);

		// VIII.C (2/2) Set the top left and bottom right corners of the bounding box for this entity.
		collider->init(position->getPosition(), graphics->getSize());
	}

	virtual void update(Game* game, float elapsed = 1.0f) override {}
	virtual void draw(Window* window) override
	{
		Entity::draw(window);
		window->draw(collider->getDrawableRect());
	}

	std::shared_ptr<ColliderComponent> getColliderComp()override { return collider; }

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded = 15;
	std::shared_ptr<ColliderComponent> collider;
};