#pragma once
#include"Player.h"
#include"Gui.h"

class Player;
class GUI::Button;

struct GuiSoundsBox
{
	std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> sounds;

	GuiSoundsBox()
	{
		this->sounds["UPGRADE_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_upgrade.wav");
		this->sounds["UPGRADE_SKILL"].second.setBuffer(this->sounds["UPGRADE_SKILL"].first);
		this->sounds["UPGRADE_SKILL"].second.setVolume(10.f);

		this->sounds["UNLOCK_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_unlock.wav");
		this->sounds["UNLOCK_SKILL"].second.setBuffer(this->sounds["UNLOCK_SKILL"].first);
		this->sounds["UNLOCK_SKILL"].second.setVolume(10.f);

		this->sounds["CLICK"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/click.wav");
		this->sounds["CLICK"].second.setBuffer(this->sounds["CLICK"].first);
		this->sounds["CLICK"].second.setVolume(10.f);
	}
};

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
	SkillsComponent* skillComponent;

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

	//Functions
	void initVariables();
	void initStatBars();
	void initQuickSlotBars();
	void initTextsIcons();
	void initAniamtions();
public:
	//Constructor
	PlayerGUI(Player& player, sf::Font& font) noexcept;
	~PlayerGUI();

	//Accessors
	sf::Texture& getCrystalsTexture();
	sf::Texture& getCoinsTexture();

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

	void renderQuickSlotBars(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	void skillsMenUpdate(const float& dt);
	void itemsMenuUpdate(const float& dt);
	
	friend class SkillsLevelingComponent;
	friend class SkillsMenu;
};

class SkillsLevelingComponent
{
private:
	//Variables
	SkillsComponent& skillsComponent;
	PlayerGUI& playerGUI;

	sf::Font& font;

	//Pointers to other icons
	std::vector<std::pair<SkillType, sf::RectangleShape>>* originalSkillsIcons;
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>>* quickSlotBars;

	//Pointer from skills component 
	const std::vector<std::pair<SkillType, int>>* playerSkills;

	//Core
	int unlockSkillsCount = 0;
	short unsigned skillMaxLevel = 5;

	float offsetY = 30.f;
	float keyTime = 0.f;
	float keyTimeMax = 20.f;

	//Crystal animations and sprites
	std::unordered_map<SkillType, sf::Sprite> crystalsSprites;
	std::unordered_map<SkillType, AnimationComponent> crystalsAnimations;

	//Menu GUI
	std::unordered_map<SkillType, int> skillLevels;
	std::unordered_map<SkillType, GUI::Button*> buttons;
	std::unordered_map<SkillType, sf::RectangleShape> skillsIcons;
	std::unordered_map<SkillType, sf::Text> texts;

	//Sounds
	GuiSoundsBox& guiSounds;
	
	//Init functions
	void initVariables(std::vector<std::pair<SkillType, sf::RectangleShape>>& originalSkillsIcons, 
		std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>>& quickSlotBars);

	void initSkill(const SkillType& type);

	//Other functions
	void updateKeyTime(const float& dt);
	void updateSkillColor(const SkillType& type, const sf::Color& color);
	void playSound(const std::string& sound);

public:
	SkillsLevelingComponent(SkillsComponent& skillsComponent, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds) noexcept;
	~SkillsLevelingComponent();

	//Functions
	void upgradeSkill(const SkillType& type);

	void updateButtons(sf::Vector2i& mousePosWindow, const float& dt);
	void updateTexts();
	void updateAnimations(const float& dt);

	void update(sf::Vector2i& mousePosWindow, const float& dt);

	void render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);

	friend class SkillsMenu;
	friend class PlayerGUI;
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

	//Sounds
	GuiSoundsBox& guiSounds;

	//Init functions
	void initButtons();
	void initBackground(const float& x, const float& y);
	void initTexts();
	void initSkillIcons();

	//Other functions
	void updateKeyTime(const float& dt);

	//Sound
	void playSound(const std::string& sound);
public:
	//Constructor
	SkillsMenu(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds,const float& x, const float& y) noexcept;
	~SkillsMenu();

	//Other functions
	const bool getKeyTime() const;

	void unlockSkill(const SkillType& type);

	void updateText();

	void updateButtons(sf::Vector2i& mousePosWindow);
	void renderButtons(sf::RenderTarget& target);

	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);

	friend class SkillsLevelingMenu;
	friend void PlayerGUI::initBuffSkill();
};

class ItemsMune
{
private:
	//Variables
	PlayerGUI& playerGui;
	Player& player;
	StatsComponent* playerStats;

	GuiSoundsBox& guiSounds;

	sf::Font& font;

	//Core
	sf::RectangleShape background;

	int maxLevel = 5;
	int unlockedItemsCount = 0;
	float offsetX;
	float offsetY;

	//Text
	std::pair<sf::Text, sf::Text> mainText;
	std::unordered_map<Items, sf::Text> upgradeTexts;
	std::unordered_map<Items, sf::Text>	statsTexts;

	//Buttons
	std::unordered_map<Items, GUI::Button*> unclockButtons;
	std::unordered_map<Items, GUI::Button*> upgradeButtons;

	//Coins animations and sprites
	std::unordered_map<Items, sf::Sprite> coinsSprites;
	std::unordered_map<Items, AnimationComponent> coinsAnimations;

	//Items
	std::unordered_map<Items, sf::RectangleShape> itemsIcons;
	std::unordered_map<Items, sf::RectangleShape> upgradeItemsIcons;
	std::unordered_map<Items, int> itemsLvl;

	//Textures
	std::unordered_map<std::string, sf::Texture> textures;

	//Key time
	float keyTime;
	float keyTimeMax;

	//Init functions
	void initVariables();
	void initTextures();
	void initBackground(const float& x, const float& y);
	void initItemsIcons();
	void initTexts();
	void initButtons();
	void initAnimations();
	void initOffsets();

	//Update functions
	void updateItemGrade(const Items& item, const sf::Color& color);
	void updateKeyTime(const float& dt);
	void updateText();
	void updateAnimations(const float& dt);

	void unlockItem(const Items& item);
	void upgradeItem(const Items& item);

	//Render functions
	void renderIcons(sf::RenderTarget& target);

	//Sound
	void playSound(const std::string& sound);

public:
	ItemsMune(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& sounds, const float& x, const float& y) noexcept;
	~ItemsMune();

	//Finctions
	void renderText(sf::RenderTarget& target);

	void updateButtons(sf::Vector2i& mousePosWindow);
	void renderButtons(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);

	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);
};