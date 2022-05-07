#pragma once

class LevelingComponent
{
public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned statsPoints;

	//Stats
	int hp;
	int hpMAX;
	int magicka;
	int magickaMAX;
	int armor;
	int armorMAX;

	int accurancy;
	int luck;
	int damagePhysical;
	int damageMagical;

	//Constructor
	LevelingComponent(unsigned level);
	~LevelingComponent();

	//Functions
	std::string debugPrint();

	void gainEXP(const unsigned exp);

	void updateLevel();
	void updateStats(const bool& reset = false);
	void update();
};

