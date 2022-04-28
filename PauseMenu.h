#pragma once
#include <ctime>
#include <iostream> 
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include "Gui.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

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

	std::map<std::string, GUI::Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	//Accessors
	std::map<std::string, GUI::Button*>& getButtons();

	//Functions
	const bool& isButtonPressed(const std::string& key);
	void addButton(const std::string& key, const float& y, const float& modifier_x, const std::string& text);
	void update(const sf::Vector2f& mousePosition);
	void render(sf::RenderTarget& target);
};

