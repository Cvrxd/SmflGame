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

	//Functions
	void updateAttack(const float& dt);
	void updateRegularKeyboard(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget& target) override;
};

