#pragma once
#include "Entity.h"
#include "Player.h"
#include "DropComponent.h"

class Entity;
class Player;
class DropComponent;
class AnimationComponent;
class StatsComponent;

class Enemy : public Entity
{
protected:
	//Variables
	std::pair<sf::Texture, sf::Sprite> takeHitSprite;
	std::pair<sf::Texture, sf::Sprite> skillImpactSprite;

	AnimationComponent takeHitAnimation;
	AnimationComponent skillImpactAnimation;

	Player* player;
	sf::Texture* textureSheet;

	std::function<void()> setOriginLeft;
	std::function<void()> setOriginRight;

	bool isAttaking = false;
	bool isTakingDamage = false;

	bool hitImpact = false;
	bool skillImpact = false;
	bool isDead = false;

	//Components
	AnimationComponent animationComponent;
	StatsComponent statsComponent;
	DropComponent dropComponent;

	//init functions
	virtual void initImpactAnimations();
	virtual void initStats();
	virtual void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) = 0;
	virtual void createAnimationComponent(sf::Texture& texture_sheet) = 0;
	virtual void addAnimations() = 0;

	//Other functions
	virtual void enemyDead(const float& dt) = 0;
public:
	Enemy(const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player);
	virtual ~Enemy();

	//Accessors
	const bool& dead();

	//Functions
	virtual void updatePlayerImpact(const float& dt) = 0;
	virtual void updateAttack(const float& dt) = 0;
	virtual void updateMovement(const float& dt) = 0;
	virtual void updateAnimations(const float& dt) = 0;
};

