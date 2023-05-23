#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/LogicComponent.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER)
{
	addComponent(std::make_shared<VelocityComponent>(playerSpeed));
	addComponent(std::make_shared<PlayerInputComponent>());
	addComponent(std::make_shared<HealthComponent>(startingHealth, maxHealth));
	addComponent(std::make_shared<ColliderComponent>());
	addComponent(std::make_shared<PlayerStateComponent>(maxWood, shootingCost, shootCooldownTime));
}

Player::~Player() {}

void Player::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	Entity::init(textureFile, gc);
	dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))
		->init(
			dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition(),
			dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSize()
		);
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();

	auto posComp = dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION));
	Vector2f pos{ posComp->getPosition().x + getTextureSize().x * 0.5f,  posComp->getPosition().y + getTextureSize().y * 0.5f };
	fireEntity->init("img/fire.png", std::make_shared<SpriteGraphicsComponent>(1.0f));
	dynamic_cast<PositionComponent*>(fireEntity->getComponent(ComponentID::POSITION))->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	dynamic_cast<VelocityComponent*>(fireEntity->getComponent(ComponentID::VELOCITY))->setVelocity(vel.x, vel.y);

	return fireEntity;
}

void Player::addWood(int w)
{
	dynamic_cast<PlayerStateComponent*>(getComponent(ComponentID::LOGIC))->addWood(w);
}


void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->setPosition(x + cntrFactorX, y + cntrFactorY);
	dynamic_cast<VelocityComponent*>(getComponent(ComponentID::VELOCITY))->setVelocity(0.0f, 0.0f);
}

bool Player::collidesWith(std::shared_ptr<Entity> _Other)
{
	auto ptr = dynamic_cast<const ColliderComponent*>(_Other->getComponent(ComponentID::COLLIDER));
	if (ptr == nullptr)return false;
	return dynamic_cast<const ColliderComponent*>(getComponent(ComponentID::COLLIDER))->interesects(*ptr);
}
