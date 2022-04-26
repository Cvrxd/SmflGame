#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	//Variables

	//Initialisation functios
	void initVariables();
	void initComponents();
public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	void update(const float& dt) override;
};

