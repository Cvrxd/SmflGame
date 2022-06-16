#include "stdafx.h"
#include "SoundComponent.h"

//======================
//Player sound Box======
//======================

//Init functions
void PlayerSoundBox::initSounds()
{
	//Walking sound
	if (!this->sounds["WALKING"].first.loadFromFile("Sounds/game_state/player/walking.wav"))
	{
		throw("UNABLE TO LOAD PLAYER WALKING SOUND");
	}
	this->sounds["WALKING"].second.setBuffer(this->sounds["WALKING"].first);
	this->sounds["WALKING"].second.setVolume(this->movementVolumeMin);
	this->sounds["WALKING"].second.setLoop(true);

	this->movementSound = &this->sounds["WALKING"].second;

	this->movementSound->play();
	this->movementSound->pause();

	//Running sound
	if (!this->sounds["RUNNING"].first.loadFromFile("Sounds/game_state/player/running.wav"))
	{
		throw("UNABLE TO LOAD PLAYER WALKING SOUND");
	}
	this->sounds["RUNNING"].second.setBuffer(this->sounds["RUNNING"].first);
	this->sounds["RUNNING"].second.setVolume(this->movementVolumeMin);
	this->sounds["RUNNING"].second.setLoop(true);

	this->sounds["RUNNING"].second.play();
	this->sounds["RUNNING"].second.pause();
}

//Constructors
PlayerSoundBox::PlayerSoundBox() 
	:movementSound(nullptr)
{
	this->initSounds();
}

PlayerSoundBox::~PlayerSoundBox()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Music::Stopped)
		{
			el.second.second.stop();
		}
	}
}

//Public functions
void PlayerSoundBox::changeMovementSound(const bool& running)
{
	if (running)
	{
		if (this->movementSound != &this->sounds["RUNNING"].second)
		{
			this->movementSound = &this->sounds["RUNNING"].second;
			this->sounds["WALKING"].second.pause();
		}
	}
	else
	{
		if (this->movementSound != &this->sounds["WALKING"].second)
		{
			this->movementSound = &this->sounds["WALKING"].second;
			this->sounds["RUNNING"].second.pause();
		}
	}
}

void PlayerSoundBox::changeMovementVolume(const bool& increase)
{
	if (increase)
	{
		if (this->movementSound->getVolume() != this->movementVolumeMax)
		{
			this->movementSound->setVolume(this->movementVolumeMax);
		}
	}
	else
	{
		if (this->movementSound->getVolume() != this->movementVolumeMin)
		{
			this->movementSound->setVolume(this->movementVolumeMax);
		}
	}
}

void PlayerSoundBox::pauseMovementSound()
{
	this->movementSound->pause();
}

void PlayerSoundBox::unpauseMovementSound()
{
	if (this->movementSound->getStatus() == sf::Sound::Paused)
	{
		this->movementSound->play();
	}
}

//=======================
//GameState sound Box====
//=======================

//Init functions
inline void GameStateSoundBox::initMusic()
{
	//Loading game music
	if (!this->music["THEME"].openFromFile("Sounds/game_state/music/background_music.ogg"))
	{
		throw("UNABLE TO LOAD THEME MUSIC");
	}
	if (!this->music["PAUSE"].openFromFile("Sounds/game_state/music/pause_menu_music.ogg"))
	{
		throw("UNABLE TO LOAD PAUSE MENU MUSIC");
	}
	if (!this->music["BOSS_FIGHT"].openFromFile("Sounds/game_state/music/boss_fight_music.ogg"))
	{
		throw("UNABLE TO LOAD BOSS FIGHT MUSIC");
	}

	//Music loop
	this->music["THEME"].setLoop      (true);
	this->music["PAUSE"].setLoop      (true);
	this->music["BOSS_FIGHT"].setLoop (true);
  
	//Music volume
	this->music["THEME"].setVolume      (this->volume);
	this->music["PAUSE"].setVolume      (this->volume);
	this->music["BOSS_FIGHT"].setVolume (this->volume);
}

//Constructor
GameStateSoundBox::GameStateSoundBox()
{
	this->initMusic();
}

GameStateSoundBox::~GameStateSoundBox()
{
	//Stoping all music
	this->stopBossFightMusic();
	this->stopPauseMenuMusic();
	this->stopThemeMusic();
}

//Accessors
void GameStateSoundBox::setVolume(const float& volume)
{
	for (auto& el : this->music)
	{
		el.second.setVolume(volume);
	}

	this->volume = volume;
}

const float& GameStateSoundBox::getVolume() const
{
	return this->volume;
}

const float& GameStateSoundBox::getVolumeMax() const
{
	return this->volumeMAX;
}

//Public functions
//Volume
void GameStateSoundBox::increaseVolume()
{
	this->volume += 0.15f;

	if (this->volume > this->volumeMAX)
	{
		this->volume = this->volumeMAX;
	}

	this->setVolume(this->volume);
}

void GameStateSoundBox::decreaseVolume()
{
	this->volume -= 0.15f;

	if (this->volume < 0)
	{
		this->volume = 0;
	}

	this->setVolume(this->volume);
}

//Music
void GameStateSoundBox::pauseThemeMusic()
{
	if (this->music["THEME"].getStatus() != sf::Music::Paused)
	{
		this->music["THEME"].pause();
	}
}

void GameStateSoundBox::playThemeMusic()
{
	if (this->music["THEME"].getStatus() != sf::Music::Playing)
	{
		this->music["THEME"].play();
	}
}

void GameStateSoundBox::stopThemeMusic()
{
	if (this->music["THEME"].getStatus() != sf::Music::Stopped)
	{
		this->music["THEME"].stop();
	}
}

void GameStateSoundBox::pausePauseMenuMusic()
{
	if (this->music["PAUSE"].getStatus() != sf::Music::Paused)
	{
		this->music["PAUSE"].pause();
	}
}

void GameStateSoundBox::playPauseMenuMusic()
{
	if (this->music["PAUSE"].getStatus() != sf::Music::Playing)
	{
		this->music["PAUSE"].play();
	}
}

void GameStateSoundBox::stopPauseMenuMusic()
{
	if (this->music["PAUSE"].getStatus() != sf::Music::Stopped)
	{
		this->music["PAUSE"].stop();
	}
}

void GameStateSoundBox::pauseBossFightMusic()
{
	if (this->music["BOSS_FIGHT"].getStatus() != sf::Music::Paused)
	{
		this->music["BOSS_FIGHT"].pause();
	}
}

void GameStateSoundBox::playBossFightMusic()
{
	if (this->music["BOSS_FIGHT"].getStatus() != sf::Music::Playing)
	{
		this->music["BOSS_FIGHT"].play();
	}
}

void GameStateSoundBox::stopBossFightMusic()
{
	if (this->music["BOSS_FIGHT"].getStatus() != sf::Music::Stopped)
	{
		this->music["BOSS_FIGHT"].stop();
	}
}

//======================
//Enemies sound Box=====
//======================

//Init functions
inline void EnemySoundBox::initSound()
{
	//Hit impact and crit impact
	this->sounds["PLAYER_CRIT"].first.loadFromFile("Sounds/game_state/hit_sounds/crit.ogg");
	this->sounds["PLAYER_CRIT"].second.setBuffer(this->sounds["PLAYER_CRIT"].first);
	this->sounds["PLAYER_CRIT"].second.setVolume(0.7f);

	this->sounds["PLAYER_HIT"].first.loadFromFile("Sounds/game_state/hit_sounds/hit.wav");
	this->sounds["PLAYER_HIT"].second.setBuffer(this->sounds["PLAYER_HIT"].first);
	this->sounds["PLAYER_HIT"].second.setVolume(5.f);

	//Skills impact
	this->skillsImpact[SkillType::DARK_BOLT].first.loadFromFile("Sounds/game_state/spell_sounds/dark_bolt.ogg");
	this->skillsImpact[SkillType::DARK_BOLT].second.setBuffer(this->skillsImpact[SkillType::DARK_BOLT].first);
	this->skillsImpact[SkillType::DARK_BOLT].second.setVolume(10.f);

	this->skillsImpact[SkillType::HOLY_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/holy_strile_impact.wav");
	this->skillsImpact[SkillType::HOLY_STRIKE].second.setBuffer(this->skillsImpact[SkillType::HOLY_STRIKE].first);
	this->skillsImpact[SkillType::HOLY_STRIKE].second.setVolume(2.f);

	this->skillsImpact[SkillType::BLOOD_SPIKE].first.loadFromFile("Sounds/game_state/spell_sounds/blood_strike_impact.wav");
	this->skillsImpact[SkillType::BLOOD_SPIKE].second.setBuffer(this->skillsImpact[SkillType::BLOOD_SPIKE].first);
	this->skillsImpact[SkillType::BLOOD_SPIKE].second.setVolume(2.f);

	this->skillsImpact[SkillType::DARK_POSION].first.loadFromFile("Sounds/game_state/spell_sounds/dark_poison_impact.wav");
	this->skillsImpact[SkillType::DARK_POSION].second.setBuffer(this->skillsImpact[SkillType::DARK_POSION].first);
	this->skillsImpact[SkillType::DARK_POSION].second.setVolume(2.f);

	this->skillsImpact[SkillType::POISON_CLAW].first.loadFromFile("Sounds/game_state/spell_sounds/poison_claw_impact.wav");
	this->skillsImpact[SkillType::POISON_CLAW].second.setBuffer(this->skillsImpact[SkillType::POISON_CLAW].first);
	this->skillsImpact[SkillType::POISON_CLAW].second.setVolume(2.f);

	this->skillsImpact[SkillType::THUNDER_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/thunder_strike_impact.wav");
	this->skillsImpact[SkillType::THUNDER_STRIKE].second.setBuffer(this->skillsImpact[SkillType::THUNDER_STRIKE].first);
	this->skillsImpact[SkillType::THUNDER_STRIKE].second.setVolume(2.f);

	this->skillsImpact[SkillType::FIRE_EXPLOSION].first.loadFromFile("Sounds/game_state/spell_sounds/fire_explosion_impact.wav");
	this->skillsImpact[SkillType::FIRE_EXPLOSION].second.setBuffer(this->skillsImpact[SkillType::FIRE_EXPLOSION].first);
	this->skillsImpact[SkillType::FIRE_EXPLOSION].second.setVolume(2.f);

	//Bosses skill sounds
	this->sounds["SAMURAI_SKILL"].first.loadFromFile("Sounds/game_state/enemies_sounds/samurai_skill.ogg");
	this->sounds["SAMURAI_SKILL"].second.setBuffer(this->sounds["SAMURAI_SKILL"].first);
	this->sounds["SAMURAI_SKILL"].second.setVolume(1.f);

	this->sounds["NIGHTBORN_SKILL"].first.loadFromFile("Sounds/game_state/enemies_sounds/nightborn_skill.wav");
	this->sounds["NIGHTBORN_SKILL"].second.setBuffer(this->sounds["NIGHTBORN_SKILL"].first);
	this->sounds["NIGHTBORN_SKILL"].second.setVolume(2.f);

	this->sounds["FIRE_DEMON_SKILL"].first.loadFromFile("Sounds/game_state/enemies_sounds/fire_demon_skill.wav");
	this->sounds["FIRE_DEMON_SKILL"].second.setBuffer(this->sounds["FIRE_DEMON_SKILL"].first);
	this->sounds["FIRE_DEMON_SKILL"].second.setVolume(2.f);

	//Mages sound
	this->sounds["MAGE_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/mage_sound.wav");
	this->sounds["MAGE_SOUND"].second.setBuffer(this->sounds["MAGE_SOUND"].first);
	this->sounds["MAGE_SOUND"].second.setVolume(1.5f);

	this->sounds["MAGE_SPELL_CAST_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/mage_spell_cast_sound.wav");
	this->sounds["MAGE_SPELL_CAST_SOUND"].second.setBuffer(this->sounds["MAGE_SPELL_CAST_SOUND"].first);
	this->sounds["MAGE_SPELL_CAST_SOUND"].second.setVolume(1.5f);

	//Bosses sounds
	this->sounds["FIRE_DEMON_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/fire_demon_sound.wav");
	this->sounds["FIRE_DEMON_SOUND"].second.setBuffer(this->sounds["FIRE_DEMON_SOUND"].first);
	this->sounds["FIRE_DEMON_SOUND"].second.setVolume(2.f);

	this->sounds["NIGHTBORN_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/nightborn_sound.wav");
	this->sounds["NIGHTBORN_SOUND"].second.setBuffer(this->sounds["NIGHTBORN_SOUND"].first);
	this->sounds["NIGHTBORN_SOUND"].second.setVolume(2.f);

	this->sounds["SAMURAI_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/samurai_sound.wav");
	this->sounds["SAMURAI_SOUND"].second.setBuffer(this->sounds["SAMURAI_SOUND"].first);
	this->sounds["SAMURAI_SOUND"].second.setVolume(1.f);

	//Mele enemies sounds
	this->sounds["HUNTRESS_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/huntress_sound.wav");
	this->sounds["HUNTRESS_SOUND"].second.setBuffer(this->sounds["HUNTRESS_SOUND"].first);
	this->sounds["HUNTRESS_SOUND"].second.setVolume(1.f);

	this->sounds["KNIGHT1_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/knight1_sound.wav");
	this->sounds["KNIGHT1_SOUND"].second.setBuffer(this->sounds["KNIGHT1_SOUND"].first);
	this->sounds["KNIGHT1_SOUND"].second.setVolume(1.f);

	this->sounds["MALE_ENEMY_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/male_enemy_sound.wav");
	this->sounds["MALE_ENEMY_SOUND"].second.setBuffer(this->sounds["MARTIAL_HERO2_SOUND"].first);
	this->sounds["MALE_ENEMY_SOUND"].second.setVolume(1.5f);

	this->sounds["MIMIC_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/mimic_sound.wav");
	this->sounds["MIMIC_SOUND"].second.setBuffer(this->sounds["MIMIC_SOUND"].first);
	this->sounds["MIMIC_SOUND"].second.setVolume(2.5f);

	this->sounds["MIMIC_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/mimic_sound.wav");
	this->sounds["MIMIC_SOUND"].second.setBuffer(this->sounds["MIMIC_SOUND"].first);
	this->sounds["MIMIC_SOUND"].second.setVolume(2.5f);

	this->sounds["BRINGER_OF_DEATH_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/bringer_of_death_sound.wav");
	this->sounds["BRINGER_OF_DEATH_SOUND"].second.setBuffer(this->sounds["BRINGER_OF_DEATH_SOUND"].first);
	this->sounds["BRINGER_OF_DEATH_SOUND"].second.setVolume(2.5f);

	//Destroing enemies sounds 
	this->sounds["DESTROY_ENEMY_SOUND"].first.loadFromFile("Sounds/game_state/enemies_sounds/destroying_sound.wav");
	this->sounds["DESTROY_ENEMY_SOUND"].second.setBuffer(this->sounds["DESTROY_ENEMY_SOUND"].first);
	this->sounds["DESTROY_ENEMY_SOUND"].second.setVolume(2.f);
}

//Constructor
EnemySoundBox::EnemySoundBox() noexcept
{
	this->initSound();
}

EnemySoundBox::~EnemySoundBox()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Music::Stopped)
		{
			el.second.second.stop();
		}
	}
}

//Functions
void EnemySoundBox::playSound(const SkillType& sound)
{
	this->skillsImpact[sound].second.play();
}

void EnemySoundBox::playSound(const std::string& sound)
{
	this->sounds[sound].second.play();
}

void EnemySoundBox::pauseSounds()
{
	//Pause regular sounds
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() == sf::Sound::Playing)
		{
			el.second.second.pause();
		}
	}

	//Pause skill impact sounds
	for (auto& el : this->skillsImpact)
	{
		if (el.second.second.getStatus() == sf::Sound::Playing)
		{
			el.second.second.pause();
		}
	}
}

void EnemySoundBox::resumeSounds()
{
	//Unpause regular sounds
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() == sf::Sound::Paused)
		{
			el.second.second.play();
		}
	}

	//Unpause skill impact sounds
	for (auto& el : this->skillsImpact)
	{
		if (el.second.second.getStatus() == sf::Sound::Paused)
		{
			el.second.second.play();
		}
	}
}
