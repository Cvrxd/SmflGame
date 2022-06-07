#include "stdafx.h"
#include "SoundComponent.h"

//======================
//Player sound Box======
//======================

//Constructors
PlayerSoundBox::PlayerSoundBox() noexcept
	:movementSound(nullptr)
{
}

PlayerSoundBox::~PlayerSoundBox()
{
}

//Functions
void PlayerSoundBox::addWalkingSound(const std::string& path)
{
	this->sounds["WALKING"].first.loadFromFile(path);
	this->sounds["WALKING"].second.setBuffer(this->sounds["WALKING"].first);
	this->sounds["WALKING"].second.setVolume(this->movementVolumeMin);
	this->sounds["WALKING"].second.setLoop(true);

	this->movementSound = &this->sounds["WALKING"].second;

	this->movementSound->play();
	this->movementSound->pause();
}

void PlayerSoundBox::addRunningSound(const std::string& path)
{
	this->sounds["RUNNING"].first.loadFromFile(path);
	this->sounds["RUNNING"].second.setBuffer(this->sounds["RUNNING"].first);
	this->sounds["RUNNING"].second.setVolume(this->movementVolumeMin);
	this->sounds["RUNNING"].second.setLoop(true);

	this->sounds["RUNNING"].second.play();
	this->sounds["RUNNING"].second.pause();
}

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

//======================
//Enemies sound Box=====
//======================

//Init functions
inline void EnemySoundBox::initSound()
{
	//Hit impact and crit impact
	this->hit["PLAYER_CRIT"].first.loadFromFile("Sounds/game_state/hit_sounds/crit.ogg");
	this->hit["PLAYER_CRIT"].second.setBuffer(this->hit["PLAYER_CRIT"].first);
	this->hit["PLAYER_CRIT"].second.setVolume(0.7f);

	this->hit["PLAYER_HIT"].first.loadFromFile("Sounds/game_state/hit_sounds/hit.wav");
	this->hit["PLAYER_HIT"].second.setBuffer(this->hit["PLAYER_HIT"].first);
	this->hit["PLAYER_HIT"].second.setVolume(2.8f);

	//Skills impact
	this->skillsImpact[SkillType::DARK_BOLT].first.loadFromFile("Sounds/game_state/spell_sounds/dark_bolt.ogg");
	this->skillsImpact[SkillType::DARK_BOLT].second.setBuffer(this->skillsImpact[SkillType::DARK_BOLT].first);
	this->skillsImpact[SkillType::DARK_BOLT].second.setVolume(10.f);

	this->skillsImpact[SkillType::HOLY_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/holy_strile_impact.wav");
	this->skillsImpact[SkillType::HOLY_STRIKE].second.setBuffer(this->skillsImpact[SkillType::HOLY_STRIKE].first);
	this->skillsImpact[SkillType::HOLY_STRIKE].second.setVolume(1.f);

	this->skillsImpact[SkillType::BLOOD_SPIKE].first.loadFromFile("Sounds/game_state/spell_sounds/blood_strike_impact.wav");
	this->skillsImpact[SkillType::BLOOD_SPIKE].second.setBuffer(this->skillsImpact[SkillType::BLOOD_SPIKE].first);
	this->skillsImpact[SkillType::BLOOD_SPIKE].second.setVolume(1.f);

	this->skillsImpact[SkillType::DARK_POSION].first.loadFromFile("Sounds/game_state/spell_sounds/dark_poison_impact.wav");
	this->skillsImpact[SkillType::DARK_POSION].second.setBuffer(this->skillsImpact[SkillType::DARK_POSION].first);
	this->skillsImpact[SkillType::DARK_POSION].second.setVolume(1.f);

	this->skillsImpact[SkillType::POISON_CLAW].first.loadFromFile("Sounds/game_state/spell_sounds/poison_claw_impact.wav");
	this->skillsImpact[SkillType::POISON_CLAW].second.setBuffer(this->skillsImpact[SkillType::POISON_CLAW].first);
	this->skillsImpact[SkillType::POISON_CLAW].second.setVolume(1.f);

	this->skillsImpact[SkillType::THUNDER_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/thunder_strike_impact.wav");
	this->skillsImpact[SkillType::THUNDER_STRIKE].second.setBuffer(this->skillsImpact[SkillType::THUNDER_STRIKE].first);
	this->skillsImpact[SkillType::THUNDER_STRIKE].second.setVolume(1.f);

	this->skillsImpact[SkillType::FIRE_EXPLOSION].first.loadFromFile("Sounds/game_state/spell_sounds/fire_explosion_impact.wav");
	this->skillsImpact[SkillType::FIRE_EXPLOSION].second.setBuffer(this->skillsImpact[SkillType::FIRE_EXPLOSION].first);
	this->skillsImpact[SkillType::FIRE_EXPLOSION].second.setVolume(1.f);
}

//Constructor
EnemySoundBox::EnemySoundBox() noexcept
{
	this->initSound();
}

EnemySoundBox::~EnemySoundBox()
{
}

//Functions
void EnemySoundBox::playSound(const SkillType& sound)
{
	this->skillsImpact[sound].second.play();
}

void EnemySoundBox::playSound(const std::string& sound)
{
	this->hit[sound].second.play();
}
