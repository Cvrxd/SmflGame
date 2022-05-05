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
	unsigned gridSizeU;
	sf::Vector2u maxSize;

	std::string textureFile;
	sf::Texture tileTextureSheet;
	
	sf::RectangleShape collisionBox;
	std::vector<std::vector<Tile>> map;

	//Functions
	void initTextureSheet();

public:
	TileMap(const float& gridSize, const unsigned& width, const unsigned& hight, const std::string& textureFile);
	virtual ~TileMap();

	//Accessors
	const sf::Texture& getTileTextureSheet() const;

	//Core Functions
	void addTile(const unsigned& x, const unsigned& y, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned& x, const unsigned& y);

	void saveToFile(const std::string& file);
	void loadFromFile(const std::string& file);

	//Other Fucntions
	void updateCollision(Entity* entity);
	
	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);
};

