#pragma once
#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;

class Entity
{
private:
	void initVariables();

protected:
	//core
	sf::Sprite sprite;
	
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, const float& offset_x, const float& offset_y, const float& width, const float& height);
	void createMovementComponent(const float& maxVelocity, const float& acceleration, const float& deceleration);
	virtual void createAnimationComponent(sf::Texture& texture_sheet);

	//Accessors 
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2u getGridPosition(const unsigned& gridSizeU) const;
	virtual const sf::FloatRect& getGlobalBounds() const;
	virtual const sf::FloatRect& getNextPosition(const float& dt) const;

	// Functions
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void setPosition(const float& x, const float& y);
	virtual void move(const float& x, const float& y, const float& dt);
	
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

};

