#pragma once
//#include"stdafx.h"

class HitboxComponent
{
private:
	//Variables
	//Core
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, const float& offset_x, const float& offset_y, const float& width, const float& height);
	~HitboxComponent();

	//Fucntions
	const bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);

};

