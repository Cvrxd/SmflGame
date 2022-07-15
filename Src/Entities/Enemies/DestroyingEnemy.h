#pragma once
#include "Enemy.h"

class Enemy;

enum class DestroyingEnemyType { FIRE_SKULL = 0, FIRE_WORM, DRAGON};

class DestroyingEnemy : public Enemy
{
	using PairSpriteTexture  = std::pair <sf::Sprite, sf::Texture>;
	using HealthBar          = EnemyGUI::EnemyHealthBar;
	using LevelIcon          = EnemyGUI::EnemyLevelIcon;

	//Variables
	std::string          destroySoundKey;

	DestroyingEnemyType  type;
	PairSpriteTexture    destroyingSprite;
	AnimationComponent   destroyingAnimation;

	//GUI
	HealthBar            healthBar;
	LevelIcon            levelIcon;

	//Init functions
	void initComponents              (sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent    (sf::Texture& texture_sheet)                     override;
	void addAnimations               ()                                               override;

	//Sound funtions
	void playImpactSounds       (const std::string& sound);
	void playSkillImpactSounds  (const SkillType& type);

	//Update functions
	void updateAttack          (const float& dt)           override;
	void updateMovement        (const float& dt)           override;
	void updateAnimations      (const float& dt)           override;
	void updatePlayerImpact    (const float& dt)           override;

public:
	DestroyingEnemy (const DestroyingEnemyType& type, const int& level, const float& x, const float& y, 
		sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept;

	~DestroyingEnemy();

	//Functions
	void update  (const float& dt, sf::Vector2f mouse_pos_view)             override;
	void render  (sf::RenderTarget& target, sf::Shader* shader = nullptr)   override;
};

