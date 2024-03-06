#include "../components/PlayerStateComponent.h"
#include "../core/Game.h"
#include "../entities/Fire.h"
#include "../components/GraphicsComponent.h"

void PlayerStateComponent::addWood(int w)
{
    wood += w;
    if (wood > maxWood) wood = maxWood;
    if (wood < 0) wood = 0;
}

void PlayerStateComponent::update(Game* _Game, Entity* _Ent, float _Elapsed)
{
    bool isWalking = false;
    auto graphicsComp = dynamic_cast<GraphicsComponent*>(_Ent->getComponent(ComponentID::GRAPHICS));
    auto velocityComp = dynamic_cast<const VelocityComponent*>(_Ent->getComponent(ComponentID::VELOCITY));

    if (graphicsComp == nullptr)
    {
        if (_Ent != _Game->getPlayer().get())
            throw std::exception("Should updated by Player.");
        else
            throw std::exception("Should contain the GraphicsComponent.");
    }
    if (velocityComp->getVelocity().x > 0)
    {
        isWalking = true;
        graphicsComp->setSpriteDirection(Direction::Right);
    }
    else if (velocityComp->getVelocity().x < 0)
    {
        isWalking = true;
        graphicsComp->setSpriteDirection(Direction::Left);
    }
    else if (velocityComp->getVelocity().y != 0.0f)
    {
        isWalking = true;
    }

    if (isAttacking())
    {
        graphicsComp->setAnimation("Attack", true, false);
    }
    else if (isShouting())
    {
        graphicsComp->setAnimation("Shout", true, false);
    }
    else if (isWalking)
    {
        graphicsComp->setAnimation("Walk", true, true);
    }
    else
    {
        graphicsComp->setAnimation("Idle", true, true);
    }

    if (shootCooldown > 0) shootCooldown -= _Elapsed;

    if (isShouting()
        && graphicsComp->getCurrentAnim()->getName() == "Shout"
        && graphicsComp->getCurrentAnim()->isInAction()
        && wood >= shootingCost
        && shootCooldown <= 0)
    {
        auto fire = dynamic_cast<Player*>(_Ent)->createFire();
        _Game->addEntity(fire);
        wood -= shootingCost;
        shootCooldown = shootCooldownTime;
    }

    if (!graphicsComp->getCurrentAnim()->isPlaying())
    {
        if (isAttacking())
        {
            setAttacking(false);
            graphicsComp->setAnimation("Idle", true, true);
        }
        else if (isShouting())
        {
            setShouting(false);
            graphicsComp->setAnimation("Idle", true, true);
        }
    }
}
