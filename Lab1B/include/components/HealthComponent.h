#pragma once

class HealthComponent
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
private:
	int curhealth;
	int maxHealth;
};