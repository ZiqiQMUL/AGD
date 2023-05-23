#pragma once
#include "../../include/utils/Vector2.h"
#include "Components.h"

class Entity;
class Game;

class VelocityComponent :public Component
{
public:
	VelocityComponent(float _Speed = 1.0f) :speed(_Speed) {}
	void setVelocity(float _X, float _Y) { direction.x = _X; direction.y = _Y; }
	const auto& getVelocity()const { return direction; }
	const auto getSpeed()const { return speed; }
  
	ComponentID getID()override { return ComponentID::VELOCITY; }
private:
	Vector2f direction;
	float speed;
};