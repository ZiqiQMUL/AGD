#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/PositionComponent.h"

ColliderSystem::ColliderSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
}

void ColliderSystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{
	auto pComp = dynamic_cast<const PositionComponent*>(_Entity->getComponent(ComponentID::POSITION));
	if (pComp == nullptr)
		throw std::exception("Null Position Component");

	auto cComp = dynamic_cast<ColliderComponent*>(_Entity->getComponent(ComponentID::COLLIDER));
	if (cComp == nullptr)
		throw std::exception("Null Collider Component");

	auto& position = pComp->getPosition();
	cComp->setBox(position);
}
