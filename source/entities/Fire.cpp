#include "../entities/Fire.h"//1c
#include "../components/TTLComponent.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE)
{
    addComponent(std::make_shared<TTLComponent>(startTimeToLive));
    addComponent(std::make_shared<VelocityComponent>());
}

Fire::~Fire()
{
}