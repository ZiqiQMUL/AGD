#include "../components/PlayerStateComponent.h"
#include "../components/PositionComponent.h"
#include "../components/VelocityComponent.h"
#include "../components/GraphicsComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/InputComponent.h"
#include "../components/HealthComponent.h"//  Collisions (15%)
#include "../service/Locator.h"
#include "../entities/StaticEntities.h"
#include "../graphics/AnimBase.h"
#include "../entities/Player.h"
#include "../entities/Fire.h"
#include "../core/Game.h"

#include <iostream>


Player::Player() : Entity(EntityType::PLAYER)
{
	addComponent(std::make_shared<VelocityComponent>(playerSpeed));
	addComponent(std::make_shared<PlayerInputComponent>());
	addComponent(std::make_shared<HealthComponent>(startingHealth, maxHealth));
	addComponent(std::make_shared<BoxColliderComponent>());
	addComponent(std::make_shared<PlayerStateComponent>(maxWood, shootingCost, shootCooldownTime));

	observer = std::make_unique<AchievementManager>();
}

Player::~Player() {}

void Player::init(const std::string& TextureFile, std::shared_ptr<GraphicsComponent> GraphicsComp)
{
	Entity::init(TextureFile, GraphicsComp);
	dynamic_cast<BoxColliderComponent*>(getComponent(ComponentID::COLLIDER))
		->init(
			dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition(),
			dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSize()
		);
}

std::shared_ptr<Fire> Player::createFire()
{
	auto fireEntity = std::make_shared<Fire>();
	auto posComp = dynamic_cast<const PositionComponent*>(getComponent(ComponentID::POSITION));
	const Vector2f& playerPos = posComp->getPosition();
	Vector2f pos{ playerPos.x + getTextureSize().x * 0.5f, playerPos.y + getTextureSize().y * 0.5f };

	fireEntity->init("img/fire.png", std::make_shared<SpriteGraphicsComponent>(1.0f));
	dynamic_cast<PositionComponent*>(fireEntity->getComponent(ComponentID::POSITION))->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (dynamic_cast<const GraphicsComponent*>(getComponent(ComponentID::GRAPHICS))->getSpriteDirection() == Direction::Left)
		vel.x = vel.x * -1.0f;
	dynamic_cast<VelocityComponent*>(fireEntity->getComponent(ComponentID::VELOCITY))->setVelocity(vel.x, vel.y);
	notify("shout");
	Audio& service = Locator::getAudio();
	service.playAudio(AUDIO_TYPE::FIRE);
	return fireEntity;
}

void Player::notify(const std::string& event)
{
	if (observer)
	{
		observer->onNotify(event);
	}
}

void Player::addWood(int w)
{
	dynamic_cast<PlayerStateComponent*>(getComponent(ComponentID::LOGIC))->addWood(w);
}

bool Player::collidesWith(std::shared_ptr<Entity> _Other)
{
	auto colliderComponent = dynamic_cast<const BoxColliderComponent*>(_Other->getComponent(ComponentID::COLLIDER));
	if (colliderComponent == nullptr)return false;
	return dynamic_cast<const BoxColliderComponent*>(getComponent(ComponentID::COLLIDER))->interesects(*colliderComponent);
}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);
	float cntrFactorX = cntrFactorY * 0.5f;

	dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->setPosition(x + cntrFactorX, y + cntrFactorY);
	dynamic_cast<VelocityComponent*>(getComponent(ComponentID::VELOCITY))->setVelocity(0.0f, 0.0f);

}


