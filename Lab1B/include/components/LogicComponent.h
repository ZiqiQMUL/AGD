#pragma once

class Game;
class Entity;

class LogicComponent
{
public:
	virtual void update(Game* _Game, Entity* _Ent, float _Elapsed) = 0;
};

class PlayerStateComponent :public LogicComponent
{
public:
	PlayerStateComponent(int _MaxWood, int _ShootingCost, float _ShootCooldownTime) :
		attacking(false),
		shouting(false),
		wood(0),
		shootCooldown(0),
		maxWood(_MaxWood),
		shootingCost(_ShootingCost),
		shootCooldownTime(_ShootCooldownTime)
	{}

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	int getWood() const { return wood; }

	void addWood(int w);

	void update(Game* _Game, Entity* _Ent, float _Elapsed)override;

private:
	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;

	int maxWood;
	int shootingCost;
	float shootCooldownTime;
};