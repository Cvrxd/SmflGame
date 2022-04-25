#pragma once
#include <ctime>
#include <iostream> 
#include <ostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

enum button_states { BTN_IDLE =0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	//vaeiables
	// core
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	 
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, 
		sf::Font* font, const std::string& text, 
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

};

