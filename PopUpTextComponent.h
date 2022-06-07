#pragma once

class PopUpTextComponent
{
private:
	using TextMap = std::unordered_map < std::string, sf::Text>;

	//Variables
	sf::Font& font;

	TextMap texts;

	//Update text
	void updateText (const std::string& key);

public:
	PopUpTextComponent  (sf::Font& font) noexcept;
	~PopUpTextComponent ();

	//Functions
	void addText (const std::string& text, const sf::Color& color, const unsigned int& characterSize);
	 
	bool showText (sf::RenderTarget& target, const std::string& key, const sf::Vector2f position);

};

