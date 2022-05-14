#include "stdafx.h"
#include "SkillsComponent.h"

//Init fuctions
void SkillsComponent::initAllSkills()
{
	this->allSkills.resize(6);
	//this->skillsAnimations.reserve(6);
	this->playerSkills.resize(4);

	this->allSkills[0].first = RED_BLADES;
	this->allSkills[1].first = WATER_SPIKE;
	this->allSkills[2].first = THUNDER_STRIKE;
	this->allSkills[3].first = DARK_BOLT;
	this->allSkills[4].first = POISON_CLAW;
	this->allSkills[5].first = DARK_POSION;
}

void SkillsComponent::initAllAnimations()
{
	//Init textures
	this->skillTextures[RED_BLADES].second.loadFromFile("Textures/Animations/blades/red_blades.png");
	this->skillTextures[WATER_SPIKE].second.loadFromFile("Textures/Animations/red_blades.png");
	this->skillTextures[THUNDER_STRIKE].second.loadFromFile("Textures/Animations/thunder/thunder_strike.png");
	this->skillTextures[DARK_BOLT].second.loadFromFile("Textures/Animations/dark/dark_bolt.png");
	this->skillTextures[POISON_CLAW].second.loadFromFile("Textures/Animations/poison/poison_claw.png");
	this->skillTextures[DARK_POSION].second.loadFromFile("Textures/Animations/dark/dark_poison.png");

	//Init animations
	SkillType type;
	for(int i = 0; i < this->allSkills.size(); ++i)
	{
		type = this->allSkills[i].first;
		this->skillsAnimations[type] = AnimationComponent(&this->skillTextures[type].first, &this->skillTextures[type].second);
	}
	
	//Add animations
	this->skillsAnimations[RED_BLADES].addAnimation("USE", 0, 0, 4, 0, 52, 58, 12.f);
	this->skillTextures[RED_BLADES].first.setScale(4.f, 4.f);

	this->skillsAnimations[THUNDER_STRIKE].addAnimation("USE", 0, 0, 11, 0, 64, 64, 8.f);
	this->skillTextures[THUNDER_STRIKE].first.setScale(4.f, 4.f);

	this->skillsAnimations[DARK_BOLT].addAnimation("USE", 0, 0, 10, 0, 64, 88, 8.f);
	this->skillTextures[DARK_BOLT].first.setScale(4.f, 4.f);

	this->skillsAnimations[POISON_CLAW].addAnimation("USE", 0, 0, 30, 0, 96, 96, 4.f);
	this->skillTextures[POISON_CLAW].first.setScale(4.f, 4.f);

	this->skillsAnimations[DARK_POSION].addAnimation("USE", 0, 0, 13, 0, 48, 64, 8.f);
	this->skillTextures[DARK_POSION].first.setScale(4.f, 4.f);
}

//Constructor
SkillsComponent::SkillsComponent(StatsComponent& statsComponent)
	: statsComponent(statsComponent) ,currentRender(-1), playAnimation(false), keyTime(0.f), keyTimeMax(25.f)
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

//Functions
void SkillsComponent::useSkill(const SkillType& skill_type)
{
	this->statsComponent.loseMP(1);
}

void SkillsComponent::addSkill(const SkillType& skill_type, const short& slot)
{
	this->playerSkills[slot].first = skill_type;
}

void SkillsComponent::updateClock(const float& dt)
{
	//Update key time
	this->keyTime += 10.f * dt;

	//Skills duration
	this->time = skillTimer.getElapsedTime().asSeconds();
}

void SkillsComponent::update(const float& dt, const sf::Vector2f& skill_position)
{
	this->updateClock(dt);

	if (this->getKeyTime() && this->statsComponent.magicka > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			this->skillTextures[playerSkills[0].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			currentRender = 0;
			skillTimer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			this->skillTextures[playerSkills[1].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			currentRender = 1;
			skillTimer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			this->skillTextures[playerSkills[2].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			currentRender = 2;
			skillTimer.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			this->skillTextures[playerSkills[3].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);
			this->playAnimation = true;
			currentRender = 3;
			skillTimer.restart();
		}
	}
	

	if (this->playAnimation && this->playerSkills[currentRender].first != EMPTY)	
	{
		this->keyTime = 0;
		if (this->skillsAnimations[playerSkills[currentRender].first].play("USE", dt, true))
		{
			if (this->time > 2)
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
}
