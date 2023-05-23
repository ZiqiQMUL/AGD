#pragma once
#include "Components.h"

class TTLComponent :public Component
{
public:
	TTLComponent() = delete;
	TTLComponent(int _TTL) :ttl(_TTL) {}
	int getTTL()const { return ttl; }
	void tick() { if (ttl > 0) --ttl; else ttl = 0; }
	ComponentID getID()override { return ComponentID::TTL; }
private:
	int ttl;
};