#pragma once
#include <Components/EntitiesComponents/HitboxComponent.h>
#include <Components/EntitiesComponents/StatsComponent.h>
#include <Components/EntitiesComponents/SkillsComponent.h>
#include <Components/EntitiesComponents/MovementComponent.h>

#include <Components/GeneralComponents/PopUpTextComponent.h>
#include <Components/GeneralComponents/AnimationComponent.h>

class SkillsComponent;
class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class StatsComponent;
class SkillsComponent;
class PopUpTextComponent;

class Entity
{
protected:
	//Variables
	sf::Sprite          sprite;

	HitboxComponent     hitboxComponent;
	MovementComponent   movementComponent;

	virtual void initVariables();
public:
	Entity() noexcept;
	virtual ~Entity();

	//Component functions
	void setTexture              (sf::Texture& texture);

	void createHitboxComponent   (sf::Sprite& sprite, const float& offset_x, const float& offset_y, const float& width, const float& height);
	void createMovementComponent (const float& maxVelocity, const float& acceleration, const float& deceleration);

	//Accessors 
	virtual const sf::Vector2f&  getPosition      ()                        const;
	virtual const sf::Vector2f   getCenter        ()                        const;
	virtual const sf::Vector2i   getGridPosition  (const int& gridSizeI)    const;
	virtual const sf::FloatRect  getGlobalBounds  ()                        const;
	virtual const sf::FloatRect& getNextPosition  (const float& dt);

	// Functions
	virtual void stopVelocity  ();
	virtual void stopVelocityX ();
	virtual void stopVelocityY ();

	virtual void setPosition   (const float& x, const float& y);
	virtual void move          (const float& x, const float& y, const float& dt, const bool& dash = false);
	
	virtual void update        (const float& dt, sf::Vector2f mouse_pos_view)            = 0;
	virtual void render        (sf::RenderTarget& target, sf::Shader* shader = nullptr)  = 0;

};

