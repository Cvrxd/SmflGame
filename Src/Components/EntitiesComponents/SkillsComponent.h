#pragma once
#include <Components/EntitiesComponents/StatsComponent.h>

#include <Components/GeneralComponents/PopUpTextComponent.h>
#include <Components/GeneralComponents/AnimationComponent.h>
#include <Components/GeneralComponents/ISoundsPlayer.h>


class AnimationComponent;
class StatsComponent;
class PopUpTextComponent;

enum class SkillType
{
	EMPTY = 0, THUNDER_STRIKE, DARK_BOLT,
	POISON_CLAW, DARK_POSION, BLOOD_SPIKE, FIRE_EXPLOSION, LIGHTNING_STRIKE, HOLY_STRIKE, BUFF, POTION
};

enum Potions{HEALTH = 0, MANA};

class SkillsComponent : public ISoundsPlayer<SkillType>
{
private:
	using PopUpKeysMap          = std::unordered_map<SkillType, std::string>;
    using PotionsPopUpKeys      = std::pair<Potions, std::string>;
    using VectorSkillsIndex     = std::vector<std::pair<SkillType, int>>;
    using PairSpriteTexture     = std::pair<sf::Sprite, sf::Texture>;
	using PotionsCount          = std::pair<Potions, int>;
	using MapSkillsTextures     = std::unordered_map<SkillType, std::pair<sf::Sprite, sf::Texture>>;
	using MapSkillsAnimations   = std::unordered_map<SkillType, AnimationComponent>;
	using SoundsMap             = std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>>;

	//Variables
	sf::Clock skillTimer;
	sf::Clock buffTimer;
	sf::Clock popUpTextTimer;

	StatsComponent& statsComponent;

	float  time;

	float  keyTime;
	float  keyTimeMax;

	float  potionKeyTime;
	float  potionKeyTimeMax;

	//Buff
	float  buffDuration;
	float  buffCooldown;

	int	   buffLevel      = 1;
	int	   buffMaxLevel   = 5;

	float  buffCritRate   = 5.f;
	float  buffMissChance = 5.f;

	//Sounds
	SoundsMap           sounds;

	//Potions
	PotionsCount        healthPotions;
	PotionsCount        manaPotions;

	PairSpriteTexture   potionSprite;
	AnimationComponent  potionAnimation;

	PotionsPopUpKeys	hpPopUpKey;
	PotionsPopUpKeys	mpPopUpKey;

	//PopUpText key
	PopUpKeysMap        popUpKeysMap;
	std::string         popUpTextKey;


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

	//Pop up text component
	PopUpTextComponent  popUpTextComponent;

	//Booleans
	bool   playAnimation;
	bool   usingPotion;
	bool   usingBuff;
	bool   showPopUpText;

	bool&  castingSpell;
	bool&  usingSkill;
	bool&  isBuffed;
	int&   currentSkillDamage;

	int    currentRender;

	SkillType& currentSkillType;

	//Init functions
	void initSounds         ();
	void initAllSkills      ();
	void initAllAnimations  ();
	void initPopUpText      ();

	//Update functions
	void updateClock     (const float& dt);
	void updatePopUpText (const std::string& key);

	//Render functions
	void renderPopUpText (sf::RenderTarget& target, const sf::Vector2f& player_position);
	
	//Core functions
	void useSkill        (const SkillType& skill_type);
	void playSkillSound  (const SkillType& skill_type);
public:
	SkillsComponent  (StatsComponent& statsComponent, const sf::Font& font, bool& isUsingSkill, SkillType& usingSkillType, int& currentSkillDamage, bool& isBuffed, bool& castingSpell) noexcept;
	~SkillsComponent ();

	//Accessors
	const std::vector<std::pair<SkillType, int>>& getPlayerSkills();

	const int&                getBuffMaxLevel  ()    const;
	const int&                getBuffLevel     ()    const;
	const sf::CircleShape&    getDamageArea    ();
	const bool                getKeyTime()           const;
	const bool                getBuffKeyTime   ()    const;
	int&                      getMpPotions     ();
	int&                      getHpPotions     ();

	//Functions
	void addPotion         (const Potions& potion_type);
	void usePotion         (const Potions& potion_type);

	void addSkill          (const SkillType& skill_type, const short& slot);
	void upgradeSkill      (const SkillType& skill_type);

	void updatePlayerBuff  (const float& dt, const sf::Vector2f& player_position);
	void update            (const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position);
	void render            (sf::RenderTarget& target, const sf::Vector2f& player_position);
};

