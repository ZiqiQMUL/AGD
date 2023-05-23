#pragma once
#include "Entity.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/VelocityComponent.h"

class Fire : public Entity
{
public:
	Fire();
	~Fire();
	int getTTL() const { return dynamic_cast<const TTLComponent*>(getComponent(ComponentID::TTL))->getTTL(); }
private:
	const int startTimeToLive = 150; //frames
};

