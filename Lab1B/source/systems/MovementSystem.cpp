#include "../../include/systems/Systems.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"

MovementSystem::MovementSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void MovementSystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{
	auto vComp = dynamic_cast<const VelocityComponent*>(_Entity->getComponent(ComponentID::VELOCITY));
	if (vComp == nullptr)
		throw std::exception("Null Velocity Component");

	auto pComp = dynamic_cast<PositionComponent*>(_Entity->getComponent(ComponentID::POSITION));
	if (pComp == nullptr)
		throw std::exception("Null Position Component");


	auto movement = vComp->getVelocity() * _Elapsed * vComp->getSpeed();
	auto newPos = pComp->getPosition() + movement;
	pComp->setPosition(newPos.x, newPos.y);
}