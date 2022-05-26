#pragma once
#include"StatsComponent.h"
#include"AnimationComponent.h"

class AnimationComponent;
class StatsComponent;

enum class SkillType
{
	EMPTY = 0, THUNDER_STRIKE, DARK_BOLT,
	POISON_CLAW, DARK_POSION, BLOOD_SPIKE, FIRE_EXPLOSION, LIGHTNING_STRIKE, HOLY_STRIKE, BUFF
};

enum Potions{HEALTH = 0, MANA};

class SkillsComponent
{
private:
	//Variables
	sf::Clock skillTimer;
	sf::Clock buffTimer;

	StatsComponent& statsComponent;

	float time;

	float keyTime;
	float keyTimeMax;
	float buffKeyTime;

	float potionKeyTime;
	float potionKeyTimeMax;

	float buffDuration;

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
	std::unordered_map<SkillType, std::pair<sf::Sprite, sf::Texture>> skillTextures;
	std::unordered_map<SkillType, AnimationComponent> skillsAnimations;

	bool playAnimation;
	bool usingPotion;
	bool usingBuff;

	bool& usingSkill;
	bool& isBuffed;

	int currentRender;

	int& currentSkillDamage;
	SkillType& currentSkillType;

	//Init functions
	void initAllSkills();
	void initAllAnimations();
public:
	SkillsComponent(StatsComponent& statsComponent, bool& isUsingSkill, SkillType& usingSkillType, int& currentSkillDamage, bool& isBuffed);
	~SkillsComponent();

	//Accessors
	const sf::CircleShape& getDamageArea();
	const bool getKeyTime() const;
	const bool getBuffKeyTime() const;
	int& getMpPotions();
	int& getHpPotions();

	//Functions
	void addPotion(const Potions& potion_type);
	void usePotion(const Potions& potion_type);

	void useSkill(const SkillType& skill_type);
	void addSkill(const SkillType& skill_type, const short& slot);
	void upgradeSkill(const SkillType& skill_type);

	void updateClock(const float& dt);
	void updatePlayerBuff(const float& dt, const sf::Vector2f& player_position);
	void update(const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position);
	void render(sf::RenderTarget& target);
};

