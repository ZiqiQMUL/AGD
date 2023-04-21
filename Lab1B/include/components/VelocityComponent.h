#pragma once
#include "../../include/utils/Vector2.h"

class Entity;
class Game;
class VelocityComponent
{
public:
	VelocityComponent(float _Speed = 1.0f) :speed(_Speed) {}
	void setVelocity(float _X, float _Y) { direction.x = _X; direction.y = _Y; }
	const auto& getVelocity()const { return direction; }
	void update(Game* _Game, Entity* _Ent, float _Elapsed);
private:
	Vector2f direction;
	float speed;
};