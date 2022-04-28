#pragma once
#include "Entity.h"
#include <random>
class Player : public Entity
{
private:
	//Variables
	//Initialisation functios
	void initVariables();
	void createAnimationComponent(sf::Texture& texture_sheet) override;
	void addAnimations();
	void initComponents(sf::Texture& texture_sheet);
public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions

	void updateRegularKeyboard(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget& target) override;
};

