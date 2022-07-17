#pragma once
#include <Entities/Enemies/Enemy.h>

enum class MeleEnemyType { MIMIC = 0, BRINGER_OF_DEATH, 
	KNIGHT1, HUNTRESS, MARTIAL_HERO1, MARTIAL_HERO2, NOMAND};

class MeleEnemy : public Enemy
{
	using HealthBar = EnemyGUI::EnemyHealthBar;
	using LevelIcon = EnemyGUI::EnemyLevelIcon;

	//Variables
	MeleEnemyType type;

	//GUI
	HealthBar     healthBar;
	LevelIcon     levelIcon;

	//Init functions
	void initComponents            (sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent  (sf::Texture& texture_sheet)                     override;
	void addAnimations             ()                                               override;

	//Sound fuctions
	void playImpactSounds          (const std::string& sound);
	void playSkillImpactSounds     (const SkillType& type);

	//Update functions
	void updateAttack              (const float& dt)       override;
	void updateMovement            (const float& dt)       override;
	void updateAnimations          (const float& dt)       override;
	void updatePlayerImpact        (const float& dt)       override;

public:
	MeleEnemy(const MeleEnemyType& type, const int& level, const float& x, const float& y, 
		sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept;

	~MeleEnemy();

	//Functions
	void update   (const float& dt, sf::Vector2f mouse_pos_view)              override;
	void render   (sf::RenderTarget& target, sf::Shader* shader = nullptr)    override;
};

