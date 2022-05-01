#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = std::move("UNITIALIZED");
	this->resolution = sf::VideoMode::getDesktopMode();
	this->vertucalSync = false;
	this->fullscreen = false;
	this->framerateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string& file)
{
	std::ofstream ofs(file);

	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->framerateLimit;
		ofs << this->vertucalSync;
		ofs << this->contextSettings.antialiasingLevel;
	}
	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string& file)
{
	std::ifstream ifs(file);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->framerateLimit;
		ifs >> this->vertucalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	ifs.close();
}