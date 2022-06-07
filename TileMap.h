#pragma once
#include "Tile.h"
#include "Entity.h"

class Entity;
class Tile;

class TileMap
{
private:
	using VectorTiles       = std::vector<std::vector<Tile>>;
	using VectorTilesAbove  = std::vector<Tile*>;

	//Variables
	int    gridSizeI;
	float  gridSizeF;

	sf::Vector2i        maxSizeLevelGrid;
	sf::Vector2f        maxSizeLevelF;

	std::string         textureFile;
	sf::Texture         tileTextureSheet;
	
	sf::RectangleShape  collisionBox;

	VectorTiles         map;
	VectorTilesAbove    mapAbove;

	//Collision variables
	sf::FloatRect       playerBounds;
	sf::FloatRect       wallBounds;
	sf::FloatRect       nextPositionBounds;

	int fromX;
	int toX;
	int fromY;
	int	toY;

	bool updateCollision;

	//Init unctions
	void initTextureSheet();

	//Update functions
	void updateLevelCollision(Entity* entity, const float& dt);
	void updateTilesCollision(Entity* entity, const sf::Vector2i& gridPosition, const float& dt);

public:
	TileMap(const float& gridSize, const int& width, const int& hight, const std::string& textureFile) noexcept;
	TileMap(const std::string& file_name) ;
	virtual ~TileMap();

	//Accessors
	const sf::Texture&	getTileTextureSheet()  const;
	const sf::Vector2f& getMaxSizeF()          const;

	//Core Functions
	void addTile(const int& x, const int& y, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const int& x, const int& y);

	void saveToFile(const std::string& file);
	void loadFromFile(const std::string& file);

	//Fucntions
	void clear();

	void update(Entity* entity, const sf::Vector2i& gridPosition, const float& dt);

	void renderGameState(sf::RenderTarget& target, const sf::Vector2f& player_position = sf::Vector2f(), sf::Shader* shader = nullptr);
	void renderEditorState(sf::RenderTarget& target);
	void renderAbove(sf::RenderTarget& target, const sf::Vector2f& player_position = sf::Vector2f(), sf::Shader* shader = nullptr);
};

