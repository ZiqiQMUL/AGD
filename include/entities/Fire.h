#pragma once
#include "Entity.h"
#include "../components/TTLComponent.h" 
#include "../components/VelocityComponent.h"

class Fire : public Entity
{
public:
    Fire();
    ~Fire();
    int getTTL(){ return dynamic_cast<TTLComponent*>(getComponent(ComponentID::TTL))->getTTL(); }
private:
    const int startTimeToLive = 150; //frames
};