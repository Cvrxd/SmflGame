#pragma once
#include <Entities/Enemies/Enemy.h>

class Enemy;

enum class MageEnemyType {DARK_MAGE = 0, FIRE_MAGE, WIZZARD, NECROMANCER};

class MageEnemy : public Enemy
{
	using HealthBar = EnemyGUI::EnemyHealthBar;
	using LevelIcon = EnemyGUI::EnemyLevelIcon;

	//Core variables
	MageEnemyType type;

	std::string   spellCastSoundKey;

	float castR;
	float ineerR;

	float offsetY;
	float offsetX;

	sf::CircleShape castRange;
	sf::CircleShape innerRange;

	//GUI
	HealthBar healthBar;
	LevelIcon levelIcon;

	//Init functions
	void initComponents              (sf::Texture& texture_sheet, sf::Sprite& sprite)  override;
	void createAnimationComponent    (sf::Texture& texture_sheet)                      override;
	void addAnimations               ()                                                override;

	//Sound functions
	void playImpactSounds            (const std::string& sound);
	void playSkillImpactSounds       (const SkillType& type);

	//Update functions
	void updateAttack                (const float& dt)                              override;
	void updateMovement              (const float& dt)                              override;
	void updateAnimations            (const float& dt)                              override;
	void updatePlayerImpact          (const float& dt)                              override;

public:
	MageEnemy (const MageEnemyType& type, const int& level, const float& x, const float& y, 
		sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept;

	~MageEnemy();

	//Functions
	void update  (const float& dt, sf::Vector2f mouse_pos_view)            override;
	void render  (sf::RenderTarget& target, sf::Shader* shader = nullptr)  override;
};

