#include "stdafx.h"
#include "TileMap.h"

//Initialization
void TileMap::initTextureSheet()
{
	this->tileTextureSheet.loadFromFile(this->textureFile);
}

//Constructor
TileMap::TileMap(const float& gridSize, const int& width, const int& hight, const std::string& textureFile)
	: gridSizeF(gridSize), gridSizeU(static_cast<unsigned>(gridSizeF)), textureFile(textureFile), 
	fromX(0), toX(0), fromY(0), toY(0)
{
	//Max size init
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = hight;

	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(hight) * gridSize;

	//Reserve space for map
	this->map.reserve(static_cast<size_t>(this->maxSizeWorldGrid.x));

	for (size_t y = 0; y < this->maxSizeWorldGrid.y; ++y)
	{
		this->map.push_back(std::vector<Tile>());
		this->map[y].reserve(static_cast<size_t>(this->maxSizeWorldGrid.y));
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
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0)
	{
		this->map[y].push_back(Tile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision, type));
		
		std::cout << "\nAdded  " << x << " " << y;
	}
}

void TileMap::removeTile(const unsigned& x, const unsigned& y)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0)
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
		ofile << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << '\n'
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
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
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
		this->map.reserve(static_cast<size_t>(this->maxSizeWorldGrid.x));

		for (size_t y = 0; y < this->maxSizeWorldGrid.y; ++y)
		{
			this->map.push_back(std::vector<Tile>());
			this->map[y].reserve(static_cast<size_t>(this->maxSizeWorldGrid.y));
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

void TileMap::clear()
{
	for (auto& el : map)
	{
		el.clear();
	}
	this->map.clear();
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	//World Bounds Collision
	//X check
	if (entity->getPosition().x  < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	//Y check
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//Tiles Collision
	this->fromX = entity->getGridPosition(this->gridSizeU).x - 3;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeWorldGrid.x)
	{
		this->fromX = this->maxSizeWorldGrid.x;
	}

	this->toX = entity->getGridPosition(this->gridSizeU).x + 4;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x;
	}

	this->fromY = entity->getGridPosition(this->gridSizeU).y - 3;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}

	this->toY = entity->getGridPosition(this->gridSizeU).y + 4;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}
	

	//Collision for loup
	for (auto& el_x : this->map)
	{
		for (auto& el : el_x)
		{
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = el.getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPosition(dt);

			if (el.getX() < toX && el.getY() < toY && el.getX() > fromX && el.getY() > fromY)
			{
				if (el.getCollision() && el.inersects(nextPositionBounds))
				{ 
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}

}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	//DEBUG TEST !!! REMOVE LATER !!!
	if (entity)
	{
		for (auto& el_x : this->map)
		{
			for (auto& el : el_x)
			{
 				if (el.getX() < toX && el.getY() < toY && el.getX() > fromX && el.getY() > fromY)
				{
					el.render(target);
					//DEBUG
					if (el.getCollision())
					{
						this->collisionBox.setPosition(el.getPositionF());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
	else
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
	
}