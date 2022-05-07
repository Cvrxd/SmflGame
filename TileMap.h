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
	sf::Vector2i maxSizeLevelGrid;
	sf::Vector2f maxSizeLevelF;

	std::string textureFile;
	sf::Texture tileTextureSheet;
	
	sf::RectangleShape collisionBox;

	std::vector<std::vector<Tile>> map;
	std::vector<Tile*> mapAbove;

	//Collision variables
	int fromX;
	int toX;
	int fromY;
	int toY;

	//Functions
	void initTextureSheet();

public:
	TileMap(const float& gridSize, const int& width, const int& hight, const std::string& textureFile);
	TileMap(const std::string& file_name);
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

	void updateLevelCollision(Entity* entity, const float& dt);
	void updateTilesCollision(Entity* entity, const sf::Vector2i& gridPosition, const float& dt);
	
	void update(Entity* entity, const float& dt);

	void renderGameState(sf::RenderTarget& target);
	void renderEditorState(sf::RenderTarget& target);
	void renderAbove(sf::RenderTarget& target);

};

