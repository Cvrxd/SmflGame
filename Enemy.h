#pragma once
#include "Entity.h"
#include "Player.h"
#include "EnemyGUI.h"

class Entity;
class Player;
class AnimationComponent;
class StatsComponent;
class EnemyHealthBar;

class Enemy : public Entity
{
protected:
	using PairTextureSprite = std::pair<sf::Texture, sf::Sprite>;
	using MapSprites		= std::unordered_map<SkillType, std::pair<sf::Sprite, sf::Texture>>;
	using MapAnimations		= std::unordered_map < SkillType, AnimationComponent>;
	using MapOffsets		= std::unordered_map<SkillType, int>;

	//Variables
	//Resistance
	SkillType skillReistance = SkillType::EMPTY;

	bool physicalResistance	= false;
	bool magicalResistance	= false;

	//Boleans for animations
	bool isAttaking			= false;
	bool isTakingDamage		= false;

	bool critImpact			= false;
	bool hitImpact			= false;
	bool skillImpact		= false;
	bool isDead				= false;

	//Timers
	sf::Clock attackTimer;

	float	attackColdown;
	int		attackCount;
	int		attackCountMAX;

	//Sounds
	EnemySoundBox&		soundBox;

	//Player Hit impact
	PairTextureSprite	takeHitSprite;
	AnimationComponent	takeHitAnimation;

	PairTextureSprite	critHitSprite;
	AnimationComponent	critHitAnimation;

	//Player Skills impact
	const SkillType*	playerUsingSkill;
	const int*			playerUsingSkillDmg;

	MapSprites			skillsImpactSprites;
	MapAnimations		skillsImpactAnimations;
	MapOffsets			offsets;

	//Set Origin functions
	std::function<void()>	setOriginLeft;
	std::function<void()>	setOriginRight;

	//Components
	AnimationComponent		animationComponent;
	StatsComponent			statsComponent;

	//Player and this texture sheet
	Player*			player;
	sf::Texture*	textureSheet;

	//init functions
	virtual void initImpactAnimations();
	virtual void initSkillsImpactTextures();
	virtual void initStats();
	virtual void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) = 0;
	virtual void createAnimationComponent(sf::Texture& texture_sheet)			= 0;
	virtual void addAnimations() = 0;

	//Functions
	virtual void updatePlayerImpact(const float& dt)	= 0;
	virtual void updateAttack(const float& dt)			= 0;
	virtual void updateMovement(const float& dt)		= 0;
	virtual void updateAnimations(const float& dt)		= 0;

public:
	Enemy(const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept;
	virtual ~Enemy();

	//Accessors
	const bool& dead();
};

