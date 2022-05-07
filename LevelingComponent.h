#pragma once

class LevelingComponent
{
public:
	//Leveling
	int level;
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

	int damagePhysical;
	int damageMagical;

	//Constructor
	LevelingComponent(const int& level);
	~LevelingComponent();

	//Functions
	std::string debugPrint();

	void gainEXP(const unsigned exp);

	void updateLevel();
	void updateStats(const bool& reset = false);
	void update();
};

