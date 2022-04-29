#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
	: gridSizeU(50)
{
	this->maxSize.x = 5000;
	this->maxSize.y = 5000;
}

TileMap::~TileMap()
{
}

//Functions