#pragma once
#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	//Variables
	bool isAttacking = false;
	
	//Initialisation functios
	void initVariables();
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations();
	void initComponents(sf::Texture& texture_sheet);
public:
	Player(const float& x, const float& y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Accessors
	LevelingComponent* getLVLcomponent();

	//Functions
	void gainEXP(const unsigned& exp);
	void loseHP(const int& hp);
	void gainHP(const int& hp);

	void updateAttack(const float& dt);
	void updateRegularKeyboard(const float& dt, sf::Vector2f mouse_pos_view);
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

