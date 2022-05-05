#include "stdafx.h"
#include "TileMap.h"

//Initialization
void TileMap::initTextureSheet()
{
	this->tileTextureSheet.loadFromFile(this->textureFile);
}

//Constructor
TileMap::TileMap(const float& gridSize, const unsigned& width, const unsigned& hight, const std::string& textureFile)
	: gridSizeF(gridSize), gridSizeU(static_cast<unsigned>(gridSizeF)), textureFile(textureFile)
{
	this->maxSize.x = width;
	this->maxSize.y = hight;

	this->map.reserve(static_cast<size_t>(this->maxSize.x));

	for (size_t y = 0; y < this->maxSize.y; ++y)
	{
		this->map.push_back(std::vector<Tile>());
		this->map[y].reserve(static_cast<size_t>(this->maxSize.y));
	}

	this->initTextureSheet();

	////Collision BOX for DEBUG////
	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
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
void TileMap::addTile(const unsigned& x, const unsigned& y, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0)
	{
		this->map[y].push_back(Tile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision, type));
		
		std::cout << "\nAdded  " << x << " " << y;
	}
}

void TileMap::removeTile(const unsigned& x, const unsigned& y)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0)
	{
		if (!map[y].empty())
		{
			map[y].pop_back();
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
				ofile << el.getX() << " " << el.getY() << " " << el.getAsString() << " "; //DONT SAVE LAST SPASE, FIX LATER !!!
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
		//Basics
		sf::Vector2u size;
		unsigned _gridSizeU;
		std::string texture_file;

		ifile >> size.x >> size.y >> _gridSizeU >> texture_file;

		this->gridSizeF = static_cast<float>(_gridSizeU);
		this->gridSizeU = _gridSizeU;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->textureFile = texture_file;
		//Basic
		
		this->map.clear();

		//Tiles
		unsigned x;
		unsigned y;

		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//===========
		this->map.reserve(static_cast<size_t>(this->maxSize.x));

		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			this->map.push_back(std::vector<Tile>());
			this->map[y].reserve(static_cast<size_t>(this->maxSize.y));
		}

		this->initTextureSheet();
		//============

		while (ifile >> x >> y >> trX >> trY >> collision >> type)
		{
			this->map[y].push_back(Tile(x, y, this->gridSizeF, this->tileTextureSheet, 
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), collision, type));
		}

		//Tiles
	}

	ifile.close();
}

void TileMap::updateCollision(Entity* entity)
{

}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	for (auto& el_x : this->map)
	{
		for (auto& el_y : el_x)
		{
			el_y.render(target);
			
			//DEBUG
			if (el_y.getCollision())
			{
				this->collisionBox.setPosition(el_y.getPositionF());
				target.draw(this->collisionBox);
			}
		}
	}
}