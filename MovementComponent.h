#pragma once
#include <ctime>
#include <iostream> 
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


class MovementComponent
{
private:
	//Variables
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initialisation functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);

	void update(const float& dt);
};

