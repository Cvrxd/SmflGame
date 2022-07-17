#pragma once
#include <Components/EntitiesComponents/SkillsComponent.h>

#include<Components/GeneralComponents/ISoundsPlayer.h>
#include<Components/GeneralComponents/IMusicPlayer.h>

class SkillsComponent;

static constexpr float VOLUME_MODIFIER = 15.f;

struct GuiSoundsBox : public ISoundsPlayer<std::string>
{
	using SoundsMap  = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;

	SoundsMap   sounds;

	GuiSoundsBox(): ISoundsPlayer(sounds, 1.5f, 2.f)
	{
		this->sounds["UNLOCK_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_unlock.wav");
		this->sounds["UNLOCK_SKILL"].second.setBuffer(this->sounds["UNLOCK_SKILL"].first);

		this->sounds["UNLOCK_ITEM"].first.loadFromFile("Sounds/game_state/items_menu_sounds/unlock_item.wav");
		this->sounds["UNLOCK_ITEM"].second.setBuffer(this->sounds["UNLOCK_ITEM"].first);

		this->sounds["UPGRADE_ITEM"].first.loadFromFile("Sounds/game_state/items_menu_sounds/upgrade_item.wav");
		this->sounds["UPGRADE_ITEM"].second.setBuffer(this->sounds["UPGRADE_ITEM"].first);

		this->sounds["CLICK"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/click.wav");
		this->sounds["CLICK"].second.setBuffer(this->sounds["CLICK"].first);
	}
};

class GameStateSoundBox : public IMusicPlayer<std::string>
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

class PlayerSoundBox : public ISoundsPlayer<std::string>
{
private:
	using SoundsMap = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;

	//Variables
	float volume = 0.1f;
	const float volumeMax = 1.f;

	SoundsMap sounds;

	//Movement sound to play
	sf::Sound* movementSound;

	//Intit functions
	void initSounds();

public:
	PlayerSoundBox();
	~PlayerSoundBox();


	//Functions
	void changeMovementSound  (const bool& running);
	void changeMovementVolume (const bool& increase);

	void pauseMovementSound   ();
	void unpauseMovementSound ();
};

class EnemySoundBox
{
private:
	using SoundsMap              = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;
	using SkillsImpactSoundsMap  = std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>>;

	//Variables
	//Sounds
	ISoundsPlayer<std::string> soundPlayer;
	ISoundsPlayer<SkillType>   impactSoundsPlayer;

	SoundsMap              sounds;
	SkillsImpactSoundsMap  skillsImpact;


	//Init functions
	void initSound             ();
	void initSkillImpactSounds ();

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
