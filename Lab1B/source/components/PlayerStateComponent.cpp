#include "../../include/components/LogicComponent.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/components/GraphicsComponent.h"

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}

void PlayerStateComponent::update(Game* _Game, Entity* _Ent, float _Elapsed)
{
	bool isWalking = false;
	auto graphics = _Ent->getGraphicsComp();
	if (graphics == nullptr)
	{
		if(_Ent!=_Game->getPlayer().get())
		throw std::exception("PlayerStateComponent should be updated by Player.");
		else throw std::exception("Player should contain GraphicsComponent.");
	}

	auto velocity = dynamic_cast<Player*>(_Ent)->getVelocityComp();
	if (velocity->getVelocity().x > 0)
	{
		isWalking = true;

		graphics->setSpriteDirection(Direction::Right);
	}
	else if (velocity->getVelocity().x < 0)
	{
		isWalking = true;
		graphics->setSpriteDirection(Direction::Left);
	}
	else if (velocity->getVelocity().y != 0.0f)
	{
		isWalking = true;
	}

	if (isAttacking())
	{
		graphics->setAnimation("Attack", true, false);
	}
	else if (isShouting())
	{
		graphics->setAnimation("Shout", true, false);
	}
	else if (isWalking)
	{
		graphics->setAnimation("Walk", true, true);
	}
	else
	{
		graphics->setAnimation("Idle", true, true);
	}

	if (shootCooldown > 0)shootCooldown -= _Elapsed;

	if (isShouting()
		&& graphics->getCurrentAnim()->getName() == "Shout"
		&& graphics->getCurrentAnim()->isInAction()
		&& wood >= shootingCost
		&& shootCooldown <= 0)
	{
		auto fire = dynamic_cast<Player*>(_Ent)->createFire();
		_Game->addEntity(fire);
		wood -= shootingCost;
		shootCooldown = shootCooldownTime;
	}


	if (!graphics->getCurrentAnim()->isPlaying())
	{
		if (isAttacking())setAttacking(false);
		if (isShouting())setShouting(false);
		graphics->setAnimation("Idle", true, true);
	}
}