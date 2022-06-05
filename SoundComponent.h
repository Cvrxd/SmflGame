#pragma once

struct GuiSoundsBox
{
	std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> sounds;

	GuiSoundsBox()
	{
		this->sounds["UPGRADE_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_upgrade.wav");
		this->sounds["UPGRADE_SKILL"].second.setBuffer(this->sounds["UPGRADE_SKILL"].first);
		this->sounds["UPGRADE_SKILL"].second.setVolume(10.f);

		this->sounds["UNLOCK_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_unlock.wav");
		this->sounds["UNLOCK_SKILL"].second.setBuffer(this->sounds["UNLOCK_SKILL"].first);
		this->sounds["UNLOCK_SKILL"].second.setVolume(2.f);

		this->sounds["CLICK"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/click.wav");
		this->sounds["CLICK"].second.setBuffer(this->sounds["CLICK"].first);
		this->sounds["CLICK"].second.setVolume(10.f);
	}
};

class PlayerSoundBox
{
private:
	//Variables
	float movementVolumeMin = 0.1f;
	float movementVolumeMax = 0.5f;

	std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> sounds;

	//Movement sound to play
	sf::Sound* movementSound;

public:
	PlayerSoundBox() noexcept;
	~PlayerSoundBox();

	//Functions
	void addWalkingSound(const std::string& path);
	void addRunningSound(const std::string& path);

	void changeMovementSound(const bool& running);
	void changeMovementVolume(const bool& increase);

	void pauseMovementSound();
	void unpauseMovementSound();
};

class EnemySoundBox
{
private:
	//Variables
	std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> hit;
	std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>> skillsImpact;

public:
	EnemySoundBox();
	~EnemySoundBox();
};

