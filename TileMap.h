#pragma once
#include "Tile.h"

class TileMap
{
private:
	//Variavles
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector<Tile> > > map;

public:
	TileMap();
	virtual ~TileMap();

	//Functions
};

