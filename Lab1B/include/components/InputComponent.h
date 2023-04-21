#pragma once
#include<memory>

class Game;
class Entity;
class PlayerInputHandler;
class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void update(Game* _Game, Entity* _Ent, float _Elapsed = 0.0f) = 0;
};

class PlayerInputComponent :public InputComponent
{
public:
	PlayerInputComponent();
	void update(Game* _Game, Entity* _Ent, float _Elapsed = 0.0f)override;

private:
	std::unique_ptr<PlayerInputHandler> input;
};