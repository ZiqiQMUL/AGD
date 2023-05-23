#pragma once
#include "../../include/utils/Vector2.h"
#include "Components.h"

class PositionComponent :public Component
{
public:
	void setPosition(float _X, float _Y) { position.x = _X; position.y = _Y; }
	const auto& getPosition()const { return position; }
	ComponentID getID()override { return ComponentID::POSITION; }
private:
	Vector2f position;
};