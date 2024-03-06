#pragma once
#include "../components/Components.h"

class TTLComponent : public Component
{
private:
    int ttl;

public:
    TTLComponent(int initial_ttl) : ttl(initial_ttl) {}

    int getTTL() const { return ttl; }
	void decreaseTTL() { if (ttl > 0) --ttl; else ttl = 0; }
	ComponentID getID()const override { return ComponentID::TTL; }
};