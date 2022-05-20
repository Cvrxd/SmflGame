#include "stdafx.h"
#include "Enemy.h"

void Enemy::initImpactAnimations()
{
	this->takeHitSprite.first.loadFromFile("Textures/animations/hit/hit02.png");
	this->takeHitSprite.second.setScale(3.f, 3.f);

	this->skillImpactSprite.first.loadFromFile("Textures/animations/hit/skill_hit.png");
	this->skillImpactSprite.second.setScale(4.f, 4.f);

	this->takeHitAnimation = { &this->takeHitSprite.second, &this->takeHitSprite.first };
	this->skillImpactAnimation = { &this->skillImpactSprite.second, &this->skillImpactSprite.first };

	//Take hit animations
	this->takeHitAnimation.addAnimation("TAKE_HIT1", 0, 0, 4, 0, 64, 64, 7.f);
	this->takeHitAnimation.addAnimation("TAKE_HIT2", 0, 1, 4, 1, 64, 64, 7.f);

	this->skillImpactAnimation.addAnimation("SKILL_IMPACT", 0, 0, 14, 0, 64, 49, 4.f);
}

//Init functions
void Enemy::initStats()
{
	this->statsComponent.hp = 3 * this->statsComponent.level;
	this->statsComponent.damagePhysical = 1 * this->statsComponent.level;
	this->statsComponent.damageMagical = 1 * this->statsComponent.level;
}

//Constructor
Enemy::Enemy(const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player)
	:statsComponent(1), animationComponent(&this->sprite, &texture_sheet), player(player), textureSheet(&texture_sheet)
{

}

Enemy::~Enemy()
{
}

const bool& Enemy::dead()
{
	return this->isDead;
}


