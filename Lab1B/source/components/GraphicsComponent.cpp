#include "../../include/components/GraphicsComponent.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Entity.h"

SpriteGraphicsComponent::SpriteGraphicsComponent(float _Scale)
{
	sprite.setScale(_Scale, _Scale);
}
void SpriteGraphicsComponent::init(const std::string& _TextureFile)
{
	texture.loadFromFile(_TextureFile);
	sprite.setTexture(texture);
}

void SpriteSheetGraphicsComponent::init(const std::string& _SpriteSheetFile)
{
	spriteSheet.loadSheet(_SpriteSheetFile);
	spriteSheet.setAnimation("Idle", true, true);
}

void SpriteGraphicsComponent::setPosition(float _X, float _Y)
{
	sprite.setPosition(_X, _Y);
}

void SpriteSheetGraphicsComponent::setPosition(float _X, float _Y)
{
	spriteSheet.getSprite().setPosition(_X, _Y);
}

sf::Sprite& SpriteGraphicsComponent::getSprite()
{
	return sprite;
}

sf::Sprite& SpriteSheetGraphicsComponent::getSprite()
{
	return spriteSheet.getSprite();
}

const sf::Vector2f& SpriteGraphicsComponent::getSpriteScale() const
{
	return sprite.getScale();
}

const sf::Vector2f& SpriteSheetGraphicsComponent::getSpriteScale() const
{
	return spriteSheet.getSpriteScale();
}

const sf::Vector2i SpriteGraphicsComponent::getTextureSize() const
{
	return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
}

const sf::Vector2i SpriteSheetGraphicsComponent::getTextureSize() const
{
	return spriteSheet.getSpriteSize();
}

const Vector2f SpriteGraphicsComponent::getSize()const
{
	return {
		texture.getSize().x * sprite.getScale().x,
		texture.getSize().y * sprite.getScale().y
	};
}
const Vector2f SpriteSheetGraphicsComponent::getSize()const
{
	return {
		spriteSheet.getSpriteSize().x * spriteSheet.getSpriteScale().x,
		spriteSheet.getSpriteSize().y * spriteSheet.getSpriteScale().y
	};
}

void SpriteSheetGraphicsComponent::setAnimation(const std::string& _Name, bool _Play, bool _Loop)
{
	spriteSheet.setAnimation(_Name, _Play, _Loop);
}
void SpriteSheetGraphicsComponent::setSpriteDirection(const Direction& _Dir)
{
	spriteSheet.setSpriteDirection(_Dir);
}

const Direction& SpriteSheetGraphicsComponent::getSpriteDirection()const
{
	return spriteSheet.getSpriteDirection();
}
AnimBase* SpriteSheetGraphicsComponent::getCurrentAnim()
{
	return spriteSheet.getCurrentAnim();
}