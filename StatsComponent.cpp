#include "stdafx.h"
#include "StatsComponent.h"

//Constructor
StatsComponent::StatsComponent(const int& level)
	:level(level), exp(0), statsPoints(3), skillPoints(1)
{
	//Exp
	this->expNext = static_cast<unsigned>(this->level * 20 - (this->level * 5));

	//Base init stats
	this->hp = this->hpMAX = 3;
	this->magicka = this->magickaMAX = 3;
	this->armor = this->armorMAX = 1;

	//Atributes
	this->damagePhysical = 1;
	this->damageMagical = 1;

	//Update stats
	this->updateStats(true);
}

StatsComponent::~StatsComponent()
{
}

//Functions
void StatsComponent::addItem(const Items& item)
{
	switch (item)
	{
	case SWORD:
		++this->damagePhysical;
		break;
	case STAFF:
		++this->damageMagical;
		break;
	case DAGGER:
		++this->damagePhysical;
	case MAGIK_SWORD:
		++this->damageMagical;
	case RING:
		++this->magickaMAX;
		break;
	case NECKLASE:
		++this->magickaMAX;
		break;
	case HELMET:
		++this->armorMAX;
		break;
	case ARMOR:
		++this->armorMAX;
		break;
	case GLOVES:
		++this->armorMAX;
		break;
	case BOOTS:
		++this->armorMAX;
		break;
	default:
		break;
	}
}

void StatsComponent::gainEXP(const unsigned& exp)
{
	this->exp += exp;
	this->updateLevel();
}

void StatsComponent::loseHP(const int& hp)
{
	this->hp -= hp;
	if (this->hp < 0)
	{
		this->hp = 0;

		//GameOVer
	}
}

void StatsComponent::gainHP(const int& hp)
{
	this->hp += hp;
	if (this->hp > this->hpMAX)
	{
		this->hp = this->hpMAX;
	}
}

void StatsComponent::updateLevel()
{
	//New level gained
	if(this->exp >= this->expNext)
	{
		//Each 10th level
		if ((++this->level) % 10 == 0)
		{
			++this->damagePhysical;
			++this->damageMagical;
			++this->skillPoints;
			++this->statsPoints;
		}

		this->exp = 0;
		this->expNext = static_cast<unsigned>(this->level * 20 - (this->level * 5));

		++this->statsPoints;
		++this->skillPoints;
	}
	
}

void StatsComponent::updateStats(const bool& reset)
{
	//Reset main stats if needed
	if (reset)
	{
		this->armor = this->armorMAX;
		this->hp = this->hpMAX;
		this->magicka = magickaMAX;
	}

}

void StatsComponent::update()
{
}
