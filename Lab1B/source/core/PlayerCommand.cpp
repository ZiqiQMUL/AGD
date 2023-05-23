#include "../../include/core/Command.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/LogicComponent.h"

void MoveRightCommand::execute(Game& _Game)
{
	auto velocity = dynamic_cast<VelocityComponent*>(_Game.getPlayer()->getComponent(ComponentID::VELOCITY));
	auto vec = velocity->getVelocity();
	vec.x = 1.0f;
	velocity->setVelocity(vec.x, vec.y);
}

void MoveLeftCommand::execute(Game& _Game)
{
	auto velocity = dynamic_cast<VelocityComponent*>(_Game.getPlayer()->getComponent(ComponentID::VELOCITY));
	auto vec = velocity->getVelocity();
	vec.x = -1.0f;
	velocity->setVelocity(vec.x, vec.y);
}

void MoveUpCommand::execute(Game& _Game)
{
	auto velocity = dynamic_cast<VelocityComponent*>(_Game.getPlayer()->getComponent(ComponentID::VELOCITY));
	auto vec = velocity->getVelocity();
	vec.y = -1.0f;
	velocity->setVelocity(vec.x, vec.y);
}

void MoveDownCommand::execute(Game& _Game)
{
	auto velocity = dynamic_cast<VelocityComponent*>(_Game.getPlayer()->getComponent(ComponentID::VELOCITY));
	auto vec = velocity->getVelocity();
	vec.y = 1.0f;
	velocity->setVelocity(vec.x, vec.y);
}

// We may not allow the player to attack and shout at the same time
void AttackCommand::execute(Game& _Game)
{
	auto logicCompPtr = dynamic_cast<PlayerStateComponent*>(_Game.getPlayer()->getComponent(ComponentID::LOGIC));
	if (true
		&& (!logicCompPtr->isAttacking())
		&& (!logicCompPtr->isShouting()))
	{
		logicCompPtr->setAttacking(true);
	}
}

// We may not allow the player to attack and shout at the same time
void ShoutCommand::execute(Game& _Game)
{
	auto logicCompPtr = dynamic_cast<PlayerStateComponent*>(_Game.getPlayer()->getComponent(ComponentID::LOGIC));
	if (true
		&& (!logicCompPtr->isAttacking())
		&& (!logicCompPtr->isShouting()))
	{
		logicCompPtr->setShouting(true);
	}
}