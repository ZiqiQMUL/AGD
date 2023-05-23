#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE)
{
	addComponent(std::make_shared<TTLComponent>(startTimeToLive));
	addComponent(std::make_shared<VelocityComponent>());
}

Fire::~Fire()
{}
