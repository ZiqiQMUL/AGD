#pragma once
#include "../../include/utils/Vector2.h"

class PositionComponent
{
public:
	void setPosition(float _X, float _Y) { position.x = _X; position.y = _Y; }
	const auto& getPosition()const { return position; }
private:
	Vector2f position;
};