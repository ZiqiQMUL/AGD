#include "../core/Tile.h"
#include <sstream>


void Tile::loadTile(int x, int y, float sc, const std::shared_ptr<TileIntrinsic> t)
{
	intrinsicData = t;
	sprite.setTexture(intrinsicData->getTexture());
	//Place tile on the screen.
	place(x, y, sc);
}


void Tile::place(int x, int y, float sc)
{
	//Position in grid:
	position.x = x;
	position.y = y;

	//scale for texture:
	sprite.setScale(sc, sc);

	//Position on screen:
	sf::Vector2u textSize = intrinsicData->getTexture().getSize();
	float pixels_x = static_cast<float>(x * (textSize.x * sc));
	float pixels_y = static_cast<float>(y * (textSize.y * sc));
	sprite.setPosition(pixels_x, pixels_y);
}


void Tile::draw(Window* window)
{
	window->draw(sprite);
}

