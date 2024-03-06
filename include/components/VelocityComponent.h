#pragma once
#include "../utils/Vector2.h"
#include "Components.h"

class Game;
class Entity;

class VelocityComponent :public Component
{
public:
	VelocityComponent(float Speed = 1.0f) :speed(Speed) {}
	void setVelocity(float X, float Y) { direction.x = X; direction.y = Y; }
	const auto& getVelocity()const { return direction; }
	const auto getSpeed()const { return speed; }
	ComponentID getID()const override { return ComponentID::VELOCITY; }

private:
	Vector2f direction;
	float speed;
};
