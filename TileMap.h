#pragma once
#include "Tile.h"

class Tile;

class TileMap
{
private:
	//Variavles
	float gridSizeF;
	unsigned gridSizeU;
	std::string textureFile;

	sf::Vector2u maxSize;
	std::vector<std::vector<Tile>> map;

	sf::Texture tileTextureSheet;

	//Functions
	void initTextureSheet();

public:
	TileMap(const float& gridSize, const unsigned& width, const unsigned& hight, const std::string& textureFile);
	virtual ~TileMap();

	//Accessors
	const sf::Texture& getTileTextureSheet() const;

	//Functions
	void addTile(const unsigned& x, const unsigned& y, const sf::IntRect& texture_rect);
	void removeTile(const unsigned& x, const unsigned& y);

	void saveToFile(const std::string& file);
	void loadFromFile(const std::string& file);

	void update();
	void render(sf::RenderTarget& target);
};

