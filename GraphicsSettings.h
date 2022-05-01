#pragma once

struct GraphicsSettings
{
	//Variables
	std::string title;
	bool fullscreen;
	bool vertucalSync;
	unsigned framerateLimit;

	sf::VideoMode resolution;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videModes;

	GraphicsSettings();

	//Functions
	void saveToFile(const std::string& file);
	void loadFromFile(const std::string& file);
};
