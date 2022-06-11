#pragma once

enum class Items {SWORD = 0, STAFF, RING, NECKLASE, HELMET, ARMOR, GLOVES, BOOTS, EMPTY_ITEM};

class StatsComponent
{
public:
	//Items
	Items items;

	//Leveling
	unsigned exp;
	unsigned expNext;
	unsigned statsPoints;
	unsigned skillPoints;

	int level;
	int coins;
	int crystals;

	//Stats
	int hp;
	int hpMAX;
	int mp;
	int mpMAX;
	int armor;
	int armorMAX;

	int damagePhysical;
	int damageMagical;
	int currentSkillDamage;

	float critRate;
	float missChance;

	//Constructor
	StatsComponent    (const int& level) noexcept;
	~StatsComponent   ();

	//Functions
	void addItem      (const Items& item);
	void upgradeItem  (const Items& item, const int& level);

	void gainEXP      (const unsigned& exp);
	void gainHP       (const int& hp);
	void loseHP       (const int& hp);
	void gainArmor    (const int& armor);
	void loseArmor    (const int& armor);
	void gainMP       (const int& mp);
	void loseMP       (const int& mp);

	void gainCrystals   (const int& crystals);
	void loseCrystals   (const int& crystals);
	void gainCoins      (const int& coins);
	void loseCoins      (const int& coins);

	void updateStats    (const bool& reset = false);
	void updateLevel    ();
	void update         ();
};

