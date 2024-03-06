//¨C Flyweight (10%)
#pragma once
#include <SFML/Graphics.hpp>

enum class TileType 
{
	CORRIDOR,
	WALL
};

class TileIntrinsic 
{
private:
	sf::Texture texture;
	TileType type;

public:
	TileIntrinsic(const std::string& textureFile, TileType tt);

	const sf::Texture& getTexture() const { return texture; }
	TileType getType() const { return type; }
};
