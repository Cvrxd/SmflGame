#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initStatBars()
{
	this->textures["HP_BAR"].loadFromFile("Textures/hud/game_hud/hp.png");
	this->textures["MANA_BAR"].loadFromFile("Textures/hud/game_hud/mana.png");
	this->textures["ARMOR_BAR"].loadFromFile("Textures/hud/game_hud/armor.png");
	this->textures["BAR_BORDER"].loadFromFile("Textures/hud/game_hud/border.png");
	
	//Borders
	this->bars.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		this->bars[i].first.setTexture(&this->textures["BAR_BORDER"]);
		this->bars[i].first.setPosition(sf::Vector2f(130, 35 + 20 * (i * 3)));
		this->bars[i].first.setSize(sf::Vector2f(450 - (i * 80), 40));

		this->bars[i].second.setPosition(sf::Vector2f(130 + 5, 2 + 35 + 20 * (i * 3)));
		this->bars[i].second.setSize(sf::Vector2f(450 - (i * 80) - 10, 40 - 5));
	}

	this->bars[0].second.setTexture(&this->textures["HP_BAR"]);
	this->bars[1].second.setTexture(&this->textures["MANA_BAR"]);
	this->bars[2].second.setTexture(&this->textures["ARMOR_BAR"]);
}

void PlayerGUI::initQuickSlotBars()
{
	//Quick slot bars textures
	this->quickSlotBars.resize(7);
	
	for (int i = 0; i < 7; ++i)
	{
		this->quickSlotBars[i].first.setSize(sf::Vector2f(48, 48));
		this->quickSlotBars[i].first.setFillColor(sf::Color(200,200, 200, 100));
		this->quickSlotBars[i].first.setPosition(650 + (i * 100), 920);
		this->quickSlotBars[i].first.setOutlineColor(sf::Color::White);
		this->quickSlotBars[i].first.setOutlineThickness(1.f);
	}
}

void PlayerGUI::initTextsIcons()
{
	//Game icons
	this->textures["ICON_SHEET"].loadFromFile("Textures/hud/game_hud/icons.png");
	this->textures["QUICK_SLOT_HUD"].loadFromFile("Textures/hud/game_hud/arrows.png");

	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setTexture(&this->textures["QUICK_SLOT_HUD"]);
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setTextureRect(sf::IntRect(0, 0, 50, 84));
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setSize(sf::Vector2f(60, 100));
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setPosition(520, 895);

	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setTexture(&this->textures["QUICK_SLOT_HUD"]);
	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setTextureRect(sf::IntRect(165, 0, 48, 84));
	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setSize(sf::Vector2f(60, 100));
	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setPosition(1380, 895);

	this->iconsSprites["LEVEL"].setTexture(&this->textures["ICON_SHEET"]);
	this->iconsSprites["LEVEL"].setTextureRect(sf::IntRect(158,54,32,29));
	this->iconsSprites["LEVEL"].setSize(sf::Vector2f(100, 100));
	this->iconsSprites["LEVEL"].setPosition(10,20);

	this->iconsSprites["EXP"].setTexture(&this->textures["ICON_SHEET"]);
	this->iconsSprites["EXP"].setTextureRect(sf::IntRect(149, 87, 40, 11));
	this->iconsSprites["EXP"].setSize(sf::Vector2f(120, 50));
	this->iconsSprites["EXP"].setPosition(1, 120);

	//Exp and LVL text
	this->texts["LEVEL"].setFont(this->font);
	this->texts["LEVEL"].setString(std::to_string(this->player.getStatsComponent()->level));
	this->texts["LEVEL"].setCharacterSize(65);
	this->texts["LEVEL"].setPosition(45, 25);

	this->texts["EXP"].setFont(this->font);
	this->texts["EXP"].setFillColor(sf::Color::Black);
	this->texts["EXP"].setString(std::to_string(this->player.getStatsComponent()->exp));
	this->texts["EXP"].setCharacterSize(27);
	this->texts["EXP"].setPosition(55, 122);

	//Quick slot text
	for (int i = 0; i < 7; ++i)
	{
		this->texts["SLOT" + std::to_string(i)].setFont(this->font);
		this->texts["SLOT" + std::to_string(i)].setFillColor(sf::Color::White);
		this->texts["SLOT" + std::to_string(i)].setCharacterSize(25);
		this->texts["SLOT" + std::to_string(i)].setString(std::to_string(i+1));
		if (i == 5)
		{
			this->texts["SLOT" + std::to_string(i)].setString("Q");
		}
		if (i == 6)
		{
			this->texts["SLOT" + std::to_string(i)].setString("E");
		}
		this->texts["SLOT" + std::to_string(i)].setPosition(650 + (i * 100)+ 5, 915);

	}
}

void PlayerGUI::initItems()
{
	inventoryIcons["HELMET"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["HELMET"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["HELMET"].first.setPosition(1700, 100);
	inventoryIcons["HELMET"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["HELMET"].first.setOutlineThickness(1.f);

	inventoryIcons["ARMOR"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["ARMOR"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["ARMOR"].first.setPosition(1700, 100 + 64);
	inventoryIcons["ARMOR"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["ARMOR"].first.setOutlineThickness(1.f);

	inventoryIcons["GLOVES"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["GLOVES"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["GLOVES"].first.setPosition(1700, 100 + 64 * 2);
	inventoryIcons["GLOVES"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["GLOVES"].first.setOutlineThickness(1.f);

	inventoryIcons["BOOTS"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["BOOTS"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["BOOTS"].first.setPosition(1700, 100 + 64 * 3);
	inventoryIcons["BOOTS"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["BOOTS"].first.setOutlineThickness(1.f);

	inventoryIcons["SWORD"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["SWORD"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["SWORD"].first.setPosition(1700 - 64, 100 + 64 * 2);
	inventoryIcons["SWORD"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["SWORD"].first.setOutlineThickness(1.f);

	inventoryIcons["STAFF"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["STAFF"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["STAFF"].first.setPosition(1700 + 64, 100 + 64 * 2);
	inventoryIcons["STAFF"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["STAFF"].first.setOutlineThickness(1.f);

	inventoryIcons["RING"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["RING"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["RING"].first.setPosition(1700 - 64, 100 + 64);
	inventoryIcons["RING"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["RING"].first.setOutlineThickness(1.f);

	inventoryIcons["NECKLASE"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["NECKLASE"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["NECKLASE"].first.setPosition(1700 + 64, 100 + 64);
	inventoryIcons["NECKLASE"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["NECKLASE"].first.setOutlineThickness(1.f);
}

//Constructor
PlayerGUI::PlayerGUI(Player& player, sf::Font& font)
	:player(player), font(font)
{
	this->initStatBars();
	this->initTextsIcons();
	this->initQuickSlotBars();
	this->initItems();
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::addItem()
{
}

void PlayerGUI::addSkill()
{
}

void PlayerGUI::updateBars()
{
	this->bars[0].second.setSize(sf::Vector2f(
		this->bars[0].first.getSize().x / this->player.getStatsComponent()->hpMAX * this->player.getStatsComponent()->hp - 10,
		this->bars[0].second.getSize().y));

	this->bars[1].second.setSize(sf::Vector2f(
		this->bars[1].first.getSize().x / this->player.getStatsComponent()->magickaMAX * this->player.getStatsComponent()->magicka - 10,
		this->bars[1].second.getSize().y));

	this->bars[2].second.setSize(sf::Vector2f(
		this->bars[2].first.getSize().x / this->player.getStatsComponent()->armorMAX * this->player.getStatsComponent()->armor - 10,
		this->bars[2].second.getSize().y));
}

void PlayerGUI::updateTextIcons()
{
	if (this->player.getStatsComponent()->level == 10)
	{
		this->texts["LEVEL"].setPosition(30, 25);
	}

	if (this->player.getStatsComponent()->exp < 10)
	{
		this->texts["EXP"].setPosition(55, 122);
	}
	else if(this->player.getStatsComponent()->exp >= 10 && this->player.getStatsComponent()->exp < 100)
	{
		this->texts["EXP"].setPosition(50, 122);
	}
	else
	{
		this->texts["EXP"].setPosition(40, 122);
	}

	this->texts["LEVEL"].setString(std::to_string(this->player.getStatsComponent()->level));
	this->texts["EXP"].setString(std::to_string(this->player.getStatsComponent()->exp));
}

void PlayerGUI::update(const float& dt)
{
	this->updateBars();
	this->updateTextIcons();
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	//Render bars
	for (auto& el : this->bars)
	{
		target.draw(el.second);
		target.draw(el.first);
	}

	//Render icons
	for (auto& el : this->iconsSprites)
	{
		target.draw(el.second);
	}

	//Render text
	for (auto& el : this->texts)
	{
		target.draw(el.second);
	}

	//Render quick slots
	for (auto& el : this->quickSlotBars)
	{
		target.draw(el.first);
		target.draw(el.second);
	}

	//Render Inventory
	for (auto& el : this->inventoryIcons)
	{
		target.draw(el.second.first);
		target.draw(el.second.second);
	}
}

//Skills Menu functions
void PlayerGUI::updateSkillsMenu(const float& dt)
{
}

void PlayerGUI::renderSkillsMenu(sf::RenderTarget& traget)
{
}
