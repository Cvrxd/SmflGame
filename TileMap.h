#pragma once
#include "Tile.h"
#include "Entity.h"

class Entity;
class Tile;

class TileMap
{
private:
	//Variavles
	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;

	std::string textureFile;
	sf::Texture tileTextureSheet;
	
	sf::RectangleShape collisionBox;
	std::vector<std::vector<Tile>> map;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;

	//Functions
	void initTextureSheet();

public:
	TileMap(const float& gridSize, const int& width, const int& hight, const std::string& textureFile);
	virtual ~TileMap();

	//Accessors
	const sf::Texture& getTileTextureSheet() const;

	//Core Functions
	void addTile(const int& x, const int& y, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const int& x, const int& y);

	void saveToFile(const std::string& file);
	void loadFromFile(const std::string& file);

	//Other Fucntions
	void clear();
	void updateCollision(Entity* entity, const float& dt);
	
	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);
};

