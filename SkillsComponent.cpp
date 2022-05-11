#include "stdafx.h"
#include "SkillsComponent.h"

//Init fuctions
void SkillsComponent::initAllSkills()
{
	this->allSkills.resize(5);
	this->playerSkills.resize(4);

	this->allSkills[0].first = RED_BLADES;
	this->allSkills[1].first = WATER_SPIKE;
	this->allSkills[2].first = THUNDER_STRIKE;
	this->allSkills[3].first = DARK_BOLT;
}

void SkillsComponent::initAllAnimations()
{
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
