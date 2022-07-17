#pragma once
#include <Gui/GeneralGui/Gui.h>

class GameOverMenu
{
private:
	using ButtonPtr = std::unique_ptr<GUI::Button>;

	//Variables
	sf::Font& font;
	sf::RenderWindow& window;

	sf::RectangleShape  background;
	sf::RectangleShape  container;

	sf::Text            text;
	sf::Music           music;
	float               musicVolume;

	ButtonPtr           exitButton;

	//Init functions
	void initGui() noexcept;

public:

	GameOverMenu(sf::RenderWindow& window, sf::Font& font) noexcept;
	~GameOverMenu();

	//Accessors
	const bool exitButtonIsPressed() const;

	//Functions
	void update(const float& dt, sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};
