#pragma once
#include <vector>
#include "../core/Tile.h"
#include "../graphics/Window.h"
#include "TileIntrinsic.h"

class Board
{
private:
	size_t width;
	size_t height;
	std::vector<Tile*> grid;

	using const_reference = std::vector<Tile*>::const_reference;
	using reference = std::vector<Tile*>::reference;

	std::shared_ptr<TileIntrinsic> corridorIntrinsics;
	std::shared_ptr<TileIntrinsic> wallIntrinsics;

public:

	Board() : width(0), height(0) {}
	Board(size_t newWidth, size_t newHeight);

	~Board();

	reference operator[] (const sf::Vector2i& pos) { return grid[static_cast<size_t>(pos.y * static_cast<int>(width) + pos.x)]; }
	const_reference operator[] (const sf::Vector2i& pos) const { return grid[static_cast<size_t>(pos.y * static_cast<int>(width) + pos.x)]; }

	reference get(int x, int y);
	const_reference get(int x, int y) const;

	size_t getWidth() const { return width; }
	size_t getHeight() const { return height; }
	size_t getNumTiles() const { return grid.size(); }

	bool inBounds(int x, int y) const { return x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height); };
	bool inBounds(const sf::Vector2i& pos) const { return inBounds(pos.x, pos.y); };

	void addTile(int x, int y, float scale, TileType ty);

	void draw(Window* window);
	void print();
};
