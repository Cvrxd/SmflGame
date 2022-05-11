#pragma once

enum SkillType {RED_BLADES = 0, WATER_SPIKE , THUNDER_STRIKE, DARK_BOLT};

class SkillsComponent
{
private:
	//Variables
	std::vector<std::pair<SkillType, int>> allSkills;
	std::vector<std::pair<SkillType, int>> playerSkills;

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

