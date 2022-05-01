#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const float& gridSize, const unsigned& width, const unsigned& hight)
	: gridSizeF(gridSize), gridSizeU(static_cast<unsigned>(gridSizeF))
{
	this->maxSize.x = width;
	this->maxSize.y = hight;

	this->map.reserve(static_cast<size_t>(this->maxSize.x));

	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		this->map.push_back(std::vector<Tile>());
		this->map[x].reserve(static_cast<size_t>(this->maxSize.y));
	}
	
}

TileMap::~TileMap()
{
}

//Functions

void TileMap::addTile(const unsigned& x, const unsigned& y)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0)
	{
		this->map[x].push_back(Tile(x * this->gridSizeF, y * gridSizeF, this->gridSizeF));
			std::cout << "\nAdded  " << x << " " << y;
	}
}

void TileMap::removeTile(const unsigned& x, const unsigned& y)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0)
	{
		std::find_if(map[x].begin(), map[x].end(), [](Tile& tile) {return tile.getCoordinates() == sf::Vector2u(x, y); })
		std::cout << "\Deleted  " << x << " " << y;
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& el_x : this->map)
	{
		for (auto& el_y : el_x)
		{
			el_y.render(target);
		}
	}
}