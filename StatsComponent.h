#pragma once

class StatsComponent
{
public:
	struct Items
	{
		bool sword = false;
		bool staff = false;
		bool ring = false;
		bool necklase = false;
		bool helmet = false;
		bool armor = false;
		bool gloves = false;
		bool boots = false;
	};

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
	std::string debugPrint();
	void addItem(const short& item);

	void gainEXP(const unsigned& exp);
	void loseHP(const int& hp);
	void gainHP(const int& hp);

	void updateLevel();
	void updateStats(const bool& reset = false);
	void update();
};

