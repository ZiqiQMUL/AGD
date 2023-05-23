#pragma once
#include "../utils/Bitmask.h"
#include "../entities/Entity.h"

class Game;

class System
{
public:
	virtual void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) = 0;
	bool validate(std::shared_ptr<Entity> _Entity) { return _Entity->hasComponent(componentMask); }
protected:
	Bitmask componentMask;
};

class TTLSystem :public System
{
public:
	TTLSystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};

class InputSystem :public System
{
public:
	InputSystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};

class MovementSystem :public System
{
public:
	MovementSystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};

class GraphicsSystem :public System
{
public:
	GraphicsSystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};

class ColliderSystem :public System
{
public:
	ColliderSystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};

class GameplaySystem :public System
{
public:
	GameplaySystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};

class PrintDebugSystem :public System
{
public:
	PrintDebugSystem();
	void update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)override;
};