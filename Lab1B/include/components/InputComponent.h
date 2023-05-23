#pragma once
#include<memory>
#include "Components.h"

class Game;
class Entity;
class PlayerInputHandler;
class InputComponent :public Component
{
public:
	virtual ~InputComponent() {}
	virtual std::shared_ptr<PlayerInputHandler> getHandler() = 0;

	ComponentID getID()override { return ComponentID::INPUT; }
};

class PlayerInputComponent :public InputComponent
{
public:
	PlayerInputComponent();
	std::shared_ptr<PlayerInputHandler> getHandler()override;

private:
	std::shared_ptr<PlayerInputHandler> input;
};