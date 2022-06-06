#pragma once
#include "Enemy.h"
enum class BossType { NIGHTBORN = 0, FIRE_DEMON, SAMURAI };

class BossEnemy : public Enemy
{
private:
	BossType type;

	EnemyGUI::EnemyHealthBar healthBar;
	EnemyGUI::EnemyLevelIcon levelIcon;

	//Init functions
	void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations() override;

	//Sound fucntions
	void playImpactSounds(const std::string& sound);
	void playSkillImpactSounds(const SkillType& type);

	//Update functions
	void updateAttack(const float& dt) override;
	void updateMovement(const float& dt) override;
	void updateAnimations(const float& dt) override;
	void updatePlayerImpact(const float& dt) override;

public:
	BossEnemy(const BossType& type, const int& level, const float& x, const float& y, 
		sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept;
	
	~BossEnemy();

	//Functions
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

