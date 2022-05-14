#pragma once
#include"Player.h"
#include"Gui.h"

class Player;
class GUI::Button;

class PlayerGUI
{
private:
	//Variables
	sf::Clock skillTimer;

	Player& player;

	sf::Font& font;

	//All textures
	std::map<std::string, sf::Texture> textures;

	//Stat bars 
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> bars;

	//Quick slot and inventory bars
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> quickSlotBars;

	//Text and icons
	sf::Texture iconsSheet;
	std::map<std::string, sf::Text> texts;
	std::map<std::string, sf::RectangleShape> iconsSprites;

	int index = 0;
	std::vector<std::pair<SkillType, sf::RectangleShape>>* skillsIcons;

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
	void initSkillIcons(std::vector<std::pair<SkillType, sf::RectangleShape>>* skillsIcons);

	void addItem();
	void addSkill(const SkillType& type);

	void updateBars();
	void updateTextIcons();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

class SkillsMenu
{
private:
	//Variables
	float keyTime;
	float keyTimeMax;

	Player& player;
	PlayerGUI& playerGUI;
	sf::Font& font;

	sf::RectangleShape background;
	std::vector<sf::Text> texts;

	//All textures
	std::map<std::string, sf::Texture> textures;

	//Stat icons
	std::vector<sf::RectangleShape> statIcons;

	//Skill icons
	std::vector<std::pair<SkillType, sf::RectangleShape>> skillsIcons;

	//Buttons
	std::map<std::string, GUI::Button*> buttons;
	std::map<SkillType, GUI::Button*> unclockButtons;

	//Init functions
	void initButtons();
	void initBackground(const float& x, const float& y);
	void initTexts();
	void initSkillIcons();

	//Other functions
	void updateKeyTime(const float& dt);
public:
	//Constructor
	SkillsMenu(Player& player, PlayerGUI& playerGUI, sf::Font& font, const float& x, const float& y);
	~SkillsMenu();

	//Other functions
	const bool getKeyTime() const;

	void unlockSkill(const SkillType& type);

	void updateText();

	void updateButtons(sf::Vector2i& mousePosWindow);
	void renderButtons(sf::RenderTarget& target);

	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target);
};