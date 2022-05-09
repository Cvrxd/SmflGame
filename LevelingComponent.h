#pragma once

class LevelingComponent
{
public:
	//Leveling
	int level;
	unsigned exp;
	unsigned expNext;
	unsigned statsPoints;
	unsigned skillPoints;

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

	void gainEXP(const unsigned& exp);
	void loseHP(const int& hp);
	void gainHP(const int& hp);

	void updateLevel();
	void updateStats(const bool& reset = false);
	void update();
};

