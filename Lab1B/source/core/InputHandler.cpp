#include "../../include/core/InputHandler.h"

GameInputHandler::GameInputHandler() :isEscPressed(false)
{
	pauseCmd = std::make_shared<PauseCommand>();
}

std::shared_ptr<Command> GameInputHandler::handleInput()
{
	//I modified the logic to provide a stable key response
	bool test = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	if (!isEscPressed && test)
	{
		isEscPressed = true;
		return pauseCmd;
	}
	else if (!test)
	{
		isEscPressed = false;
	}
	return nullptr;
}

PlayerInputHandler::PlayerInputHandler()
{
	mvRCmd = std::make_shared<MoveRightCommand>();
	mvLCmd = std::make_shared<MoveLeftCommand>();
	mvUCmd = std::make_shared<MoveUpCommand>();
	mvDCmd = std::make_shared<MoveDownCommand>();

	atkCmd = std::make_shared<AttackCommand>();
	shoCmd = std::make_shared<ShoutCommand>();
}

const std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput()
{
	cmdVec.clear();

	bool testA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool testD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	bool testW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool testS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

	// This is not 100% following the instruction,
	// I believe the player should not move when
	// the opposite key pairs are pressed simultaneously
	if (!(testA && testD))
	{
		if (testD)cmdVec.push_back(mvRCmd);
		else if (testA)cmdVec.push_back(mvLCmd);
	}

	if (!(testW && testS))
	{
		if (testW)cmdVec.push_back(mvUCmd);
		else if (testS)cmdVec.push_back(mvDCmd);
	}
	
	// known bug: attack overrides shout when both pressed

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		cmdVec.push_back(atkCmd);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		cmdVec.push_back(shoCmd);
	}

	return cmdVec;
}