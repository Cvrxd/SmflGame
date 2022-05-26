#pragma once
#include"Player.h"
#include"Gui.h"

class Player;
class GUI::Button;

class PlayerGUI
{
private:
	//Variables
	int* hpPotions;
	int* mpPotions;

	int* coins;
	int* crystals;

	int index = 0;
	float hpOffset = 0.f;
	float mpOffset = 0.f;
	float armorOffset = 0.f;

	sf::Clock skillTimer;

	sf::Font& font;

	//Player variables
	Player& player;
	StatsComponent& statsComponent;

	//Animations
	std::unordered_map<std::string, sf::Sprite> sprites;
	std::unordered_map<std::string, AnimationComponent> animationComponent;

	//All textures
	std::unordered_map<std::string, sf::Texture> textures;

	//Stat bars 
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> bars;

	//Quick slot and inventory bars
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> quickSlotBars;

	//Text and icons
	sf::Texture iconsSheet;
	std::unordered_map<std::string, sf::Text> texts;
	std::unordered_map<std::string, sf::RectangleShape> iconsSprites;

	std::vector<std::pair<SkillType, sf::RectangleShape>>* skillsIcons;

	//Inventory icons
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>> itemsIcons;

	//Functions
	void initVariables();
	void initStatBars();
	void initQuickSlotBars();
	void initTextsIcons();
	void initItems();
	void initAniamtions();
public:
	//Constructor
	PlayerGUI(Player& player, sf::Font& font);
	~PlayerGUI();

	//Functions
	void initBuffSkill();
	void setPotionsCount(int& hp, int& mp);
	void initSkillIcons(std::vector<std::pair<SkillType, sf::RectangleShape>>* skillsIcons);

	void addItem();
	void addSkill(const SkillType& type);

	void updateAnimations(const float& dt);
	void updateBars();
	void updateTextIcons();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

class SkillsLevelingComponent
{
private:
	//Variables
	SkillsComponent& skillsComponent;
	std::vector<std::pair<SkillType, sf::RectangleShape>>& originalSkillsIcons;

	//Core
	std::unordered_map<std::string, GUI::Button*> buttons;
	std::unordered_map<SkillType, sf::RectangleShape> skillsIcons;

	//Functions
	void initVariables();
	void initSkill(const SkillType& type);

public:
	SkillsLevelingComponent(SkillsComponent& skillsComponent, std::vector<std::pair<SkillType, sf::RectangleShape>>& originalSkillsIcons);
	~SkillsLevelingComponent();

	//Functions

	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target);

	friend class SkillsMenu;
};

class SkillsMenu
{
private:
	//Variables
	const int skillsSize;
	int unlockSkillsCount = 0;

	Player& player;
	PlayerGUI& playerGUI;
	SkillsLevelingComponent skillsLevelingComponent;

	sf::Font& font;

	float keyTime;
	float keyTimeMax;

	sf::RectangleShape background;
	std::vector<sf::Text> texts;

	//All textures
	std::unordered_map<std::string, sf::Texture> textures;

	//Stat icons
	std::vector<sf::RectangleShape> statIcons;

	//Skill icons
	std::vector<std::pair<SkillType, sf::RectangleShape>> skillsIcons;

	//Buttons
	std::unordered_map<std::string, GUI::Button*> buttons;
	std::unordered_map<SkillType, GUI::Button*> unclockButtons;

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

	friend class SkillsLevelingMenu;
	friend void PlayerGUI::initBuffSkill();
};
