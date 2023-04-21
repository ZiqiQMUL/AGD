#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Game.h"

void VelocityComponent::update(Game* _Game, Entity* _Ent, float _Elapsed)
{
	auto movement = direction * _Elapsed * speed;
	auto newPos = _Ent->getPosition() + movement;
	_Ent->setPosition(newPos.x, newPos.y);

}