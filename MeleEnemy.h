#pragma once
#include "Enemy.h"

enum class MeleEnemyType { MIMIC = 0, BRINGER_OF_DEATH, 
	KNIGHT1, HUNTRESS, MARTIAL_HERO1, MARTIAL_HERO2, MARTIAL_HERO3};

class MeleEnemy : public Enemy
{
	MeleEnemyType type;

	EnemyGUI::EnemyHealthBar healthBar;
	EnemyGUI::EnemyLevelIcon levelIcon;

	//Init functions
	void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations() override;

	//Other fuctions
	void enemyDead(const float& dt) override;

	//Sound fuctions
	void playImpactSounds(const std::string& sound);
	void playSkillImpactSounds(const SkillType& type);

public:
	MeleEnemy(const MeleEnemyType& type, const int& level, const float& x, const float& y, 
		sf::Texture& texture_sheet, Player* player, EnemiesSounds& sounds);

	~MeleEnemy();

	//Functions
	void updateAttack(const float& dt) override;
	void updateMovement(const float& dt) override;
	void updateAnimations(const float& dt) override;
	void updatePlayerImpact(const float& dt) override;
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

