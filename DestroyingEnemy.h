#pragma once
#include "Enemy.h"

class Enemy;

enum class DestroyingEnemyType { FIRE_SKULL = 0};

class DestroyingEnemy : public Enemy
{
	DestroyingEnemyType type;

	std::pair<sf::Sprite, sf::Texture> destroyingSprite;
	AnimationComponent destroyingAnimation;

	//Init functions
	void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations() override;

	//Other fuctions
	void enemyDead(const float& dt) override;
public:
	DestroyingEnemy(const DestroyingEnemyType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player);
	DestroyingEnemy(DestroyingEnemy&& other);

	~DestroyingEnemy();

	//Functions
	void updateAttack(const float& dt) override;
	void updateMovement(const float& dt) override;
	void updateAnimations(const float& dt) override;
	void updatePlayerImpact(const float& dt) override;
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

