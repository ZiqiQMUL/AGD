#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/components/ColliderComponent.h"
#include "SFML/Graphics.hpp"

PrintDebugSystem::PrintDebugSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
}

void PrintDebugSystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{
	auto cComp = dynamic_cast<ColliderComponent*>(_Entity->getComponent(ComponentID::COLLIDER));
	if (cComp == nullptr)
		throw std::exception("Null Collider Component");
	_Game->getWindow()->draw(cComp->getDrawableRect());
}
