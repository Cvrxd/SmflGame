#include "stdafx.h"
#include "TileMap.h"

//Initialization
void TileMap::initTextureSheet()
{
	this->tileTextureSheet.loadFromFile(this->textureFile);
}

TileMap::TileMap(const float& gridSize, const unsigned& width, const unsigned& hight, const std::string& textureFile)
	: gridSizeF(gridSize), gridSizeU(static_cast<unsigned>(gridSizeF)), textureFile(textureFile)
{
	this->maxSize.x = width;
	this->maxSize.y = hight;

	this->map.reserve(static_cast<size_t>(this->maxSize.x));

	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		this->map.push_back(std::vector<Tile>());
		this->map[x].reserve(static_cast<size_t>(this->maxSize.y));
	}

	this->initTextureSheet();
}

TileMap::~TileMap()
{
}

//Accessors
const sf::Texture& TileMap::getTileTextureSheet() const 
{
	return this->tileTextureSheet;
}

//Functions
void TileMap::addTile(const unsigned& x, const unsigned& y, const sf::IntRect& texture_rect)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0)
	{
		this->map[x].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet, texture_rect));
		
		std::cout << "\nAdded  " << x << " " << y;
	}
}

void TileMap::removeTile(const unsigned& x, const unsigned& y)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0)
	{
		if (!map[x].empty())
		{
			map[x].pop_back();
			std::cout << "\nDeleted " << x << " " << y;
		}
	}
}

void TileMap::saveToFile(const std::string& file_name)
{
	/*Saves the tile map to a text file
	Basic:
	Size x y 
	gridSize
	file with textures

	Tiles:
	gridPos x y (all tiles)
	Texture rect x y w h
	collision
	type
	*/

	std::ofstream ofile(file_name);

	if (ofile.is_open())
	{
		ofile << this->maxSize.x << " " << this->maxSize.y << '\n'
			<< this->gridSizeU << '\n'
			<< this->textureFile << '\n';

		for (auto& el_x : this->map)
		{
			for (auto& el : el_x)
			{
				ofile << el.getX() << " " << el.getY() << " " 
					<< el.getAsString() << " "; //DONT SAVE LAST SPASE, FIX LATER !!!
			}
		}
	}

	ofile.close();
}

void TileMap::loadFromFile(const std::string& file_name)
{
	std::ifstream ifile(file_name);

	if (ifile.is_open())
	{
		sf::Vector2u size;
		unsigned _gridSizeU;
		std::string texture_file;

		unsigned x;
		unsigned y;

		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		this->map.clear();

		//Basics
		ifile >> size.x >> size.y >> _gridSizeU >> texture_file;

		//Tiles
		for (auto& el_x : this->map)
		{
			for (auto& el_y : el_x)
			{
				
			}
		}
	}

	ifile.close();
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