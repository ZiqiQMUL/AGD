#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Vector2.h"
#include <string>

class Game;
class Entity;

class GraphicsComponent
{
public:
	virtual void init(const std::string&) = 0;
	virtual void setPosition(float _X, float _Y) = 0;
	virtual void update(Game* _Game, Entity* _Ent, float _Elapsed) = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual const sf::Vector2f& getSpriteScale()const = 0;
	virtual const sf::Vector2i getTextureSize()const = 0;
	virtual const Vector2f getSize()const = 0;
	// <FEEDBACK> Functions to do with animation should be included in the graphics component such as setAnimation()
	virtual void setAnimation(const std::string& _Name, bool _Play, bool _Loop) = 0;
	virtual void setSpriteDirection(const Direction& _Dir) = 0;
	virtual const Direction& getSpriteDirection()const = 0;
	virtual AnimBase* getCurrentAnim() = 0;
};

class SpriteGraphicsComponent :public GraphicsComponent
{
public:
	SpriteGraphicsComponent(float _Scale);
	void init(const std::string& _TextureFile)override;
	void setPosition(float _X, float _Y)override;
	void update(Game* _Game, Entity* _Ent, float _Elapsed)override;
	sf::Sprite& getSprite()override;
	const sf::Vector2f& getSpriteScale()const override;
	const sf::Vector2i getTextureSize()const override;
	const Vector2f getSize()const override;

	void setAnimation(const std::string& _Name, bool _Play, bool _Loop)override { throw std::exception("No Animation on Static Sprites!"); }
	void setSpriteDirection(const Direction& _Dir)override { throw std::exception("No Animation on Static Sprites!"); }
	const Direction& getSpriteDirection()const override { throw std::exception("No Animation on Static Sprites!"); }
	AnimBase* getCurrentAnim()override { throw std::exception("No Animation on Static Sprites!"); }
private:
	sf::Texture texture;
	sf::Sprite sprite;
};


class SpriteSheetGraphicsComponent :public GraphicsComponent
{
public:
	void init(const std::string& _SpriteSheetFile)override;
	void setPosition(float _X, float _Y)override;
	void update(Game* _Game, Entity* _Ent, float _Elapsed)override;
	sf::Sprite& getSprite()override;
	const sf::Vector2f& getSpriteScale()const override;
	const sf::Vector2i getTextureSize()const override;
	const Vector2f getSize()const override;

	void setAnimation(const std::string& _Name, bool _Play, bool _Loop)override;
	void setSpriteDirection(const Direction& _Dir)override;
	const Direction& getSpriteDirection()const override;
	AnimBase* getCurrentAnim()override;
private:
	SpriteSheet spriteSheet;
};
