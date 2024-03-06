#pragma once
#include "../utils/Vector2.h"
#include "Components.h"

class PositionComponent :public Component
{
private:
    Vector2f position;

public:
    const auto& getPosition() const{return position;}

    void setPosition(float x, float y) { position.x = x; position.y = y;}

    ComponentID getID()const override { return ComponentID::POSITION; }
};