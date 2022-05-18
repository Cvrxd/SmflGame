#pragma once
#include "Enemy.h"
enum BossType { NIGHTBORN = 0 };

class BossEnemy : public Enemy
{
private:
	BossType type;
	std::function<void()> setOriginLeft;
	std::function<void()> setOriginRight;

	void initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite) override;
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations() override;
public:
	BossEnemy(const BossType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player);
	~BossEnemy();

	//Functions
	void updateAttack(const float& dt) override;
	void updateMovement(const float& dt) override;
	void updateAnimations(const float& dt) override;
	void updatePlayerImpact() override;
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

