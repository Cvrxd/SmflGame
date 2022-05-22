#pragma once
#include "Gui.h"

class Button;

class PauseMenu
{
private:
	//Variables
	//
	//Core
	sf::Font font;
	sf::Text menuText;
	sf::Texture backgroundTexture;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::unordered_map<std::string, GUI::Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	//Accessors
	std::unordered_map<std::string, GUI::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string& key);
	void addButton(const std::string& key, const float& y, const float& modifier_x, const std::string& text);
	void update(const sf::Vector2i& mousePosition);
	void render(sf::RenderTarget& target);
};

