#include "stdafx.h"
#include "LevelingComponent.h"

//Constructor
LevelingComponent::LevelingComponent(const int& level)
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

LevelingComponent::~LevelingComponent()
{
}

std::string LevelingComponent::debugPrint()
{
	std::stringstream ss;

	ss << "\nLevel " << this->level
		<< "\nExp " << this->exp
		<< "\nExpNext " << this->expNext
		<< "\nstat points " << this->statsPoints;

	return ss.str();
}

//Functions
void LevelingComponent::gainEXP(const unsigned& exp)
{
	this->exp += exp;
	this->updateLevel();
}

void LevelingComponent::loseHP(const int& hp)
{
	this->hp -= hp;
	if (this->hp < 0)
	{
		this->hp = 0;

		//GameOVer
	}
}

void LevelingComponent::gainHP(const int& hp)
{
	this->hp += hp;
	if (this->hp > this->hpMAX)
	{
		this->hp = this->hpMAX;
	}
}

void LevelingComponent::updateLevel()
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

void LevelingComponent::updateStats(const bool& reset)
{
	//Reset main stats if needed
	if (reset)
	{
		this->armor = this->armorMAX;
		this->hp = this->hpMAX;
		this->magicka = magickaMAX;
	}
}

void LevelingComponent::update()
{
}
