#pragma once
#include"Player.h"

class Player;

class PlayerGUI
{
private:
	struct LevelingMenu
	{
		
	};

	//Variables
	Player& player;
	sf::Font& font;

	std::map<std::string, sf::Texture> textures;
	//Stat bars 
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> bars;

	//Quick slot and inventory bars
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> quickSlotBars;

	//Text and icons
	sf::Texture iconsSheet;
	std::map<std::string, sf::Text> texts;
	std::map<std::string, sf::RectangleShape> iconsSprites;

	//Inventory icons
	
	std::map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>> inventoryIcons;

	//Functions
	void initStatBars();
	void initQuickSlotBars();
	void initTextsIcons();
	void initItems();
public:
	//Constructor
	PlayerGUI(Player& player, sf::Font& font);
	~PlayerGUI();

	//Functions
	//GUI
	void addItem();
	void addSkill();

	void updateBars();
	void updateTextIcons();

	void update(const float& dt);
	void render(sf::RenderTarget& target);

	//Skills Menu
	void updateSkillsMenu(const float& dt);
	void renderSkillsMenu(sf::RenderTarget& traget);
};

