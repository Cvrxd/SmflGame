#pragma once

enum MovementStates {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVE_UP, MOVE_DOWN};

class MovementComponent
{
private:
	//Variables
	sf::Sprite* sprite;

	float maxVelocityOriginal;
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initialisation functions

public:
	MovementComponent() {};
	MovementComponent(sf::Sprite& sprite, const float& maxVelocity, const float& acceleration, const float& deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;
	const bool getState(const short unsigned state) const;

	//Functions
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float& dir_x, const float& dir_y, const float& dt, const bool& dash = false);
	void update(const float& dt);
};

