#pragma once
#include "Tile.h"

class Tile;

class TileMap
{
private:
	//Variavles
	float gridSizeF;
	unsigned gridSizeU;

	sf::Vector2u maxSize;
	std::vector<std::vector<Tile>> map;

public:
	TileMap(const float& gridSize, const unsigned& width, const unsigned& hight);
	virtual ~TileMap();

	//Functions
	void addTile(const unsigned& x, const unsigned& y);
	void removeTile(const unsigned& x, const unsigned& y);

	void update();
	void render(sf::RenderTarget& target);
};

