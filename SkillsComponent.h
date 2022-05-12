#pragma once
#include"AnimationComponent.h"

enum SkillType {RED_BLADES = 0, WATER_SPIKE , THUNDER_STRIKE, DARK_BOLT, POISON_CLAW, DARK_POSION};

class SkillsComponent
{
private:
	//Variables
	sf::Clock skillTimer;

	std::vector<std::pair<SkillType, int>> allSkills;
	std::vector<std::pair<SkillType, int>> playerSkills;

	std::map<SkillType, AnimationComponent> skillsAnimations;
	std::map<SkillType, std::pair<sf::Sprite, sf::Texture>> skillSprites;
	
	//Init functions
	void initAllSkills();
	void initAllAnimations();

public:
	SkillsComponent();
	~SkillsComponent();

	//Functions
	const short activated();
	void useSkill();
	void addSkill(const SkillType& skill_type, const short& slot);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

