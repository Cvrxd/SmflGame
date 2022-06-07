#pragma once

struct GraphicsSettings
{
	using Videomodes = std::vector<sf::VideoMode>;

	//Variables
	std::string         title;
	unsigned            framerateLimit;
	bool                fullscreen;
	bool                vertucalSync;

	sf::VideoMode       resolution;
	sf::ContextSettings contextSettings;
	Videomodes          videModes;

	//Functions
	void saveToFile(const std::string& file);
	void loadFromFile(const std::string& file);
};
