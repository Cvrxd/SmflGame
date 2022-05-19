#pragma once
#include"StatsComponent.h"
#include"AnimationComponent.h"

class AnimationComponent;
class StatsComponent;

enum SkillType
{
	EMPTY = 0, RED_BLADES, WATER_SPIKE, THUNDER_STRIKE, DARK_BOLT,
	POISON_CLAW, DARK_POSION, BLOOD_SPIKE, FIRE_EXPLOSION, LIGHTNING_STRIKE, HOLY_STRIKE
};

enum Potions{HEALTH = 0, MANA};

class SkillsComponent
{
private:
	//Variables
	sf::Clock skillTimer;

	StatsComponent& statsComponent;

	float time;
	float keyTime;
	float keyTimeMax;

	float potionKeyTime;
	float potionKeyTimeMax;

	//Potions
	std::pair<Potions, int> healthPotions;
	std::pair<Potions, int> manaPotions;

	std::pair<sf::Sprite, sf::Texture> potionSprite;
	AnimationComponent potionAnimation;

	//Skills
	const int skillsSize;
	sf::CircleShape damageArea;

	std::vector<std::pair<SkillType, int>> allSkills;
	std::vector<std::pair<SkillType, int>> playerSkills;

	std::pair<sf::Sprite, sf::Texture> skillsEndingSprite;
	AnimationComponent skillsEndingAnimation;

	//Regular animation
	std::map<SkillType, std::pair<sf::Sprite, sf::Texture>> skillTextures;
	std::map<SkillType, AnimationComponent> skillsAnimations;

	//Skills impact animation
	std::map<SkillType, std::pair<sf::Sprite, sf::Texture>> skillsImpactSprites;
	std::map<SkillType, AnimationComponent> skillsImpactAnimations;

	int currentRender;

	bool playAnimation;
	bool usingPotion;
	bool& usingSkill;

	//Init functions
	void initAllSkills();
	void initAllAnimations();

public:
	SkillsComponent(StatsComponent& statsComponent, bool& isUsingSkill);
	~SkillsComponent();

	//Accessors
	const sf::CircleShape& getDamageArea();
	const bool getKeyTime() const;
	int& getMpPotions();
	int& getHpPotions();

	//Functions
	void addPotion(const Potions& potion_type);
	void usePotion(const Potions& potion_type);

	void useSkill(const SkillType& skill_type);
	void addSkill(const SkillType& skill_type, const short& slot);

	void updateClock(const float& dt);
	void update(const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position);
	void render(sf::RenderTarget& target);
};

