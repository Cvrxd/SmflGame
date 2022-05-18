#include "stdafx.h"
#include "Enemy.h"


//Init functions
void Enemy::initStats()
{
	this->statsComponent.hp = 3 * this->statsComponent.level;
	this->statsComponent.damagePhysical = 1 * this->statsComponent.level;
	this->statsComponent.damageMagical = 1 * this->statsComponent.level;
}

//Constructor
Enemy::Enemy(const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player)
	:statsComponent(1), animationComponent(&this->sprite, &texture_sheet), player(player)
{

}

Enemy::~Enemy()
{
}


