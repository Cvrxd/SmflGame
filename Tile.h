#pragma once

enum TileTypes { DEFAULT = 0, ABOVE, DAMAGING, LIGHT };

class Tile
{
private:
	//Variables
	
protected:
	//Variables
	int x;
	int	y;

	bool    collision;
	short   type;

	sf::Sprite shape;

public:
	Tile(const int& x, const int& y, const float& gridSizef, const sf::Texture& texture, const sf::IntRect& texture_rect,
		const bool& collision = false, const short& type = TileTypes::DEFAULT) noexcept;

	virtual ~Tile();
	
	//Accessors
	const std::string	getAsString     ()     const;
	const sf::Vector2f& getPositionF    ()     const;
	const sf::FloatRect getGlobalBounds ()     const;

	const bool&   getCollision ()						     const;
	const short&  getType      ()                            const;
	const bool    inersects    (const sf::FloatRect bounds)  const;

	const int&    getX ();
	const int&    getY ();

	//Functions
	void update ();
	void render (sf::RenderTarget& target, const sf::Vector2f& player_position = sf::Vector2f(), sf::Shader* shader = nullptr);
};

