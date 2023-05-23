#include "../../include/systems/Systems.h"
#include "../../include/components/LogicComponent.h"

GameplaySystem::GameplaySystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::LOGIC));
}

void GameplaySystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{

	auto lComp = dynamic_cast<PlayerStateComponent*>(_Entity->getComponent(ComponentID::LOGIC));
	if (lComp == nullptr)
		throw std::exception("Null tLogic Component");

	lComp->update(_Game, _Entity.get(), _Elapsed);
}