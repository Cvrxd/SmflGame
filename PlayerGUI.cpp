#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initStatBars()
{
	//Fill borders textures
	this->barsTextures.resize(3);
	this->barsTextures[0].loadFromFile("Textures/hud/game_hud/hp.png");
	this->barsTextures[1].loadFromFile("Textures/hud/game_hud/mana.png");
	this->barsTextures[2].loadFromFile("Textures/hud/game_hud/armor.png");

	//Borders
	this->borderTexture.loadFromFile("Textures/hud/game_hud/border.png");
	this->bars.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		this->bars[i].first.setTexture(&this->borderTexture);
		this->bars[i].first.setPosition(sf::Vector2f(130, 35 + 20 * (i * 3)));
		this->bars[i].first.setSize(sf::Vector2f(450 - (i * 80), 40));

		this->bars[i].second.setTexture(&barsTextures[i]);
		this->bars[i].second.setPosition(sf::Vector2f(130 + 5, 2 + 35 + 20 * (i * 3)));
		this->bars[i].second.setSize(sf::Vector2f(450 - (i * 80) - 10, 40 - 5));
	}
}

void PlayerGUI::initQuickSlotBars()
{
	this->quickSlotBorderTexture.loadFromFile("Textures/inventory_hud/1bit_icons.png");
}

void PlayerGUI::initTextsIcons()
{
	
	//Init icons
	this->iconsSheet.loadFromFile("Textures/hud/game_hud/icons.png");
	this->iconsSprites["LEVEL"].setTexture(&iconsSheet);
	this->iconsSprites["LEVEL"].setTextureRect(sf::IntRect(158,54,32,29));
	this->iconsSprites["LEVEL"].setSize(sf::Vector2f(100, 100));
	this->iconsSprites["LEVEL"].setPosition(10,20);

	this->iconsSprites["EXP"].setTexture(&iconsSheet);
	this->iconsSprites["EXP"].setTextureRect(sf::IntRect(149, 87, 40, 11));
	this->iconsSprites["EXP"].setSize(sf::Vector2f(120, 50));
	this->iconsSprites["EXP"].setPosition(1, 120);

	//Init text

	this->texts["LEVEL"].setFont(this->font);
	this->texts["LEVEL"].setString(std::to_string(this->player.getLVLcomponent()->level));
	this->texts["LEVEL"].setCharacterSize(65);
	this->texts["LEVEL"].setPosition(45, 25);

	this->texts["EXP"].setFont(this->font);
	this->texts["EXP"].setFillColor(sf::Color::Black);
	this->texts["EXP"].setString(std::to_string(this->player.getLVLcomponent()->exp));
	this->texts["EXP"].setCharacterSize(27);
	this->texts["EXP"].setPosition(55, 122);
}

//Constructor
PlayerGUI::PlayerGUI(Player& player, sf::Font& font)
	:player(player), font(font)
{
	this->initStatBars();
	this->initTextsIcons();
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::updateBars()
{
	this->bars[0].second.setSize(sf::Vector2f(
		this->bars[0].first.getSize().x / this->player.getLVLcomponent()->hpMAX * this->player.getLVLcomponent()->hp - 10,
		this->bars[0].second.getSize().y));

	this->bars[1].second.setSize(sf::Vector2f(
		this->bars[1].first.getSize().x / this->player.getLVLcomponent()->magickaMAX * this->player.getLVLcomponent()->magicka - 10,
		this->bars[1].second.getSize().y));

	this->bars[2].second.setSize(sf::Vector2f(
		this->bars[2].first.getSize().x / this->player.getLVLcomponent()->armorMAX * this->player.getLVLcomponent()->armor - 10,
		this->bars[2].second.getSize().y));
}

void PlayerGUI::updateTextIcons()
{
	if (this->player.getLVLcomponent()->level == 10)
	{
		this->texts["LEVEL"].setPosition(30, 25);
	}

	if (this->player.getLVLcomponent()->exp < 10)
	{
		this->texts["EXP"].setPosition(55, 122);
	}
	else if(this->player.getLVLcomponent()->exp >= 10 && this->player.getLVLcomponent()->exp < 100)
	{
		this->texts["EXP"].setPosition(50, 122);
	}
	else
	{
		this->texts["EXP"].setPosition(40, 122);
	}

	this->texts["LEVEL"].setString(std::to_string(this->player.getLVLcomponent()->level));
	this->texts["EXP"].setString(std::to_string(this->player.getLVLcomponent()->exp));
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
}
