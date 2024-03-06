#pragma once
#include "../core/TileIntrinsic.h"
#include "../utils/Vector2.h"
#include "../graphics/Window.h"


class Tile
{
private:

	TileType type;
	sf::Vector2i position;
	std::shared_ptr<TileIntrinsic> intrinsicData;
	sf::Sprite sprite;

	void place(int x, int y, float sc);

public:
	//Tile() : position(0, 0), intrinsicData(nullptr) {}//¨C Flyweight (10%)
	void loadTile(int x, int y, float sc, const std::shared_ptr<TileIntrinsic> t);//¨C Flyweight (10%)
	inline int x() const { return position.x; }
	inline int y() const { return position.y; }
	inline const sf::Vector2f& getScale() const { return sprite.getScale(); }
	inline TileType getType() const { return intrinsicData->getType(); }
	inline float getSpriteXpos() const { return sprite.getPosition().x; }
	inline float getSpriteYpos() const { return sprite.getPosition().y; }
	void draw(Window* window);
};
