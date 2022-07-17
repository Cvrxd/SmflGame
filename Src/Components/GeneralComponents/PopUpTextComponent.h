#pragma once

class PopUpTextComponent
{
private:
	using TextMap = std::unordered_map < std::string, sf::Text>;

	//Variables
	const sf::Font& font;

	sf::Color orirginalTextColor;

	float textExpireTime  = 1.2f;

	float offsetX         = 0;
	float offsetY         = 0;

	float offsetYbase     = 0;
	float modifierY	      = 5;

	TextMap textsMap;

public:
	PopUpTextComponent  (const sf::Font& font) noexcept;
	~PopUpTextComponent ();

	//Accessors
	const float& getpTextExpireTime () const;

	//Functions
	void addText      (const std::string& text, const sf::Color& color, const unsigned int& characterSize);
	
	void popUpText    (sf::RenderTarget& target, const std::string& key, const sf::Vector2f position);

	void prepareText  (const std::string& key);
	void resetText    (const std::string& key);
};

