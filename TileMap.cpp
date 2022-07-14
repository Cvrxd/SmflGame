#include "stdafx.h"
#include "TileMap.h"

//Initialization
inline void TileMap::initTextureSheet()
{
	sf::Image image;
	image.loadFromFile(this->textureFile);
	image.createMaskFromColor(sf::Color(0, 0, 0));
	this->tileTextureSheet.loadFromImage(image);
}

//Constructor
TileMap::TileMap(const float& gridSize, const int& width, const int& hight, const std::string& textureFile) noexcept
	: gridSizeF(gridSize), gridSizeI(static_cast<int>(gridSizeF)), textureFile(textureFile), 
	fromX(0), toX(0), fromY(0), toY(0)
{
	//Max size init
	this->maxSizeLevelGrid.x = width;
	this->maxSizeLevelGrid.y = hight;

	this->maxSizeLevelF.x = static_cast<float>(width) * gridSize;
	this->maxSizeLevelF.y = static_cast<float>(hight) * gridSize;

	//Reserve space for map
	this->map.reserve(static_cast<size_t>(this->maxSizeLevelGrid.x));

	for (size_t y = 0; y < this->maxSizeLevelGrid.y; ++y)
	{
		this->map.push_back(std::vector<Tile>());
		this->map[y].reserve(static_cast<size_t>(this->maxSizeLevelGrid.y));
	}

	this->initTextureSheet();

	
	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color::Transparent);

	////Collision BOX for DEBUG////
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::TileMap(const std::string& file_name)
	:fromX(0), toX(0), fromY(0), toY(0)
{
	this->loadFromFile(file_name);
}

TileMap::~TileMap()
{
	for (auto& el : this->mapAbove)
	{
		el = nullptr;
	}
}

//Accessors
const sf::Texture& TileMap::getTileTextureSheet() const 
{
	return this->tileTextureSheet;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeLevelF;
}

//Public functions
void TileMap::addTile(const int& x, const int& y, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSizeLevelGrid.x && x >= 0 && y < this->maxSizeLevelGrid.y && y >= 0)
	{
		this->map[y].push_back(Tile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision, type));
		std::cout << "\nAdded  " << x << " " << y;
	}
}

void TileMap::removeTile(const int& x, const int& y)
{
	if (x < this->maxSizeLevelGrid.x && x >= 0 && y < this->maxSizeLevelGrid.y && y >= 0)
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
		ofile << this->maxSizeLevelGrid.x << " " << this->maxSizeLevelGrid.y << '\n'
			<< this->gridSizeF << '\n'
			<< this->textureFile << '\n';

		for (auto& el_x : this->map)
		{
			for (auto& el : el_x)
			{
				ofile << el.getX() << " " << el.getY() << " " << el.getAsString() << " ";
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
		int _gridSizeI;
		std::string texture_file;

		ifile >> size.x >> size.y >> _gridSizeI >> texture_file;

		this->gridSizeF          = static_cast<float>(_gridSizeI);
		this->gridSizeI          = _gridSizeI;

		this->maxSizeLevelGrid.x = size.x;
		this->maxSizeLevelGrid.y = size.y;

		this->maxSizeLevelF.x    = static_cast<float>(size.x * _gridSizeI);
		this->maxSizeLevelF.y    = static_cast<float>(size.y * _gridSizeI + _gridSizeI - 25.f);

		this->textureFile        = texture_file;
		//Basic
		
		this->map.clear();

		//Tiles
		int x;
		int y;

		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//===========
		this->map.reserve(static_cast<size_t>(this->maxSizeLevelGrid.x));
		this->mapAbove.reserve(20);

		for (size_t y = 0; y < this->maxSizeLevelGrid.y; ++y)
		{
			this->map.push_back(std::vector<Tile>());
			this->map[y].reserve(static_cast<size_t>(this->maxSizeLevelGrid.y));
		}

		this->initTextureSheet();
		//============

		while (ifile >> x >> y >> trX >> trY >> collision >> type)
		{
			this->map[y].push_back(Tile(x, y, this->gridSizeF, this->tileTextureSheet, 
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), collision, type));

			if (this->map[y].back().getType() == TileTypes::ABOVE)
			{
				this->mapAbove.push_back(&this->map[y].back());
			}
		}
		//Tiles
	}
	ifile.close();
}

void TileMap::clear()
{
	for (auto& el : map)
	{
		el.clear();
	}
	this->map.clear();
}

void TileMap::update(Entity* entity, const sf::Vector2i& gridPosition, const float& dt)
{	
	this->updateTilesCollision(entity, gridPosition, dt);
}

void TileMap::renderGameState(sf::RenderTarget& target, const sf::Vector2f& player_position, sf::Shader* shader)
{
	this->updateCollision = false;

	for (auto& el_x : this->map)
	{
		for (auto& el_y : el_x)
		{
			if (el_y.getX() < toX && el_y.getY() < toY && el_y.getX() > fromX && el_y.getY() > fromY && el_y.getType() != TileTypes::ABOVE)
			{
				el_y.render(target, player_position, shader);

				if (el_y.getCollision())
				{
					this->updateCollision = true; // if need to update collision
				}
			}
		}
	}	
}

void TileMap::renderEditorState(sf::RenderTarget& target)
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

void TileMap::renderAbove(sf::RenderTarget& target, const sf::Vector2f& player_position, sf::Shader* shader)
{
	for (auto& el : this->mapAbove)
	{
		if (el->getX() < toX && el->getY() < toY && el->getX() > fromX && el->getY() > fromY)
		{
			el->render(target, player_position, shader);
		}
	}
}
