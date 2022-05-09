#pragma once
#include"Player.h"

class Player;

class PlayerGUI
{
private:
	//Variables
	Player& player;
	sf::Font& font;

	//Stat bars 
	sf::Texture borderTexture;
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> bars;
	std::vector<sf::Texture> barsTextures;

	//Quick slot bars
	sf::Texture quickSlotBorderTexture;
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> quickSlotBars;
	std::vector<sf::Texture> quickSlotIconsTextures;

	//Text and icons
	sf::Texture iconsSheet;
	std::map<std::string, sf::Text> texts;
	std::map<std::string, sf::RectangleShape> iconsSprites;

	//Functions
	void initStatBars();
	void initQuickSlotBars();
	void initTextsIcons();
public:
	//Constructor
	PlayerGUI(Player& player, sf::Font& font);
	~PlayerGUI();

	//Functions
	void updateBars();
	void updateTextIcons();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

