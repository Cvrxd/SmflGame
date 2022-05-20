#pragma once
#include "Enemy.h"

enum class MageEnemyType {DARK_MAGE = 0};

class MageEnemy : public Enemy
{
	MageEnemyType type;
	sf::CircleShape castRange;
	sf::CircleShape innerRange;

	//Init functions
	void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations() override;

	//Other fuctions
	void enemyDead(const float& dt) override;
public:
	MageEnemy(const MageEnemyType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player);
	MageEnemy(MageEnemy&& other);

	~MageEnemy();

	//Functions
	void updateAttack(const float& dt) override;
	void updateMovement(const float& dt) override;
	void updateAnimations(const float& dt) override;
	void updatePlayerImpact(const float& dt) override;
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

