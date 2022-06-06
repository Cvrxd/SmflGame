#pragma once
#include"StatsComponent.h"
#include"AnimationComponent.h"

class AnimationComponent;
class StatsComponent;

enum class SkillType
{
	EMPTY = 0, THUNDER_STRIKE, DARK_BOLT,
	POISON_CLAW, DARK_POSION, BLOOD_SPIKE, FIRE_EXPLOSION, LIGHTNING_STRIKE, HOLY_STRIKE, BUFF, POTION
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

	float potionKeyTime;
	float potionKeyTimeMax;

	//Buff
	float buffDuration;
	float buffCooldown;

	int buffLevel = 1;
	int buffMaxLevel = 5;
	float buffCritRate = 5.f;

	//Sounds
	std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>> sounds;

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
	void initSounds();
	void initAllSkills();
	void initAllAnimations();

	//Update functions
	void updateClock(const float& dt);

	//Core functions
	void useSkill(const SkillType& skill_type);
	void playSkillSound(const SkillType& type);

public:
	SkillsComponent(StatsComponent& statsComponent, bool& isUsingSkill, SkillType& usingSkillType, int& currentSkillDamage, bool& isBuffed) noexcept;
	~SkillsComponent();

	//Accessors
	const int& getBuffMaxLevel() const;
	const int& getBuffLevel() const;

	const std::vector<std::pair<SkillType, int>>& getPlayerSkills();
	const sf::CircleShape& getDamageArea();
	const bool getKeyTime() const;
	const bool getBuffKeyTime() const;
	int& getMpPotions();
	int& getHpPotions();

	//Functions
	void addPotion(const Potions& potion_type);
	void usePotion(const Potions& potion_type);

	void addSkill(const SkillType& skill_type, const short& slot);
	void upgradeSkill(const SkillType& skill_type);

	void updatePlayerBuff(const float& dt, const sf::Vector2f& player_position);
	void update(const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position);
	void render(sf::RenderTarget& target);
};

