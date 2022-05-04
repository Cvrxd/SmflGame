#pragma once

enum TileTypes { DEFAULT = 0, DAMAGING };

class Tile
{
private:
	//Variables
	
protected:
	//Variables
	sf::RectangleShape shape;
	bool collision;
	short type;

	unsigned x;
	unsigned y;
	
public:
	Tile(const unsigned& x, const unsigned& y, const float& gridSizef, const sf::Texture& texture, const sf::IntRect& texture_rect,
		const bool& collision = false, const short& type = TileTypes::DEFAULT);

	virtual ~Tile();
	
	//Accessors
	const std::string getAsString() const;

	void setX(const unsigned& x);
	void setY(const unsigned& y);
	const unsigned& getX();
	const unsigned& getY();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

