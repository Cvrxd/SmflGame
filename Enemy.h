#pragma once
#include "Entity.h"
#include "Player.h"

class Entity;
class Player;

class Enemy : public Entity
{
protected:
	//Variables
	Player* player;

	bool isAttaking = false;
	bool takingHit = false;
	bool isDead = false;
	//Components
	AnimationComponent animationComponent;
	StatsComponent statsComponent;

	//init functions
	virtual void initStats();
	virtual void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) = 0;
	virtual void createAnimationComponent(sf::Texture& texture_sheet) = 0;
	virtual void addAnimations() = 0;
public:
	Enemy(const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player);
	virtual ~Enemy();

	//Functions
	virtual void updatePlayerImpact() = 0;
	virtual void updateAttack(const float& dt) = 0;
	virtual void updateMovement(const float& dt) = 0;
	virtual void updateAnimations(const float& dt) = 0;
};

