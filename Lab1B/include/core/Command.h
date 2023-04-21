#pragma once
#include "../core/Game.h"

class Command
{
public:
	virtual void execute(Game&) = 0;
	virtual ~Command() {}
};

class PauseCommand :public Command
{
public:
	void execute(Game&) override;
};

class MoveRightCommand :public Command
{
public:
	void execute(Game&) override;
};

class MoveLeftCommand :public Command
{
public:
	void execute(Game&) override;
};

class MoveUpCommand :public Command
{
public:
	void execute(Game&) override;
};

class MoveDownCommand :public Command
{
public:
	void execute(Game&) override;
};

class AttackCommand :public Command
{
public:
	void execute(Game&) override;
};

class ShoutCommand :public Command
{
public:
	void execute(Game&) override;
};