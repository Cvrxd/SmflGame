#pragma once
#include"MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	//core
	sf::Sprite sprite;
	
	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, float acceleration, float deceleration);

	// Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);

	//update
	virtual void update(const float& dt);

	//render
	virtual void render(sf::RenderTarget* target);

};

