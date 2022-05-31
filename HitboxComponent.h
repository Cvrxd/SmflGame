#pragma once

class HitboxComponent
{
private:
	//Variables
	//Core
	sf::Sprite* sprite;

	float offsetX;
	float offsetY;

	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

public:
	HitboxComponent() {};
	HitboxComponent(sf::Sprite& sprite, const float& offset_x, const float& offset_y, const float& width, const float& height) noexcept;


	~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPositionHitbox() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const float& x, const float& y);
	void setPosition(const sf::Vector2f& position);

	//Fucntions
	const bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);

};

