#pragma once
#include"SkillsComponent.h"

class SkillsComponent;

#define VOLUME_MODIFIER 15.f

struct GuiSoundsBox
{
	using SoundsMap  = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;
	using VolumesMap = std::unordered_map<std::string, float>;

	SoundsMap   sounds;
	VolumesMap  volumes;

	GuiSoundsBox()
	{
		this->volumes["UNLOCK_SKILL"] = 2.f;
		this->sounds["UNLOCK_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_unlock.wav");
		this->sounds["UNLOCK_SKILL"].second.setBuffer(this->sounds["UNLOCK_SKILL"].first);
		this->sounds["UNLOCK_SKILL"].second.setVolume(this->volumes["UNLOCK_SKILL"]);

		this->volumes["UNLOCK_ITEM"] = 2.f;
		this->sounds["UNLOCK_ITEM"].first.loadFromFile("Sounds/game_state/items_menu_sounds/unlock_item.wav");
		this->sounds["UNLOCK_ITEM"].second.setBuffer(this->sounds["UNLOCK_ITEM"].first);
		this->sounds["UNLOCK_ITEM"].second.setVolume(this->volumes["UNLOCK_ITEM"]);

		this->volumes["UPGRADE_ITEM"] = 2.f;
		this->sounds["UPGRADE_ITEM"].first.loadFromFile("Sounds/game_state/items_menu_sounds/upgrade_item.wav");
		this->sounds["UPGRADE_ITEM"].second.setBuffer(this->sounds["UPGRADE_ITEM"].first);
		this->sounds["UPGRADE_ITEM"].second.setVolume(this->volumes["UPGRADE_ITEM"]);

		this->volumes["CLICK"] = 10.f;
		this->sounds["CLICK"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/click.wav");
		this->sounds["CLICK"].second.setBuffer(this->sounds["CLICK"].first);
		this->sounds["CLICK"].second.setVolume(this->volumes["CLICK"]);
	}

	void stopSounds()
	{
		for (auto& el : this->sounds)
		{
			if (el.second.second.getStatus() != sf::Music::Stopped)
			{
				el.second.second.stop();
			}
		}
	}

	void increaseVolume()
	{
		for (auto& el : this->sounds)
		{
			el.second.second.setVolume(el.second.second.getVolume() + (this->volumes[el.first] * VOLUME_MODIFIER / 100.f));
		}

		this->sounds["CLICK"].second.setVolume(this->volumes["CLICK"]);
	}

	void decreaseVolume()
	{
		for (auto& el : this->sounds)
		{
			el.second.second.setVolume(el.second.second.getVolume() - (this->volumes[el.first] * VOLUME_MODIFIER / 100.f));

			if (el.second.second.getVolume() < 0)
			{
				el.second.second.setVolume(0);
			}
		}

		this->sounds["CLICK"].second.setVolume(this->volumes["CLICK"]);
	}

	void setVolume(const float& volume)
	{
		for (auto& el : this->sounds)
		{
			el.second.second.setVolume(volume);
		}

		this->sounds["CLICK"].second.setVolume(this->volumes["CLICK"]);
	}
};

class GameStateSoundBox
{
private:
	using MusicMap = std::unordered_map<std::string, sf::Music>;

	//Variables
	MusicMap music;

	float volume          = 1.7f;
	const float volumeMAX = 3.f;

	//Functions
	void initMusic();
public:
	GameStateSoundBox();
	~GameStateSoundBox();

	//Accessors
	void setVolume(const float& volume);

	const float& getVolume    ()   const;
	const float& getVolumeMax ()   const;

	//Functions
	void increaseVolume();
	void decreaseVolume();

	//Theme music
	void pauseThemeMusic();
	void playThemeMusic ();
	void stopThemeMusic ();

	//Puse menu music
	void pausePauseMenuMusic();
	void playPauseMenuMusic ();
	void stopPauseMenuMusic ();

	//Boss fight music
	void pauseBossFightMusic();
	void playBossFightMusic ();
	void stopBossFightMusic ();

	//Game over music
	void pauseGameOverMusic();
	void playGameOverMusic();
	void stopGameOverMusic();
};

class PlayerSoundBox
{
private:
	using SoundsMap = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;

	//Variables
	float volumeMin = 0.1f;
	float volumeMax = 0.5f;

	SoundsMap sounds;

	//Movement sound to play
	sf::Sound* movementSound;

	//Intit functions
	void initSounds();

public:
	PlayerSoundBox();
	~PlayerSoundBox();

	//Accessors
	void setVolume(const float& volume);

	//Functions
	void changeMovementSound  (const bool& running);
	void changeMovementVolume (const bool& increase);

	void increaseVolume       ();
	void decreaseVolume       ();

	void pauseMovementSound   ();
	void unpauseMovementSound ();
};

class EnemySoundBox
{
private:
	using SoundsMap              = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;
	using SkillsImpactSoundsMap  = std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>>;
	using SoundsVolumeMap        = std::unordered_map<std::string, float>;
	using SkillsImpactVolumeMap  = std::unordered_map<SkillType, float>;

	//Variables
	//Sounds
	SoundsMap              sounds;
	SkillsImpactSoundsMap  skillsImpact;

	//Volumes
	SoundsVolumeMap        soundsVolumes;
	SkillsImpactVolumeMap  skillsImpactVolumes;

	//Init functions
	void initSound             ();
	void initSkillImpactSounds ();
	void initVolumes           ();

public:
	EnemySoundBox() noexcept;
	~EnemySoundBox();

	//Accessors
	void setVolume    (const float& volume);

	//Functions
	void playSound    (const SkillType& sound);
	void playSound    (const std::string& sound);

	void pauseSounds  ();
	void resumeSounds ();

	void increaseVolume();
	void decreaseVolume();
};
