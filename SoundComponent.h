#pragma once
#include"SkillsComponent.h"

class SkillsComponent;

struct GuiSoundsBox
	{
		using SoundsMap = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;

		SoundsMap sounds;

		GuiSoundsBox()
		{
			this->sounds["UPGRADE_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_upgrade.wav");
			this->sounds["UPGRADE_SKILL"].second.setBuffer(this->sounds["UPGRADE_SKILL"].first);
			this->sounds["UPGRADE_SKILL"].second.setVolume(2.f);

			this->sounds["UNLOCK_SKILL"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/spell_unlock.wav");
			this->sounds["UNLOCK_SKILL"].second.setBuffer(this->sounds["UNLOCK_SKILL"].first);
			this->sounds["UNLOCK_SKILL"].second.setVolume(2.f);

			this->sounds["UNLOCK_ITEM"].first.loadFromFile("Sounds/game_state/items_menu_sounds/unlock_item.wav");
			this->sounds["UNLOCK_ITEM"].second.setBuffer(this->sounds["UNLOCK_ITEM"].first);
			this->sounds["UNLOCK_ITEM"].second.setVolume(2.f);

			this->sounds["UPGRADE_ITEM"].first.loadFromFile("Sounds/game_state/items_menu_sounds/upgrade_item.wav");
			this->sounds["UPGRADE_ITEM"].second.setBuffer(this->sounds["UPGRADE_ITEM"].first);
			this->sounds["UPGRADE_ITEM"].second.setVolume(2.f);

			this->sounds["CLICK"].first.loadFromFile("Sounds/game_state/skills_menu_sounds/click.wav");
			this->sounds["CLICK"].second.setBuffer(this->sounds["CLICK"].first);
			this->sounds["CLICK"].second.setVolume(10.f);
		}
	};

class PlayerSoundBox
	{
	private:
		using SoundsMap = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;

		//Variables
		float movementVolumeMin = 0.1f;
		float movementVolumeMax = 0.5f;

		SoundsMap sounds;

		//Movement sound to play
		sf::Sound* movementSound;

	public:
		PlayerSoundBox   () noexcept;
		~PlayerSoundBox  ();

		//Functions
		void addWalkingSound       (const std::string& path);
		void addRunningSound       (const std::string& path);

		void changeMovementSound   (const bool& running);
		void changeMovementVolume  (const bool& increase);

		void pauseMovementSound    ();
		void unpauseMovementSound  ();
	};

class EnemySoundBox
	{
	private:
		using SoundsMap = std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>>;
		using SkillsImpactSoundsMap = std::unordered_map<SkillType, std::pair<sf::SoundBuffer, sf::Sound>>;

		//Variables
		SoundsMap              sounds;
		SkillsImpactSoundsMap  skillsImpact;

		//Init functions
		void initSound();
	public:
		EnemySoundBox() noexcept;
		~EnemySoundBox();

		//Functions
		void playSound(const SkillType& sound);
		void playSound(const std::string& sound);

		void pauseSounds();
		void resumeSounds();
	};
