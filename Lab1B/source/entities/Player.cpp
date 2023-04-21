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
	velocity = std::make_shared<VelocityComponent>(playerSpeed);

	// VI.B: Create the unique pointer to the PlayerInputHandler object
	input = std::make_unique<PlayerInputComponent>();

	health = std::make_shared<HealthComponent>(startingHealth, maxHealth);

	collider = std::make_shared<ColliderComponent>();

	state = std::make_shared<PlayerStateComponent>(maxWood, shootingCost, shootCooldownTime);
}

Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	Entity::update(game, elapsed);

	velocity->update(game, this, elapsed);
	collider->update(game, this, elapsed);
	state->update(game, this, elapsed);
}

void Player::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	Entity::init(textureFile, gc);
	collider->init(position->getPosition(), graphics->getSize());
}

void Player::draw(Window* window)
{
	Entity::draw(window);
	window->draw(collider->getDrawableRect());
}


void Player::handleInput(Game& game)
{
	input->update(&game, this);
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();

	Vector2f pos{ position->getPosition().x + getTextureSize().x * 0.5f,  position->getPosition().y + getTextureSize().y * 0.5f };
	fireEntity->init("img/fire.png", std::make_shared<SpriteGraphicsComponent>(1.0f));
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (graphics->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	fireEntity->getVelocityComp()->setVelocity(vel.x, vel.y);

	return fireEntity;
}

void Player::addWood(int w)
{
	state->addWood(w);
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

	setPosition(x + cntrFactorX, y + cntrFactorY);
	velocity->setVelocity(0.0f, 0.0f);
}

bool Player::collidesWith(std::shared_ptr<Entity> _Other)
{
	auto ptr = _Other->getColliderComp().get();
	if (ptr == nullptr)return false;
	return collider->interesects(*ptr);
}
