#include "../../include/systems/Systems.h"
#include "../../include/components/TTLComponent.h"

TTLSystem::TTLSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::TTL));
}

void TTLSystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{
	auto ttlComp = dynamic_cast<TTLComponent*>(_Entity->getComponent(ComponentID::TTL));
	if (ttlComp == nullptr)
		throw std::exception("Null TTL Component");
	ttlComp->tick();
	if (ttlComp->getTTL() <= 0)
	{
		_Entity->deleteEntity();
	}
}