#pragma once
#include"Player.h"
#include"Gui.h"

class Player;
class GUI::Button;
struct GuiSoundsBox;

class PlayerGUI
{
private:
	using MapSprites			= std::unordered_map<std::string, sf::Sprite>;
	using MapAnimations			= std::unordered_map<std::string, AnimationComponent>;
	using MapTextures			= std::unordered_map<std::string, sf::Texture>;
	using VectorPairShapes		= std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>>;
	using VectorText			= std::unordered_map<std::string, sf::Text>;
	using MapShapes				= std::unordered_map<std::string, sf::RectangleShape>;
	using vectorSkillTypeShape	= std::vector<std::pair<SkillType, sf::RectangleShape>>;

	//Variables
	int*  hpPotions;
	int*  mpPotions;

	int*  coins;
	int*  crystals;

	int   index			= 0;
	float hpOffset		= 0.f;
	float mpOffset		= 0.f;
	float armorOffset	= 0.f;

	sf::Clock skillTimer;
	sf::Font& font;

	//Player variables
	Player&          player;
	StatsComponent&  statsComponent;
	SkillsComponent* skillComponent;

	//Animations
	MapSprites		sprites;
	MapAnimations	animationComponent;

	//All textures
	MapTextures		textures;

	//Bars 
	VectorPairShapes bars;
	VectorPairShapes quickSlotBars;

	//Text and icons
	sf::Texture		iconsSheet;
	VectorText		texts;
	MapShapes		iconsShapes;

	//Skill icons pointer
	vectorSkillTypeShape* skillsIcons;

	//Init functions
	void initVariables();
	void initStatBars();
	void initQuickSlotBars();
	void initTextsIcons();
	void initAniamtions();

	//Update functions
	void updateAnimations(const float& dt);
	void updateBars();
	void updateTextIcons();

	//Render functions
	void renderQuickSlotBars(sf::RenderTarget& target);

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
	void initSkillIcons(vectorSkillTypeShape* skillsIcons);

	void addSkill(const SkillType& type);
	void upgradePlayerBuff(const int& level);

	void update(const float& dt);
	void render(sf::RenderTarget& target);

	void skillsMenUpdate(const float& dt);
	void itemsMenuUpdate(const float& dt);
	
	friend class SkillsLevelingComponent;
	friend class SkillsMenu;
};

class SkillsLevelingComponent
{
private:
	using VectorSkillIcons		= std::vector<std::pair<SkillType, sf::RectangleShape>>;
	using VectorQuickSlotBars	= std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>>;
	using MapSprites			= std::unordered_map<SkillType, sf::Sprite>;
	using MapAnimations			= std::unordered_map<SkillType, AnimationComponent>;
	using MapSkillLevels		= std::unordered_map<SkillType, int>;
	using VectorLevelSkills		= const std::vector<std::pair<SkillType, int>>;
	using MapButtons			= std::unordered_map<SkillType, std::unique_ptr<GUI::Button>>;
	using MapSkillShapes		= std::unordered_map<SkillType, sf::RectangleShape>;
	using MapText				= std::unordered_map<SkillType, sf::Text>;

	//Variables
	//References
	SkillsComponent& skillsComponent;
	PlayerGUI&       playerGUI;
	sf::Font&        font;

	//Pointers to other icons
	VectorSkillIcons*		originalSkillsIcons;
	VectorQuickSlotBars*	quickSlotBars;

	//Pointer from skills component 
	VectorLevelSkills*		playerSkills;

	//Core
	int				unlockSkillsCount = 0;
	short unsigned	skillMaxLevel = 5;

	float			offsetY	 = 30.f;
	float			keyTime	 = 0.f;
	float			keyTimeMax = 20.f;

	//Crystal animations and sprites
	MapSprites		crystalsSprites;
	MapAnimations	crystalsAnimations;

	//Menu GUI
	MapSkillLevels	skillLevels;
	MapButtons		buttons;
	MapSkillShapes  skillsIcons;
	MapText			texts;

	//Sounds
	GuiSoundsBox&	guiSounds;
	
	//Init functions
	void initVariables(VectorSkillIcons& originalSkillsIcons, VectorQuickSlotBars& quickSlotBars);

	void initSkill(const SkillType& type);

	//Update functions
	void updateButtons(sf::Vector2i& mousePosWindow, const float& dt);
	void updateTexts();
	void updateAnimations(const float& dt);
	void updateKeyTime(const float& dt);
	void updateSkillColor(const SkillType& type, const sf::Color& color);

	//Sound functions
	void playSound(const std::string& sound);

public:
	SkillsLevelingComponent(SkillsComponent& skillsComponent, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds) noexcept;
	~SkillsLevelingComponent();

	//Functions
	void upgradeSkill(const SkillType& type);

	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);

	friend class SkillsMenu;
	friend class PlayerGUI;
};

class SkillsMenu
{
private:
	using VectorShapes				= std::vector<sf::RectangleShape>;
	using MapTextures				= std::unordered_map<std::string, sf::Texture>;
	using VectorText				= std::vector<sf::Text>;
	using VectorSkillIconsShapes	= std::vector<std::pair<SkillType, sf::RectangleShape>>;
	using MapButtons				= std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;
	using MapUnlockButtons			= std::unordered_map<SkillType, std::unique_ptr<GUI::Button>>;

	//Variables
	//References
	Player&		player;
	PlayerGUI&	playerGUI;
	sf::Font&	font;

	//Sounds
	GuiSoundsBox& guiSounds;

	//Core
	const int	skillsSize;
	int			unlockSkillsCount = 0;

	float		keyTime;
	float		keyTimeMax;

	sf::RectangleShape		background;
	SkillsLevelingComponent skillsLevelingComponent;

	//Texts
	VectorText				texts;

	//All textures
	MapTextures				textures;

	//Stat icons
	VectorShapes			statIcons;

	//Skill icons
	VectorSkillIconsShapes	skillsIcons;

	//Buttons
	MapButtons				buttons;
	MapUnlockButtons		unclockButtons;

	//Init functions
	void initButtons();
	void initBackground(const float& x, const float& y);
	void initTexts();
	void initSkillIcons();

	//Update functions
	void updateKeyTime(const float& dt);
	void updateText();
	void updateButtons(sf::Vector2i& mousePosWindow);

	//Render functions
	void renderButtons(sf::RenderTarget& target);

	//Sound functions
	void playSound(const std::string& sound);

public:
	//Constructor
	SkillsMenu(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds,const float& x, const float& y) noexcept;
	~SkillsMenu();

	//Accessors
	const bool getKeyTime() const;

	//Functions
	void unlockSkill(const SkillType& type);

	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);

	friend class SkillsLevelingMenu;
	friend void PlayerGUI::initBuffSkill();
};

class ItemsMune
{
private:
	using MainTexts		= std::pair<sf::Text, sf::Text>;
	using MapTexts		= std::unordered_map<Items, sf::Text>;
	using MapButtons	= std::unordered_map<Items, std::unique_ptr<GUI::Button>>;
	using MapSprites	= std::unordered_map<Items, sf::Sprite>;
	using MapAnimations = std::unordered_map<Items, AnimationComponent>;
	using MapShapes		= std::unordered_map<Items, sf::RectangleShape>;
	using MapItemsLvl	= std::unordered_map<Items, int>;
	using Maptextures	= std::unordered_map<std::string, sf::Texture>;

	//Variables
	//References
	PlayerGUI&		playerGui;
	Player&			player;
	StatsComponent* playerStats;
	sf::Font&		font;

	//Sounds
	GuiSoundsBox&	guiSounds;

	//Core
	sf::RectangleShape background;

	int		maxLevel			= 5;
	int		unlockedItemsCount	= 0;
	float	offsetX;
	float	offsetY;

	//Key time
	float	keyTime;
	float	keyTimeMax;

	//Text
	MainTexts		mainText;
	MapTexts		upgradeTexts;
	MapTexts		statsTexts;

	//Buttons
	MapButtons		unclockButtons;
	MapButtons		upgradeButtons;

	//Coins animations and sprites
	MapSprites		coinsSprites;
	MapAnimations	coinsAnimations;

	//Items
	MapShapes		itemsIcons;
	MapShapes		upgradeItemsIcons;
	MapItemsLvl		itemsLvl;

	//Textures
	Maptextures		textures;

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
	void updateAnimations(const float& dt);
	void updateButtons(sf::Vector2i& mousePosWindow);

	void unlockItem(const Items& item);
	void upgradeItem(const Items& item);

	//Render functions
	void renderIcons(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);

	//Sound
	void playSound(const std::string& sound);

public:
	ItemsMune(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& sounds, const float& x, const float& y) noexcept;
	~ItemsMune();

	//Fonctions
	void update(sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow);
};