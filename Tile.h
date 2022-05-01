#pragma once
class Tile
{
private:
	//Variables
	
protected:
	//Variables
	sf::RectangleShape shape;

	float x;
	float y;
	bool added;

public:
	Tile(const float& x, const float& y, const float& gridSizef);
	virtual ~Tile();
	
	//Accessors
	const sf::Vector2u& getCoordinates();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

