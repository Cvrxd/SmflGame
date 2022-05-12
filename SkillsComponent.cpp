#include "stdafx.h"
#include "SkillsComponent.h"

//Init fuctions
void SkillsComponent::initAllSkills()
{
	this->allSkills.resize(10);
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
	//this->skillSprites
}

//Constructor
SkillsComponent::SkillsComponent()
{
	this->initAllSkills();
	this->initAllAnimations();
}

SkillsComponent::~SkillsComponent()
{
}

//Functions
const short SkillsComponent::activated()
{
	return 0;
}

void SkillsComponent::useSkill()
{
}

void SkillsComponent::addSkill(const SkillType& skill_type, const short& slot)
{
	this->playerSkills[slot].first = skill_type;
}

void SkillsComponent::update(const float& dt)
{
}

void SkillsComponent::render(sf::RenderTarget& target)
{
}
