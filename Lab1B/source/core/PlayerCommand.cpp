#include "../../include/core/Command.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/LogicComponent.h"

void MoveRightCommand::execute(Game& _Game)
{
	auto vec = _Game.getPlayer()->getVelocityComp()->getVelocity();
	vec.x = 1.0f;
	_Game.getPlayer()->getVelocityComp()->setVelocity(vec.x, vec.y);
}

void MoveLeftCommand::execute(Game& _Game)
{
	auto vec = _Game.getPlayer()->getVelocityComp()->getVelocity();
	vec.x = -1.0f;
	_Game.getPlayer()->getVelocityComp()->setVelocity(vec.x, vec.y);
}

void MoveUpCommand::execute(Game& _Game)
{
	auto vec = _Game.getPlayer()->getVelocityComp()->getVelocity();
	vec.y = -1.0f;
	_Game.getPlayer()->getVelocityComp()->setVelocity(vec.x, vec.y);
}

void MoveDownCommand::execute(Game& _Game)
{
	auto vec = _Game.getPlayer()->getVelocityComp()->getVelocity();
	vec.y = 1.0f;
	_Game.getPlayer()->getVelocityComp()->setVelocity(vec.x, vec.y);
}

// We may not allow the player to attack and shout at the same time
void AttackCommand::execute(Game& _Game)
{
	if (true
		&& (!_Game.getPlayer()->getStateComp()->isAttacking())
		&& (!_Game.getPlayer()->getStateComp()->isShouting()))
	{
		_Game.getPlayer()->getStateComp()->setAttacking(true);
	}
}

// We may not allow the player to attack and shout at the same time
void ShoutCommand::execute(Game& _Game)
{
	if (true
		&& (!_Game.getPlayer()->getStateComp()->isAttacking())
		&& (!_Game.getPlayer()->getStateComp()->isShouting()))
	{
		_Game.getPlayer()->getStateComp()->setShouting(true);
	}
}