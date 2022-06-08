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
	using VectorSkillsIndex     = std::vector<std::pair<SkillType, int>>;
	using PairSpriteTexture     = std::pair<sf::Sprite, sf::Texture>;
	using PotionsCount          = std::pair<Potions, int>;
	using MapSkillsTextures     = std::unordered_map<SkillType, std::pair<sf::Sprite, sf::Texture>>;
	using MapSkillsAnimations   = std::unordered_map<SkillType, AnimationComponent>;

	//Variables
	sf::Clock skillTimer;
	sf::Clock buffTimer;
	
	StatsComponent& statsComponent;

	float  time;

	float  keyTime;
	float  keyTimeMax;

	float  potionKeyTime;
	float  potionKeyTimeMax;

	//Buff
	float  buffDuration;
	float  buffCooldown;

	int	   buffLevel = 1;
	int	   buffMaxLevel = 5;
	float  buffCritRate = 5.f;

	//Sounds
	std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>> sounds;

	//Potions
	PotionsCount        healthPotions;
	PotionsCount        manaPotions;

	PairSpriteTexture   potionSprite;
	AnimationComponent  potionAnimation;

	//Skills
	const int           skillsSize;
	sf::CircleShape	    damageArea;

	VectorSkillsIndex   allSkills;
	VectorSkillsIndex   playerSkills;

	PairSpriteTexture   skillsEndingSprite;
	AnimationComponent  skillsEndingAnimation;

	//Regular animation
	MapSkillsTextures   skillTextures;
	MapSkillsAnimations skillsAnimations;

	//Booleans
	bool   playAnimation;
	bool   usingPotion;
	bool   usingBuff;

	bool&  usingSkill;
	bool&  isBuffed;
	int&   currentSkillDamage;

	int    currentRender;

	SkillType& currentSkillType;

	//Init functions
	void initSounds         ();
	void initAllSkills      ();
	void initAllAnimations  ();

	//Update functions
	void updateClock     (const float& dt);

	//Core functions
	void useSkill        (const SkillType& skill_type);
	void playSkillSound  (const SkillType& type);

public:
	SkillsComponent  (StatsComponent& statsComponent, bool& isUsingSkill, SkillType& usingSkillType, int& currentSkillDamage, bool& isBuffed) noexcept;
	~SkillsComponent ();

	//Accessors
	const std::vector<std::pair<SkillType, int>>& getPlayerSkills();

	const int&              getBuffMaxLevel  ()    const;
	const int&              getBuffLevel     ()    const;
	const sf::CircleShape&  getDamageArea    ();
	const bool              getKeyTime()           const;
	const bool              getBuffKeyTime   ()    const;
	int&                    getMpPotions     ();
	int&                    getHpPotions     ();

	//Functions
	void addPotion         (const Potions& potion_type);
	void usePotion         (const Potions& potion_type);

	void addSkill          (const SkillType& skill_type, const short& slot);
	void upgradeSkill      (const SkillType& skill_type);

	void updatePlayerBuff  (const float& dt, const sf::Vector2f& player_position);
	void update            (const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position);
	void render            (sf::RenderTarget& target);
};

