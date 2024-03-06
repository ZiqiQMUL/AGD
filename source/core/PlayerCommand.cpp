#include "../../include/core/Command.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PlayerStateComponent.h"

VelocityComponent* Command::getVelocityComponent(Game& game)
{
    return dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
}

PlayerStateComponent* Command::getPlayerStateComponent(Game& game)
{
    return dynamic_cast<PlayerStateComponent*>(game.getPlayer()->getComponent(ComponentID::LOGIC));
}

void MoveRightCommand::execute(Game& game)
{
    move(getVelocityComponent(game));
}

void MoveRightCommand::move(VelocityComponent* velocityComp)
{
    auto vec = velocityComp->getVelocity();
    vec.x = 1.0f;
    velocityComp->setVelocity(vec.x, vec.y);
}

void MoveLeftCommand::execute(Game& game)
{
    move(getVelocityComponent(game));
}

void MoveLeftCommand::move(VelocityComponent* velocityComp)
{
    auto vec = velocityComp->getVelocity();
    vec.x = -1.0f;
    velocityComp->setVelocity(vec.x, vec.y);
}

void MoveUpCommand::execute(Game& game)
{
    move(getVelocityComponent(game));
}

void MoveUpCommand::move(VelocityComponent* velocityComp)
{
    auto vec = velocityComp->getVelocity();
    vec.y = -1.0f;
    velocityComp->setVelocity(vec.x, vec.y);
}

void MoveDownCommand::execute(Game& game)
{
    move(getVelocityComponent(game));
}

void MoveDownCommand::move(VelocityComponent* velocityComp)
{
    auto vec = velocityComp->getVelocity();
    vec.y = 1.0f;
    velocityComp->setVelocity(vec.x, vec.y);
}

void AttackCommand::execute(Game& game)
{
    action(getPlayerStateComponent(game));
}

void AttackCommand::action(PlayerStateComponent* playerStateComp)
{
    if (!playerStateComp->isAttacking() && !playerStateComp->isShouting())
    {
        playerStateComp->setAttacking(true);
    }
}

void ShoutCommand::execute(Game& game)
{
    action(getPlayerStateComponent(game));
}

void ShoutCommand::action(PlayerStateComponent* playerStateComp)
{
    if (!playerStateComp->isAttacking() && !playerStateComp->isShouting())
    {
        playerStateComp->setShouting(true);
    }
}