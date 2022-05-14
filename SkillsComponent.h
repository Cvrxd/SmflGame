#pragma once
#include"StatsComponent.h"
#include"AnimationComponent.h"

class AnimationComponent;
class StatsComponent;

enum SkillType {EMPTY = 0, RED_BLADES ,WATER_SPIKE , THUNDER_STRIKE, DARK_BOLT, POISON_CLAW, DARK_POSION};

class SkillsComponent
{
private:
	//Variables
	sf::Clock skillTimer;

	StatsComponent& statsComponent;

	float time;
	float keyTime;
	float keyTimeMax;

	std::vector<std::pair<SkillType, int>> allSkills;
	std::vector<std::pair<SkillType, int>> playerSkills;

	std::map<SkillType, AnimationComponent> skillsAnimations;
	int currentRender;
	bool playAnimation;

	std::map<SkillType, std::pair<sf::Sprite, sf::Texture>> skillTextures;
	
	//Init functions
	void initAllSkills();
	void initAllAnimations();

public:
	SkillsComponent(StatsComponent& statsComponent);
	~SkillsComponent();

	//Accessors
	const bool getKeyTime() const;

	//Functions
	void useSkill(const SkillType& skill_type);
	void addSkill(const SkillType& skill_type, const short& slot);

	void updateClock(const float& dt);
	void update(const float& dt, const sf::Vector2f& skill_position);
	void render(sf::RenderTarget& target);
};

