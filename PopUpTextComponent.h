#pragma once

class PopUpTextComponent
{
private:
	//Variables
	sf::Font& font;

	std::unordered_map<std::string, sf::Text> texts;

	//Update text
	void updateText(const std::string& key);

public:
	PopUpTextComponent(sf::Font& font) noexcept;
	~PopUpTextComponent();

	//Functions
	void addText(const std::string& text, const sf::Color& color, const unsigned int& characterSize);

	bool showText(sf::RenderTarget& target, const std::string& key, const sf::Vector2f position);

};

