#pragma once

enum Items {SWORD = 0, DAGGER, MAGIK_SWORD, STAFF, RING, NECKLASE, HELMET, ARMOR, GLOVES, BOOTS};

class StatsComponent
{
public:
	//Items
	Items items;

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
	StatsComponent(const int& level);
	~StatsComponent();

	//Functions
	void addItem(const Items& item);

	void gainEXP(const unsigned& exp);
	void gainHP(const int& hp);
	void loseHP(const int& hp);
	void gainArmor(const int& armor);
	void loseArmor(const int& armor);
	void gainMP(const int& mp);
	void loseMP(const int& mp);

	void updateLevel();
	void updateStats(const bool& reset = false);
	void update();
};

