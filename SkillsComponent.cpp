#include "stdafx.h"
#include "SkillsComponent.h"

#define _SKILLS_COMPONENT_USE_SKILL_CHECK this->keyTime >= this->keyTimeMax && this->statsComponent.mp > 0

#define _SKILLS_COMPONENT_SET_SKILL_POSITION this->skillTextures[playerSkills[currentRender].first].first.setPosition(skill_position.x - 100, skill_position.y - 150);\
										     this->skillsEndingSprite.first.setPosition(skill_position.x - 100, skill_position.y - 150);\
											 this->damageArea.setPosition(skill_position.x - 300, skill_position.y - 300)

//Init fuctions
inline void SkillsComponent::initSounds()
{
	//Loading sounds
	this->sounds[SkillType::BUFF].first.loadFromFile("Sounds/game_state/spell_sounds/buff.wav");
	this->sounds[SkillType::BUFF].second.setBuffer(this->sounds[SkillType::BUFF].first);
	this->sounds[SkillType::BUFF].second.setVolume(5.f);

	this->sounds[SkillType::THUNDER_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/thunder_strike.wav");
	this->sounds[SkillType::THUNDER_STRIKE].second.setBuffer(this->sounds[SkillType::THUNDER_STRIKE].first);
	this->sounds[SkillType::THUNDER_STRIKE].second.setVolume(4.f);

	this->sounds[SkillType::FIRE_EXPLOSION].first.loadFromFile("Sounds/game_state/spell_sounds/fire_explosion.wav");
	this->sounds[SkillType::FIRE_EXPLOSION].second.setBuffer(this->sounds[SkillType::FIRE_EXPLOSION].first);
	this->sounds[SkillType::FIRE_EXPLOSION].second.setVolume(3.f);

	this->sounds[SkillType::POISON_CLAW].first.loadFromFile("Sounds/game_state/spell_sounds/poison_claw.wav");
	this->sounds[SkillType::POISON_CLAW].second.setBuffer(this->sounds[SkillType::POISON_CLAW].first);
	this->sounds[SkillType::POISON_CLAW].second.setVolume(3.f);

	this->sounds[SkillType::BLOOD_SPIKE].first.loadFromFile("Sounds/game_state/spell_sounds/blood_strike.wav");
	this->sounds[SkillType::BLOOD_SPIKE].second.setBuffer(this->sounds[SkillType::BLOOD_SPIKE].first);
	this->sounds[SkillType::BLOOD_SPIKE].second.setVolume(2.f);

	this->sounds[SkillType::DARK_POSION].first.loadFromFile("Sounds/game_state/spell_sounds/dark_poision.wav");
	this->sounds[SkillType::DARK_POSION].second.setBuffer(this->sounds[SkillType::DARK_POSION].first);
	this->sounds[SkillType::DARK_POSION].second.setVolume(3.f);

	this->sounds[SkillType::DARK_BOLT].first.loadFromFile("Sounds/game_state/spell_sounds/dark_bolt.wav");
	this->sounds[SkillType::DARK_BOLT].second.setBuffer(this->sounds[SkillType::DARK_BOLT].first);
	this->sounds[SkillType::DARK_BOLT].second.setVolume(3.f);

	this->sounds[SkillType::HOLY_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/holy_strike.wav");
	this->sounds[SkillType::HOLY_STRIKE].second.setBuffer(this->sounds[SkillType::HOLY_STRIKE].first);
	this->sounds[SkillType::HOLY_STRIKE].second.setVolume(2.f);

	this->sounds[SkillType::LIGHTNING_STRIKE].first.loadFromFile("Sounds/game_state/spell_sounds/lightning_strike.wav");
	this->sounds[SkillType::LIGHTNING_STRIKE].second.setBuffer(this->sounds[SkillType::LIGHTNING_STRIKE].first);
	this->sounds[SkillType::LIGHTNING_STRIKE].second.setVolume(2.f);

	this->sounds[SkillType::POTION].first.loadFromFile("Sounds/game_state/spell_sounds/potion.wav");
	this->sounds[SkillType::POTION].second.setBuffer(this->sounds[SkillType::POTION].first);
	this->sounds[SkillType::POTION].second.setVolume(3.f);

	//Init volumes
	for (auto& el : this->sounds)
	{
		this->soundsVolumes[el.first] = el.second.second.getVolume();
	}
}

inline void SkillsComponent::initAllSkills()
{
	//SKill damage radius
	this->damageArea.setRadius(300.f);
	this->damageArea.setFillColor(sf::Color::Transparent);
	this->damageArea.setOutlineThickness(1.f);
	this->damageArea.setOutlineColor(sf::Color::Red);

	//Skills
	this->allSkills.resize(this->skillsSize);
	this->playerSkills.resize(5);

	this->playerSkills[4].first = SkillType::BUFF;

	this->allSkills[0].first = SkillType::THUNDER_STRIKE;
	this->allSkills[1].first = SkillType::DARK_BOLT;
	this->allSkills[2].first = SkillType::POISON_CLAW;
	this->allSkills[3].first = SkillType::DARK_POSION;
	this->allSkills[4].first = SkillType::BLOOD_SPIKE;
	this->allSkills[5].first = SkillType::FIRE_EXPLOSION;
	this->allSkills[6].first = SkillType::LIGHTNING_STRIKE;
	this->allSkills[7].first = SkillType::HOLY_STRIKE;

	for (auto& el : this->allSkills)
	{
		el.second = 1;
	}

	//Items
	this->healthPotions.first   = HEALTH;
	this->manaPotions.first     = MANA;

	this->healthPotions.second  = 3;
	this->manaPotions.second    = 3;
}

inline void SkillsComponent::initAllAnimations()
{
	//Init textures
	this->skillTextures[SkillType::THUNDER_STRIKE].second.loadFromFile("Textures/Animations/thunder/thunder_strike.png");
	this->skillTextures[SkillType::DARK_BOLT].second.loadFromFile("Textures/Animations/dark/dark_bolt.png");
	this->skillTextures[SkillType::POISON_CLAW].second.loadFromFile("Textures/Animations/poison/poison_claw.png");
	this->skillTextures[SkillType::DARK_POSION].second.loadFromFile("Textures/Animations/dark/dark_poison.png");
	this->skillTextures[SkillType::BLOOD_SPIKE].second.loadFromFile("Textures/Animations/blood/blood.png");
	this->skillTextures[SkillType::FIRE_EXPLOSION].second.loadFromFile("Textures/Animations/fire/fire.png");
	this->skillTextures[SkillType::LIGHTNING_STRIKE].second.loadFromFile("Textures/Animations/thunder/Lightning.png");
	this->skillTextures[SkillType::HOLY_STRIKE].second.loadFromFile("Textures/Animations/holy/holy_strike.png");
	this->skillTextures[SkillType::BUFF].second.loadFromFile("Textures/animations/buff.png");

	this->potionSprite.second.loadFromFile("Textures/Animations/healing.png");
	this->potionSprite.first.setScale(3.f, 3.f);

	this->skillsEndingSprite.second.loadFromFile("Textures/Animations/hit/circle02.png");
	this->skillsEndingSprite.first.setScale(3.f, 3.f);

	//Init animations
	this->potionAnimation = AnimationComponent(&this->potionSprite.first, &this->potionSprite.second);
	this->skillsEndingAnimation = AnimationComponent(&this->skillsEndingSprite.first, &this->skillsEndingSprite.second);
	this->skillsAnimations[SkillType::BUFF] = AnimationComponent(&this->skillTextures[SkillType::BUFF].first, &this->skillTextures[SkillType::BUFF].second);

	SkillType type;
	for (int i = 0; i < this->skillsSize; ++i)
	{
		type = this->allSkills[i].first;
		this->skillsAnimations[type] = AnimationComponent(&this->skillTextures[type].first, &this->skillTextures[type].second);
	}


	//Add animations
	//Potion animations
	this->potionAnimation.addAnimation("USE1", 1, 0, 3, 0, 128, 128, 11.f);
	this->potionAnimation.addAnimation("USE2", 0, 1, 3, 1, 128, 128, 11.f);
	this->potionAnimation.addAnimation("USE3", 0, 2, 3, 2, 128, 128, 11.f);
	this->potionAnimation.addAnimation("USE4", 0, 3, 2, 3, 128, 128, 11.f);

	//Skills ending animation
	this->skillsEndingAnimation.addAnimation("USE1", 0, 0, 3, 0, 64, 64, 11.f);
	this->skillsEndingAnimation.addAnimation("USE2", 0, 1, 3, 1, 64, 64, 11.f);

	//Skills animation
	this->skillsAnimations[SkillType::THUNDER_STRIKE].addAnimation("USE", 0, 0, 11, 0, 64, 64, 10.f);
	this->skillTextures[SkillType::THUNDER_STRIKE].first.setScale(5.f, 5.f);

	this->skillsAnimations[SkillType::DARK_BOLT].addAnimation("USE", 0, 0, 10, 0, 64, 88, 10.f);
	this->skillTextures[SkillType::DARK_BOLT].first.setScale(4.f, 4.f);

	this->skillsAnimations[SkillType::POISON_CLAW].addAnimation("USE", 0, 0, 30, 0, 96, 96, 6.f);
	this->skillTextures[SkillType::POISON_CLAW].first.setScale(4.f, 4.f);

	this->skillsAnimations[SkillType::DARK_POSION].addAnimation("USE", 0, 0, 13, 0, 48, 64, 8.f);
	this->skillTextures[SkillType::DARK_POSION].first.setScale(5.f, 5.f);

	this->skillsAnimations[SkillType::BLOOD_SPIKE].addAnimation("USE", 0, 0, 17, 0, 48, 32, 8.f);
	this->skillTextures[SkillType::BLOOD_SPIKE].first.setScale(5.5f, 5.5f);

	this->skillsAnimations[SkillType::FIRE_EXPLOSION].addAnimation("USE", 0, 0, 17, 0, 48, 48, 10.f);
	this->skillTextures[SkillType::FIRE_EXPLOSION].first.setScale(6.f, 6.f);

	this->skillsAnimations[SkillType::LIGHTNING_STRIKE].addAnimation("USE", 0, 0, 9, 0, 64, 128, 8.f);
	this->skillTextures[SkillType::LIGHTNING_STRIKE].first.setScale(3.5f, 3.5f);

	this->skillsAnimations[SkillType::HOLY_STRIKE].addAnimation("USE", 0, 0, 15, 0, 48, 48, 8.f);
	this->skillTextures[SkillType::HOLY_STRIKE].first.setScale(5.f, 5.f);

	this->skillsAnimations[SkillType::BUFF].addAnimation("USE", 0, 0, 5, 0, 32, 32, 15.f);
	this->skillTextures[SkillType::BUFF].first.setScale(5.f, 5.f);
}

inline void SkillsComponent::initPopUpText()
{
	//Skills pop up text
	this->popUpKeysMap[SkillType::BUFF] = "BUFF";
	this->popUpTextComponent.addText(this->popUpKeysMap[SkillType::BUFF], sf::Color::Red, 35);

	//this->popUpKeysMap[SkillType::THUNDER_STRIKE] = "THUNDER STRIKE";
	//this->popUpTextComponent.addText(this->popUpKeysMap[SkillType::THUNDER_STRIKE], sf::Color::Yellow, 35);


	//Potions pop up text
	this->mpPopUpKey.first = MANA;
	this->mpPopUpKey.second = "MP: +3";

	this->hpPopUpKey.first = HEALTH;
	this->hpPopUpKey.second = "HP: +3";

	this->popUpTextComponent.addText(this->hpPopUpKey.second, sf::Color::Green, 35);
	this->popUpTextComponent.addText(this->mpPopUpKey.second, sf::Color(102, 178, 255), 35);
}

//Update functions
inline void SkillsComponent::updateClock(const float& dt)
{
	//Update key time
	this->keyTime       += 10.f * dt;
	this->potionKeyTime += 10.f * dt;

	//Skills duration
	this->time = skillTimer.getElapsedTime().asSeconds();
}

inline void SkillsComponent::updatePopUpText(const std::string& key)
{
	this->popUpTextKey = key;
	this->popUpTextComponent.prepareText(this->popUpTextKey);
	this->popUpTextTimer.restart();
	this->showPopUpText = true;
}

//Render functions
inline void SkillsComponent::renderPopUpText(sf::RenderTarget& target, const sf::Vector2f& player_position)
{
	//Render pop up text
	if (this->showPopUpText)
	{
		if (this->popUpTextTimer.getElapsedTime().asSeconds() > this->popUpTextComponent.getpTextExpireTime())
		{
			this->showPopUpText = false;
			this->popUpTextComponent.resetText(this->popUpTextKey);
		}
		else
		{
			this->popUpTextComponent.popUpText(target, this->popUpTextKey, player_position);
		}
	}
}

//Core functions
inline void SkillsComponent::useSkill(const SkillType& skill_type)
{
	this->statsComponent.loseMP(1);
}

inline void SkillsComponent::playSkillSound(const SkillType& type)
{
	this->sounds[type].second.play();
}

//Constructor
SkillsComponent::SkillsComponent(StatsComponent& statsComponent, const sf::Font& font, bool& isUsingSkill, SkillType& currentSkillType,
	int& currentSkillDamage, bool& isBuffed, bool& castingSpell) noexcept
	:
	statsComponent(statsComponent),
	popUpTextComponent(font),

	currentRender(-1), playAnimation(false), usingPotion(false), usingBuff(false),      isBuffed(isBuffed), castingSpell(castingSpell),
	keyTime(0.f),      keyTimeMax(15.f),     potionKeyTime(0.f), potionKeyTimeMax(5.f), buffDuration(5.f),  buffCooldown(15.f),

	skillsSize(8), usingSkill(isUsingSkill), currentSkillType(currentSkillType), currentSkillDamage(currentSkillDamage)
{
	std::thread initSoundsThread     (&SkillsComponent::initAllAnimations, this);  //Thrad for loading textures and initing animations
	std::thread initAnimationsThread (&SkillsComponent::initSounds, this);         //Thread for loading sounds

	this->initAllSkills();
	this->initPopUpText();

	initSoundsThread.join();
	initAnimationsThread.join();
}

SkillsComponent::~SkillsComponent()
{
}

//Accessors
const int& SkillsComponent::getBuffMaxLevel() const
{
	return this->buffMaxLevel;
}

const int& SkillsComponent::getBuffLevel() const
{
	return this->buffLevel;
}

const std::vector<std::pair<SkillType, int>>& SkillsComponent::getPlayerSkills()
{
	return this->playerSkills;
}

const sf::CircleShape& SkillsComponent::getDamageArea()
{
	return this->damageArea;
}

const bool SkillsComponent::getKeyTime() const
{
	return this->keyTime >= this->keyTimeMax;
}

const bool SkillsComponent::getBuffKeyTime() const
{
	return this->buffTimer.getElapsedTime().asSeconds() > this->buffCooldown;
}

int& SkillsComponent::getMpPotions()
{
	return this->manaPotions.second;
}

int& SkillsComponent::getHpPotions()
{
	return this->healthPotions.second;
}

//Sounds functions 
void SkillsComponent::setSoundsVolume(const float& volume)
{
	for (auto& el : this->sounds)
	{
		el.second.second.setVolume(volume);
	}
}

void SkillsComponent::increaseSoundsVolume()
{
	for (auto& el : this->sounds)
	{
		el.second.second.setVolume(el.second.second.getVolume() + (this->soundsVolumes[el.first] * SKILLS_SOUNDS_VOLUME_MODIFIER / 100.f));
	}

}

void SkillsComponent::decreaseSoundsVolume()
{
	for (auto& el : this->sounds)
	{
		el.second.second.setVolume(el.second.second.getVolume() - (this->soundsVolumes[el.first] * SKILLS_SOUNDS_VOLUME_MODIFIER / 100.f));

		if (el.second.second.getVolume() < 0)
		{
			el.second.second.setVolume(0);
		}
	}
}

void SkillsComponent::pauseSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() == sf::Sound::Status::Playing)
		{
			el.second.second.pause();
		}
	}
}

void SkillsComponent::resumeSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() == sf::Sound::Status::Paused)
		{
			el.second.second.play();
		}
	}
}

//Public Functions
void SkillsComponent::addPotion(const Potions& potion_type)
{
	switch (potion_type)
	{
	case HEALTH:
		++this->healthPotions.second;
		break;
	case MANA:
		++this->manaPotions.second;
	default:
		break;
	}
}

void SkillsComponent::usePotion(const Potions& potion_type)
{
	switch (potion_type)
	{
	case HEALTH:
		--this->healthPotions.second;
		this->statsComponent.gainHP(3);
		break;
	case MANA:
		--this->manaPotions.second;
		this->statsComponent.gainMP(3);
		break;
	default:
		break;
	}

	this->playSkillSound(SkillType::POTION);
}

void SkillsComponent::addSkill(const SkillType& skill_type, const short& slot)
{
	this->playerSkills[slot].first = skill_type;

	this->playerSkills[slot].second = 1;
}

void SkillsComponent::upgradeSkill(const SkillType& skill_type)
{
	if (skill_type == SkillType::BUFF)
	{
		this->buffDuration += 1.f;
		this->buffCooldown -= 0.5f;
		++this->buffLevel;

		if (this->buffLevel == this->buffMaxLevel)
		{
			this->buffCritRate += 2.f;
		}
	}
	else
	{
		std::find_if(this->playerSkills.begin(), this->playerSkills.end(), [&skill_type](const std::pair<SkillType, int>& temp)
			{
				return temp.first == skill_type;
			}).operator*().second++;
	}
}

void SkillsComponent::updatePlayerBuff(const float& dt, const sf::Vector2f& player_position)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && this->buffTimer.getElapsedTime().asSeconds() > this->buffCooldown && this->statsComponent.mp != 0)
	{
		this->statsComponent.gainMP(this->buffLevel);
		this->statsComponent.gainHP(this->buffLevel);

		this->isBuffed = true;
		this->usingBuff = true;
		this->buffTimer.restart();

		this->statsComponent.critRate   += this->buffCritRate;
		this->statsComponent.missChance += this->buffMissChance;

		//Sound
		this->playSkillSound(SkillType::BUFF);

		//Pop up text
		this->updatePopUpText(this->popUpKeysMap[SkillType::BUFF]);
	}

	if (this->isBuffed)
	{
		if (this->buffTimer.getElapsedTime().asSeconds() > this->buffDuration)
		{
			this->isBuffed = false;

			this->statsComponent.critRate -= this->buffCritRate;
			this->statsComponent.missChance -= this->buffMissChance;

			this->buffTimer.restart();
		}
	}
}

void SkillsComponent::update(const float& dt, const sf::Vector2f& skill_position, const sf::Vector2f& player_position)
{
	this->updateClock(dt);
	this->updatePlayerBuff(dt, player_position);

	//Skills
	this->usingSkill = false;

	if (_SKILLS_COMPONENT_USE_SKILL_CHECK)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			currentRender = 0;

			_SKILLS_COMPONENT_SET_SKILL_POSITION;

			this->playAnimation = true;
			this->castingSpell = true;

			skillTimer.restart();

			//Sound
			this->playSkillSound(this->playerSkills[currentRender].first);

			//Pop up text
			this->updatePopUpText(this->popUpKeysMap[this->playerSkills[currentRender].first]);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			currentRender = 1;

			_SKILLS_COMPONENT_SET_SKILL_POSITION;

			this->playAnimation = true;
			this->castingSpell = true;

			this->playAnimation = true;
			skillTimer.restart();

			//Sound
			this->playSkillSound(this->playerSkills[currentRender].first);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			currentRender = 2;

			_SKILLS_COMPONENT_SET_SKILL_POSITION;

			this->playAnimation = true;
			this->castingSpell = true;

			skillTimer.restart();

			//Sound
			this->playSkillSound(this->playerSkills[currentRender].first);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			currentRender = 3;

			_SKILLS_COMPONENT_SET_SKILL_POSITION;

			this->playAnimation = true;
			this->castingSpell = true;

			skillTimer.restart();

			//Sound
			this->playSkillSound(this->playerSkills[currentRender].first);
		}
	}

	//Potion
	if (this->potionKeyTime >= this->potionKeyTimeMax)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->manaPotions.second != 0)
		{
			this->usingPotion = true;
			this->usePotion(MANA);

			//Pop up text
			this->updatePopUpText(this->mpPopUpKey.second);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->healthPotions.second != 0)
		{
			this->usingPotion = true;
			this->usePotion(HEALTH);

			//Pop up text
			this->updatePopUpText(this->hpPopUpKey.second);
		}
	}

	//Potion animations
	if (this->usingPotion)
	{
		this->potionSprite.first.setPosition(player_position.x - 180, player_position.y - 200);
		this->potionKeyTime = 0;
		if (this->potionAnimation.play("USE1", dt, true))
		{
			if (this->potionAnimation.play("USE2", dt, true))
			{
				if (this->potionAnimation.play("USE3", dt, true))
				{
					if (this->potionAnimation.play("USE4", dt, true))
					{
						this->usingPotion = false;
					}
				}
			}

		}
	}

	//Using buff
	if (this->usingBuff)
	{
		this->skillTextures[SkillType::BUFF].first.setPosition(player_position.x - 90.f, player_position.y - 90.f);

		if (this->skillsAnimations[SkillType::BUFF].play("USE", dt, true))
		{
			this->usingBuff = false;
		}
	}

	//Skills animation
	if (this->playAnimation && this->playerSkills[currentRender].first != SkillType::EMPTY)
	{
		this->keyTime = 0;

		if (this->skillsAnimations[this->playerSkills[currentRender].first].play("USE", dt, true))
		{
			this->playAnimation = false;

			//Player variables
			this->usingSkill = true;

			this->currentSkillType = this->playerSkills[currentRender].first;
			this->statsComponent.currentSkillDamage = this->playerSkills[currentRender].second;

			//Using skill
			this->useSkill(playerSkills[currentRender].first);
			this->currentRender = -1;
		}
	}
}

void SkillsComponent::render(sf::RenderTarget& target, const sf::Vector2f& player_position)
{
	if (this->currentRender != -1)
	{
		target.draw(this->skillTextures[playerSkills[currentRender].first].first);
	}
	if (this->usingPotion)
	{
		target.draw(this->potionSprite.first);
	}
	if (this->usingBuff)
	{
		target.draw(this->skillTextures[SkillType::BUFF].first);
	}

	this->renderPopUpText(target, player_position);
}