#pragma once
#include "../core/Command.h"

class Command;

class GameInputHandler
{
public:
	GameInputHandler();

	std::shared_ptr<Command> handleInput();	

private:
	std::shared_ptr<Command> pauseCmd;
	bool isEscPressed;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();

	const std::vector<std::shared_ptr<Command>>& handleInput();

private:
	std::vector<std::shared_ptr<Command>> cmdVec;

	std::shared_ptr<Command> mvRCmd;
	std::shared_ptr<Command> mvLCmd;
	std::shared_ptr<Command> mvUCmd;
	std::shared_ptr<Command> mvDCmd;

	std::shared_ptr<Command> atkCmd;
	std::shared_ptr<Command> shoCmd;
};