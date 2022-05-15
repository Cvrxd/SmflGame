#include "stdafx.h"
#include "SkillsComponent.h"

#define _SKILLS_COMPONENT_USE_SKILL_CHECK this->keyTime >= this->keyTimeMax && this->statsComponent.magicka > 0
//Init fuctions
inline void SkillsComponent::initAllSkills()
{
	//Skills
	this->allSkills.resize(7);
	this->playerSkills.resize(4);

	this->allSkills[0].first = RED_BLADES;
	this->allSkills[1].first = WATER_SPIKE;
	this->allSkills[2].first = THUNDER_STRIKE;
	this->allSkills[3].first = DARK_BOLT;
	this->allSkills[4].first = POISON_CLAW;
	this->allSkills[5].first = DARK_POSION;
	this->allSkills[6].first = BLOOD_SPIKE;
	//Items
	this->healthPotions.first = HEALTH;
	this->manaPotions.first = MANA;

	this->healthPotions.second = 3;
	this->manaPotions.second = 3;
}

inline void SkillsComponent::initAllAnimations()
{
	//Init textures
	this->skillTextures[RED_BLADES].second.loadFromFile("Textures/Animations/blades/red_blades.png");
	this->skillTextures[WATER_SPIKE].second.loadFromFile("Textures/Animations/red_blades.png");
	this->skillTextures[THUNDER_STRIKE].second.loadFromFile("Textures/Animations/thunder/thunder_strike.png");
	this->skillTextures[DARK_BOLT].second.loadFromFile("Textures/Animations/dark/dark_bolt.png");
	this->skillTextures[POISON_CLAW].second.loadFromFile("Textures/Animations/poison/poison_claw.png");
	this->skillTextures[DARK_POSION].second.loadFromFile("Textures/Animations/dark/dark_poison.png");
	this->skillTextures[BLOOD_SPIKE].second.loadFromFile("Textures/Animations/blood/blood.png");

	this->potionSprite.second.loadFromFile("Textures/Animations/healing.png");
	this->potionSprite.first.setScale(3.f, 3.f);

	//Init animations
	this->potionAnimation = AnimationComponent(&this->potionSprite.first, &this->potionSprite.second);

	SkillType type;
	for(int i = 0; i < this->allSkills.size(); ++i)
	{
		type = this->allSkills[i].first;
		this->skillsAnimations[type] = AnimationComponent(&this->skillTextures[type].first, &this->skillTextures[type].second);
	}
	
	//Add animations
	//Potion animations
	this->potionAnimation.addAnimation("USE1", 1, 0, 3, 0, 128, 128, 11.f);
	this->potionAnimation.addAnimation("USE2", 0, 1, 3, 1, 128, 128, 11.f);
	this->potionAnimation.addAnimation("USE3", 0, 2, 3, 2, 128, 128, 11.f);
	this->potionAnimation.addAnimation("USE4", 0, 3, 2, 3, 128, 128, 11.f);

	//Skills animation
	this->skillsAnimations[RED_BLADES].addAnimation("USE", 0, 0, 4, 0, 52, 58, 12.f);
	this->skillTextures[RED_BLADES].first.setScale(4.f, 4.f);

	this->skillsAnimations[THUNDER_STRIKE].addAnimation("USE", 0, 0, 11, 0, 64, 64, 8.f);
	this->skillTextures[THUNDER_STRIKE].first.setScale(5.f, 5.f);

	this->skillsAnimations[DARK_BOLT].addAnimation("USE", 0, 0, 10, 0, 64, 88, 8.f);
	this->skillTextures[DARK_BOLT].first.setScale(4.f, 4.f);

	this->skillsAnimations[POISON_CLAW].addAnimation("USE", 0, 0, 30, 0, 96, 96, 4.f);
	this->skillTextures[POISON_CLAW].first.setScale(4.f, 4.f);

	this->skillsAnimations[DARK_POSION].addAnimation("USE", 0, 0, 13, 0, 48, 64, 8.f);
	this->skillTextures[DARK_POSION].first.setScale(4.f, 4.f);

	this->skillsAnimations[BLOOD_SPIKE].addAnimation("USE", 0, 0, 17, 0, 48, 32, 8.f);
	this->skillTextures[BLOOD_SPIKE].first.setScale(5.f, 5.f);
}

//Constructor
SkillsComponent::SkillsComponent(StatsComponent& statsComponent)
	: statsComponent(statsComponent) ,currentRender(-1), playAnimation(false), usingPotion(false),
	keyTime(0.f), keyTimeMax(20.f), potionKeyTime(0.f), potionKeyTimeMax(10.f)
{
	this->initAllSkills();
	this->initAllAnimations();
}

SkillsComponent::~SkillsComponent()
{
}

//Accessors
const bool SkillsComponent::getKeyTime() const
{
	return this->keyTime >= this->keyTimeMax;
}

int& SkillsComponent::getMpPotions()
{
	return this->manaPotions.second;
}

int& SkillsComponent::getHpPotions()
{
	return this->healthPotions.second;
}

void SkillsComponent::addPotion(const Potions& potion_type)
{
	switch (potion_type)
	{
	case HEALTH:
		++this->healthPotions.second;
		break;
	case MANA:
		++this->manaPotions.second;
	default:
		break;
	}
}

void SkillsComponent::usePotion(const Potions& potion_type)
{
	switch (potion_type)
	{
	case HEALTH:
		--this->healthPotions.second;
		this->statsComponent.gainHP(3);
		break;
	case MANA:
		--this->manaPotions.second;
		this->statsComponent.gainMP(3);
		break;
	default:
		break;
	}
}

//Functions
void SkillsComponent::useSkill(const SkillType& skill_type)
{
	this->statsComponent.loseMP(1);
}

void SkillsComponent::addSkill(const SkillType& skill_type, const short& slot)
{
	this->playerSkills[slot].first = skill_type;
}

inline void SkillsComponent::updateClock(const float& dt)
{
	//Update key time
	this->keyTime += 10.f * dt;
	this->potionKeyTime += 10.f * dt;

	//Skills duration
	this->time = skillTimer.getElapsedTime().asSeconds();
}

void SkillsComponent::update(const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position)
{
	this->updateClock(dt);

	//Skills
	if (_SKILLS_COMPONENT_USE_SKILL_CHECK)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			currentRender = 0;
			this->skillTextures[playerSkills[currentRender].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			skillTimer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			currentRender = 1;
			this->skillTextures[playerSkills[currentRender].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			skillTimer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			currentRender = 2;
			this->skillTextures[playerSkills[currentRender].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			skillTimer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			currentRender = 3;
			this->skillTextures[playerSkills[currentRender].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			skillTimer.restart();
		}
	}

	//Potion
	if (this->potionKeyTime >= this->potionKeyTimeMax)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->manaPotions.second != 0)
		{
			this->usingPotion = true;
			this->usePotion(MANA);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->healthPotions.second != 0)
		{
			this->usingPotion = true;
			this->usePotion(HEALTH);
		}
	}
	
	//Potion animations
	if (this->usingPotion)
	{
		this->potionSprite.first.setPosition(player_position.x - 180, player_position.y - 200);
		this->potionKeyTime = 0;
		if (this->potionAnimation.play("USE1", dt, true))
		{
			if (this->potionAnimation.play("USE2", dt, true))
			{
				if (this->potionAnimation.play("USE3", dt, true))
				{
					if (this->potionAnimation.play("USE4", dt, true))
					{
						this->usingPotion = false;
					}
				}
			}

		}
	}

	//Skills animation
	if (this->playAnimation && this->playerSkills[currentRender].first != EMPTY)	
	{
		this->keyTime = 0;
		if (this->skillsAnimations[playerSkills[currentRender].first].play("USE", dt, true))
		{
			if (this->time > 4)
			{
				this->playAnimation = false;
				this->useSkill(playerSkills[currentRender].first);
				currentRender = -1;
			}
		}
	}
}

void SkillsComponent::render(sf::RenderTarget& target)
{
	if (currentRender != -1)
	{
		target.draw(this->skillTextures[playerSkills[currentRender].first].first);
	}
	if (this->usingPotion)
	{
		target.draw(this->potionSprite.first);
	}
}
