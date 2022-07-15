#pragma once
#include <Gui/GeneralGui/Gui.h>

class Button;

class PauseMenu
{
private:
	using MapButtons    =  std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;
	using Sound         =  std::pair<sf::SoundBuffer, sf::Sound>;

	//Variables
	sf::Font    font;
	sf::Text    menuText;
	sf::Texture backgroundTexture;

	sf::RectangleShape background;
	sf::RectangleShape container;

	//Buttons
	MapButtons buttons;

	//Sounds
	Sound clickSound;

	//Init functions
	void initSounds();

public:
	PauseMenu  (sf::RenderWindow& window, sf::Font& font)   noexcept;
	~PauseMenu();

	//Accessors
	MapButtons& getButtons();

	//Functions
	const bool isButtonPressed  (const std::string& key);

	void playClickSound  ();
	void addButton       (const std::string& key, const float& y, const float& modifier_x, const std::string& text);
	void update          (const sf::Vector2i& mousePosition);
	void render          (sf::RenderTarget& target);
};

