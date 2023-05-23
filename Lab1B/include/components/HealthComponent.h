#pragma once
#include "Components.h"

class HealthComponent :public Component
{
public:
	HealthComponent(int _Cur, int _Max) :curhealth(_Cur), maxHealth(_Max) {}
	int getHealth()const { return curhealth; }
	void changeHealth(int _Delta)
	{
		curhealth += _Delta;
		if (curhealth < 0)curhealth = 0;
		if (curhealth > maxHealth)curhealth = maxHealth;
	}
	ComponentID getID()override { return ComponentID::HEALTH; }
private:
	int curhealth;
	int maxHealth;
};