#include "stdafx.h"
#include "Player.h"

#define SPTIRES_SETSCALE_LEFT this->sprite.setOrigin(50.f, 0.f);\
							this->sprite.setScale(-2.8f, 2.8f);\
							this->sprites[0].second.setPosition(this->getCenter().x - 220, this->getCenter().y - 150);\
							this->damageRange.setPosition(this->getCenter().x - 180, this->getCenter().y - 140)
							
#define SPTIRES_SETSCALE_RIGHT this->sprite.setOrigin(0.f, 0.f);\
							this->sprite.setScale(2.8f, 2.8f);\
							this->sprites[0].second.setPosition(this->getCenter().x - 50, this->getCenter().y - 150);\
							this->damageRange.setPosition(this->getCenter().x + 30, this->getCenter().y - 140)
							

//Initialasation functions
inline void Player::initVariables()
{
	//Player damage range
	this->damageRange.setSize(sf::Vector2f(150, 250));
	this->damageRange.setOutlineThickness(1.f);
	this->damageRange.setOutlineColor(sf::Color::Red);
	this->damageRange.setFillColor(sf::Color::Transparent);

	//Player hit range
	this->hitRange.setPosition(this->getCenter().x - 200, this->getCenter().y - 200);
	this->hitRange.setRadius(80.f);
	this->hitRange.setOutlineThickness(1.f);
	this->hitRange.setOutlineColor(sf::Color::White);
	this->hitRange.setFillColor(sf::Color::Transparent);

	//Player sprites
	this->sprites.resize(3);
	this->hitAnimations.resize(3);

	this->sprites[0].first.loadFromFile("Textures/animations/hit/magick_hit.png");
	this->sprites[0].second.setScale(4.f, 4.f);

	this->sprites[1].first.loadFromFile("Textures/animations/hit/take_hit.png");
	this->sprites[1].second.setScale(4.f, 4.f);

	this->sprites[2].first.loadFromFile("Textures/animations/hit/hit03.png");
	this->sprites[2].second.setScale(3.f, 3.f);
}

inline void Player::createAnimationComponent(sf::Texture& texture_sheet)
{
	//Regular texture
	for (int i = 0; i < this->hitAnimations.size(); ++i)
	{
		this->hitAnimations[i] = { &this->sprites[i].second, &this->sprites[i].first };
	}

	this->addAnimations();
}

inline void Player::initComponents(sf::Texture& texture_sheet)
{
	this->createHitboxComponent(this->sprite, 45.f, 48.f, 55.f, 55.f);
	this->createMovementComponent(270.f, 1200.f, 400.f);
	this->createAnimationComponent(texture_sheet);
}

inline void Player::addAnimations()
{
	//Regular sprite
	this->animationComponent.addAnimation("IDLE", 0, 0, 3, 0, 50, 40, 13.f);
	this->animationComponent.addAnimation("MOVE", 0, 1, 5, 1, 50, 37, 9.f);
	this->animationComponent.addAnimation("DASH", 1, 8, 4, 8, 50, 37, 9.f);
	this->animationComponent.addAnimation("DEATH", 0, 9, 4, 9, 50, 37, 9.f);

	this->animationComponent.addAnimation("ATTACK_FIRST", 0, 4, 8, 4, 50, 37, 8.f);
	this->animationComponent.addAnimation("CAST_SPELL", 0, 3, 8, 3, 50, 37, 10.f);

	//Hit sprites
	this->hitAnimations[0].addAnimation("HIT", 0, 0, 32, 0, 64, 64, 1.6f);
	this->hitAnimations[1].addAnimation("TAKE_HIT", 0, 0, 9, 0, 64, 24, 6.f);

	this->hitAnimations[2].addAnimation("TAKE_HIT1", 0, 0, 4, 0, 64, 64, 3.f);
	this->hitAnimations[2].addAnimation("TAKE_HIT2", 0, 1, 4, 1, 64, 64, 3.f);
}

inline void Player::initSounds()
{
	this->soundComponent.addWalkingSound("Sounds/game_state/player/walking.wav");
	this->soundComponent.addRunningSound("Sounds/game_state/player/running.wav");
}

//Sound functions
inline void Player::updateSound()
{
	//Pause or unpause movement sound
	if (this->movementComponent.getState(IDLE))
	{
		this->soundComponent.pauseMovementSound();
	}
	else
	{
		this->soundComponent.unpauseMovementSound();
	}

	//Change movement sound if player is buffed
	if (this->isBuffed)
	{
		this->soundComponent.changeMovementSound(true);
	}
	else
	{
		this->soundComponent.changeMovementSound(false);
	}

	//Decrease movement sound if isAttacking
	if (this->isAttacking)
	{
		this->soundComponent.changeMovementVolume(false);
	}
	else
	{
		this->soundComponent.changeMovementVolume(true);
	}
}

//Constructor
Player::Player(const float& x, const float& y, sf::Texture& texture_sheet, const sf::Font& font, bool& isBuffed) noexcept
	: currentHitAnimation(0), font(font), isBuffed(isBuffed),
	statsComponent(1),
	animationComponent(&this->sprite, &texture_sheet),
	skillsComponent(this->statsComponent, this->isUsingSkill, this->currentSkilltype, this->currentskillDamage, this->isBuffed),
	moveKey("MOVE"), dashKey("DASH"), currentKey(&moveKey)
{
	this->initVariables();
	this->initComponents(texture_sheet);
	this->setPosition(x, y);
	this->initSounds();

	this->sprite.setScale(2.8f, 2.8f);
}

Player::~Player()
{
}

//Accessors
const SkillType& Player::getUsingSkilltype()
{
	return this->currentSkilltype;
}

const int& Player::getUsingSkilldamage()
{
	return this->currentskillDamage;
}

const sf::Font& Player::getFont()
{
	return this->font;
}

void Player::setPlayerGUI(PlayerGUI& playerGUI)
{
	this->playerGUI = &playerGUI;
}

const bool& Player::usingSkill()
{
	return this->isUsingSkill;
}

const bool& Player::isDealingDmg()
{
	return this->dealDMG;
}

StatsComponent* Player::getStatsComponent()
{
	return &this->statsComponent;
}

SkillsComponent* Player::getSkillComponent()
{
	return &this->skillsComponent;
}

const sf::CircleShape& Player::getHitRange()
{
	return this->hitRange;
}

const sf::RectangleShape& Player::getDamageRange()
{
	return this->damageRange;
}

//Stats functions
void Player::gainEXP(const unsigned& exp)
{
	this->statsComponent.gainEXP(exp);
}

void Player::gainHP(const int& hp)
{
	this->statsComponent.gainHP(hp);
}

void Player::loseHP(const int& hp)
{
	this->statsComponent.loseHP(hp);
	this->isTakingHit = true;
}

void Player::gainMP(const int& mp)
{
	this->statsComponent.gainMP(mp);
}

void Player::loseMP(const int& mp)
{
	this->statsComponent.loseMP(mp);
}

void Player::gainArmor(const int& armor)
{
	this->statsComponent.gainArmor(armor);
}

void Player::gainCrystals(const int& crystals)
{
	this->statsComponent.gainCrystals(crystals);
}

void Player::loseCrystals(const int& crystals)
{
	this->statsComponent.loseCrystals(crystals);
}

void Player::gainCoins(const int& coins)
{
	this->statsComponent.gainCoins(coins);
}

void Player::loseCoins(const int& coins)
{
	this->statsComponent.loseCoins(coins);
}

void Player::addItem(const Items& item)
{
	this->statsComponent.addItem(item);
}

void Player::addPotions(const Potions& potion_type)
{
	this->skillsComponent.addPotion(potion_type);
}

void Player::usePotions(const Potions& potion_type)
{
	this->skillsComponent.usePotion(potion_type);
}

//Functions
void Player::pauseSounds()
{
	this->soundComponent.pauseMovementSound();
}

inline void Player::updateAttack(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->dealDMG = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isAttacking = true;
		this->isHit = true;
	}
	if (this->isAttacking)
	{
		if (this->damageTimer.getElapsedTime().asSeconds() > 1.f)
		{
			this->dealDMG = true;
			this->damageTimer.restart();
		}
		else
		{
			this->dealDMG = false;
		}

		if (mouse_pos_view.x < this->hitboxComponent.getPositionHitbox().x)
		{
			SPTIRES_SETSCALE_LEFT;
		}
		else
		{
			SPTIRES_SETSCALE_RIGHT;
		}
		if (this->animationComponent.play("ATTACK_FIRST", dt, true))
		{
			this->isAttacking = false;
		}
	}

	if (this->isHit)
	{
		if (this->hitAnimations[currentHitAnimation].play("HIT", dt, true))
		{
			this->isHit = false;
		}
	}
	if (this->isTakingHit)
	{
		if (this->statsComponent.armor != 0)
		{
			this->sprites[2].second.setPosition(this->getCenter().x - 120, this->getCenter().y - 100);

			if (this->hitAnimations[2].play("TAKE_HIT1", dt, true))
			{
				if (this->hitAnimations[2].play("TAKE_HIT2", dt, true))
				{
					this->isTakingHit = false;
				}
			}
		}
		else
		{
			this->sprites[1].second.setPosition(this->getCenter().x - 100, this->getCenter().y - 70);

			if (this->hitAnimations[1].play("TAKE_HIT", dt, true))
			{
				this->isTakingHit = false;
			}
		}
	}

}

inline void Player::updateAnimations(const float& dt, sf::Vector2f mouse_pos_view)
{
	if (this->isBuffed)
	{
		this->currentKey = &this->dashKey;
	}
	else
	{
		this->currentKey = &this->moveKey;
	}	

	if (this->movementComponent.getState(IDLE))
	{
		if (mouse_pos_view.x < this->hitboxComponent.getPositionHitbox().x)
		{
			SPTIRES_SETSCALE_LEFT;
		}
		else
		{
			SPTIRES_SETSCALE_RIGHT;
		}

		this->animationComponent.play("IDLE", dt);
	}
	else if (this->movementComponent.getState(MOVING_RIGHT))
	{
		SPTIRES_SETSCALE_RIGHT;

		//Animation
		this->animationComponent.play(*this->currentKey, dt, this->movementComponent.getVelocity().x, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVING_LEFT))
	{
		SPTIRES_SETSCALE_LEFT;

		//Animation
		this->animationComponent.play(*this->currentKey, dt, this->movementComponent.getVelocity().x, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVE_UP))
	{
		//Animation
		this->animationComponent.play(*this->currentKey, dt, this->movementComponent.getVelocity().y, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVE_DOWN))
	{
		//Animation
		this->animationComponent.play(*this->currentKey, dt, this->movementComponent.getVelocity().y, this->movementComponent.getMaxVelocity());
	}
}

void Player::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->hitRange.setPosition(this->getCenter().x - 80, this->getCenter().y - 80);

	this->updateSound();
	this->movementComponent.update(dt);
	this->updateAnimations(dt, mouse_pos_view);
	this->updateAttack(dt, mouse_pos_view);
	this->skillsComponent.update(dt, mouse_pos_view, this->getCenter());
	this->hitboxComponent.update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());

		target.draw(this->sprite, shader);
		if (this->isHit)
		{
			target.draw(this->sprites[currentHitAnimation].second);
		}

		if (this->isTakingHit && this->statsComponent.armor != 0)
		{
			target.draw(this->sprites[2].second);
		}
		else if (this->isTakingHit && this->statsComponent.armor == 0)
		{
			target.draw(this->sprites[1].second);
		}

		this->skillsComponent.render(target);
	}
	else
	{
		target.draw(this->sprite);
	}
	
	//this->hitboxComponent.render(target);
	//target.draw(this->hitRange);
}

