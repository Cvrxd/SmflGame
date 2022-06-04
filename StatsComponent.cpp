#include "stdafx.h"
#include "StatsComponent.h"

//Constructor
StatsComponent::StatsComponent(const int& level) noexcept
	:level(level), exp(0), statsPoints(3), skillPoints(1), coins(0), crystals(0)
{
	//Exp
	this->expNext = static_cast<unsigned>(this->level * 20 - (this->level * 5));

	//Base init stats
	this->hp = this->hpMAX = 5;
	this->magicka = this->magickaMAX = 3;
	this->armor = this->armorMAX = 3;

	//Atributes
	this->damagePhysical = 1;
	this->damageMagical = 1;
	this->critRate = 10.f;

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
	case Items::SWORD:
		++this->damagePhysical;
		break;
	case Items::STAFF:
		++this->damageMagical;
		break;
	case Items::RING:
		++this->magickaMAX;
		break;
	case Items::NECKLASE:
		++this->magickaMAX;
		break;
	case Items::HELMET:
		++this->armorMAX;
		break;
	case Items::ARMOR:
		++this->armorMAX;
		break;
	case Items::GLOVES:
		++this->armorMAX;
		break;
	case Items::BOOTS:
		++this->armorMAX;
		break;
	default:
		break;
	}
}

void StatsComponent::upgradeItem(const Items& item, const int& level)
{
	//
}

void StatsComponent::gainEXP(const unsigned& exp)
{
	this->exp += exp;
	this->updateLevel();
}

void StatsComponent::gainHP(const int& hp)
{
	this->hp += hp;
	if (this->hp > this->hpMAX)
	{
		this->hp = this->hpMAX;
	}
}

void StatsComponent::loseHP(const int& hp)
{
	if (this->armor != 0)
	{
		this->loseArmor(hp);
	}
	else
	{
		this->hp -= hp;
		if (this->hp < 0)
		{
			this->hp = 0;
			//GameOVer
		}
	}
}

void StatsComponent::gainArmor(const int& armor)
{
	if (this->armor < this->armorMAX)
	{
		++this->armor;
	}
}

void StatsComponent::loseArmor(const int& armor)
{
	if (this->armor - armor >= 0)
	{
		this->armor -= armor;
	}
	else
	{
		this->armor = 0;
		this->loseHP(armor - this->armor);
	}
}

void StatsComponent::gainMP(const int& mp)
{
	if (this->magicka + mp < this->magickaMAX)
	{
		this->magicka += mp;
	}
	else
	{
		this->magicka = this->magickaMAX;
	}
}

void StatsComponent::loseMP(const int& mp)
{
	if (this->magicka > 0)
	{
		--this->magicka;
	}
}

void StatsComponent::gainCrystals(const int& crystals)
{
	this->crystals += crystals;
}

void StatsComponent::loseCrystals(const int& crystals)
{
	this->crystals -= crystals;
	if (this->crystals < 0)
	{
		this->crystals = 0;
	}
}

void StatsComponent::gainCoins(const int& coins)
{
	this->coins += coins;
}

void StatsComponent::loseCoins(const int& coins)
{
	this->coins -= coins;
	if (coins <= 0)
	{
		this->coins = 0;
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

		//Each 5th level
		if ((++this->level) % 5 == 0)
		{
			++this->critRate;
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
