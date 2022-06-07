#include "stdafx.h"
#include "MageEnemy.h"

//Init functions
inline void MageEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case MageEnemyType::DARK_MAGE:
		this->offsetX = 0;
		this->offsetY = 0;

		this->sprite.setScale(2.f, 2.f);
		
		//Attack time
		this->attackCountMAX = 1;
		this->attackColdown = 2.f;

		//Resistance
		this->skillReistance = SkillType::DARK_POSION;

		//Init spell cast range
		this->castR = 500.f;
		this->ineerR = 350.f;

		this->castRange.setRadius(this->castR);
		this->castRange.setFillColor(sf::Color::Transparent);
		this->castRange.setOutlineColor(sf::Color::Red);
		this->castRange.setOutlineThickness(1.f);

		this->innerRange.setRadius(this->ineerR);
		this->innerRange.setFillColor(sf::Color::Transparent);
		this->innerRange.setOutlineColor(sf::Color::Green);
		this->innerRange.setOutlineThickness(1.f);

		//Init components
		this->createHitboxComponent(this->sprite, 150.f, 150.f, 150.f, 150.f);
		this->createMovementComponent(120.f, 750.f, 150.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(230.f, 0.f);
			sprite.setScale(-2.f, 2.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(2.f, 2.f);
		};
		break;

	case MageEnemyType::FIRE_MAGE:
		this->offsetX = 70;
		this->offsetY = 70;

		this->sprite.setScale(3.f, 3.f);

		//Attack time
		this->attackCountMAX = 2;
		this->attackColdown = 3.f;

		//Resistance
		this->skillReistance = SkillType::FIRE_EXPLOSION;

		//Init spell cast range
		this->castR = 200.f;
		this->ineerR = 170.f;

		this->castRange.setRadius(this->castR);
		this->castRange.setFillColor(sf::Color::Transparent);
		this->castRange.setOutlineColor(sf::Color::Red);
		this->castRange.setOutlineThickness(1.f);

		this->innerRange.setRadius(this->ineerR);
		this->innerRange.setFillColor(sf::Color::Transparent);
		this->innerRange.setOutlineColor(sf::Color::Green);
		this->innerRange.setOutlineThickness(1.f);

		//Init components
		this->createHitboxComponent(this->sprite, 150.f, 150.f, 150.f, 150.f);
		this->createMovementComponent(120.f, 750.f, 150.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(160.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		break;

	case MageEnemyType::WIZZARD:
		this->offsetX = 0;
		this->offsetY = 0;

		this->sprite.setScale(1.5f, 1.5f);

		//Attack time
		this->attackCountMAX = 2;
		this->attackColdown = 3.f;

		//Resistance
		this->skillReistance = SkillType::LIGHTNING_STRIKE;

		//Init spell cast range
		this->castR = 700.f;
		this->ineerR = 350.f;

		this->castRange.setRadius(this->castR);
		this->castRange.setFillColor(sf::Color::Transparent);
		this->castRange.setOutlineColor(sf::Color::Red);
		this->castRange.setOutlineThickness(1.f);

		this->innerRange.setRadius(this->ineerR);
		this->innerRange.setFillColor(sf::Color::Transparent);
		this->innerRange.setOutlineColor(sf::Color::Green);
		this->innerRange.setOutlineThickness(1.f);

		//Init components
		this->createHitboxComponent(this->sprite, 100.f, 100.f, 150.f, 150.f);
		this->createMovementComponent(100.f, 700.f, 120.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(230.f, 0.f);
			sprite.setScale(-1.5f, 1.5f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(1.5f, 1.5f);
		};
		break;
	default:
		break;
	}
}

inline void MageEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->addAnimations();
}

inline void MageEnemy::addAnimations()
{
	switch (this->type)
	{
	case MageEnemyType::DARK_MAGE:
		this->animationComponent.addAnimation("IDLE", 0, 1, 7, 1, 250, 250, 20.f);
		this->animationComponent.addAnimation("MOVE", 0, 1, 7, 1, 250, 250, 20.f);
		this->animationComponent.addAnimation("CAST", 0, 3, 15, 3, 250, 250, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 2, 2, 250, 250, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 0, 6, 0, 250, 250, 15.f);
		break;
	case MageEnemyType::FIRE_MAGE:
		this->animationComponent.addAnimation("IDLE", 0, 2, 7, 2, 150, 150, 20.f);
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 150, 150, 20.f);
		this->animationComponent.addAnimation("CAST", 0, 0, 7, 0, 150, 150, 15.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 3, 3, 150, 150, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 6, 1, 150, 150, 15.f);
		break;
	case MageEnemyType::WIZZARD:
		this->animationComponent.addAnimation("IDLE", 0, 3, 5, 3, 231, 190, 20.f);
		this->animationComponent.addAnimation("MOVE", 0, 4, 7, 4, 231, 190, 11.f);
		this->animationComponent.addAnimation("CAST", 0, 0, 7, 0, 231, 190, 15.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 3, 2, 231, 190, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 6, 1, 231, 190, 11.f);
		break;
	default:
		break;
	}
}

//Sound functions
inline void MageEnemy::playImpactSounds(const std::string& sound)
{
	this->soundBox.playSound(sound);
}

inline void MageEnemy::playSkillImpactSounds(const SkillType& type)
{
	this->soundBox.playSound(type);
}

//Update functions
inline void MageEnemy::updateAttack(const float& dt)
{
	if (this->player->getHitRange().getGlobalBounds().intersects(this->castRange.getGlobalBounds()) &&
		!this->player->getHitRange().getGlobalBounds().intersects(this->innerRange.getGlobalBounds()) && !this->isDead)
	{
		if (this->attackCount == this->attackCountMAX)
		{
			this->attackTimer.restart();
			this->attackCount = 0;
		}
		else if (this->attackColdown <= this->attackTimer.getElapsedTime().asSeconds() && !this->isAttaking)
		{
			this->isAttaking = true;
			++this->attackCount;
		}
	}

	if (this->isAttaking)
	{
		this->stopVelocity();

		if (this->animationComponent.play("CAST", dt, true))
		{
			if (this->player->getHitRange().getGlobalBounds().intersects(this->castRange.getGlobalBounds()))
			{
				this->player->loseHP(this->statsComponent.damagePhysical);
			}
			this->isAttaking = false;
		}
	}
}

inline void MageEnemy::updateMovement(const float& dt)
{
	//Ranges
	this->castRange.setPosition(this->getPosition().x - this->castR + offsetX, this->getPosition().y - this->castR + offsetY);
	this->innerRange.setPosition(this->getPosition().x - this->ineerR + offsetX, this->getPosition().y - this->ineerR + offsetY);

	//Inner range intersects
	if (this->player->getHitRange().getGlobalBounds().intersects(this->innerRange.getGlobalBounds()))
	{
		if (this->player->getPosition().x > this->getPosition().x)
		{
			this->move(-1.f, 0.f, dt);
		}
		else if (this->player->getPosition().x < this->getPosition().x)
		{
			this->move(1.f, 0.f, dt);
		}
		if (this->player->getPosition().y < this->getPosition().y)
		{
			this->move(0.f, 1.f, dt);
		}
		else if (this->player->getPosition().y > this->getPosition().y)
		{
			this->move(0, -1.f, dt);
		}
	}
	//Cast range intersects
	if (!this->player->getHitRange().getGlobalBounds().intersects(this->castRange.getGlobalBounds()))
	{
		if (this->player->getPosition().x > this->getPosition().x)
		{
			this->move(1.f, 0.f, dt);
		}
		else if (this->player->getPosition().x < this->getPosition().x)
		{
			this->move(-1.f, 0.f, dt);
		}
		if (this->player->getPosition().y < this->getPosition().y)
		{
			this->move(0.f, -1.f, dt);
		}
		else if (this->player->getPosition().y > this->getPosition().y)
		{
			this->move(0, 1.f, dt);
		}
	}

	//Set attack origin
	if (this->player->getHitRange().getGlobalBounds().intersects(this->castRange.getGlobalBounds()) &&
		!this->player->getHitRange().getGlobalBounds().intersects(this->innerRange.getGlobalBounds()))
	{
		if (this->player->getPosition().x > this->getPosition().x)
		{
			this->setOriginRight();
		}
		else if (this->player->getPosition().x < this->getPosition().x)
		{
			this->setOriginLeft();
		}
	}
}

inline void MageEnemy::updateAnimations(const float& dt)
{
	if (this->isTakingDamage)
	{
		this->stopVelocity();

		if (this->animationComponent.play("TAKE_HIT", dt, true))
		{
			this->isTakingDamage = false;
		}
	}

	//Player hit
	if (this->hitImpact)
	{
		this->takeHitSprite.second.setPosition(this->getPosition());

		if (this->takeHitAnimation.play("TAKE_HIT1", dt, true))
		{
			if (this->takeHitAnimation.play("TAKE_HIT2", dt, true))
			{
				this->hitImpact = false;
			}
		}
	}

	//Player crit
	if (this->critImpact)
	{
		this->critHitSprite.second.setPosition(this->getPosition().x - 20, this->getPosition().y - 100);

		if (this->critHitAnimation.play("CRIT", dt, true))
		{
			this->critImpact = false;
		}
	}

	//Plyaer skill
	if (this->skillImpact)
	{
		this->skillsImpactSprites[*this->playerUsingSkill].first.setPosition(
			this->getPosition().x - this->offsets[*this->playerUsingSkill],
			this->getPosition().y - this->offsets[*this->playerUsingSkill]);

		if (this->skillsImpactAnimations[*this->playerUsingSkill].play("SKILL_IMPACT", dt, true))
		{
			this->skillImpact = false;
		}
	}

	if (this->statsComponent.hp == 0)
	{
		this->stopVelocity();
		if (this->animationComponent.play("DEATH", dt, true))
		{
			this->player->gainCrystals(3 * this->statsComponent.level);
			this->player->gainEXP(this->statsComponent.level * 2);

			this->isDead = true;
		}
	}

	if (this->movementComponent.getState(IDLE))
	{
		this->animationComponent.play("IDLE", dt);
	}
	else if (this->movementComponent.getState(MOVING_RIGHT))
	{
		this->setOriginRight();
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().x, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVING_LEFT))
	{
		this->setOriginLeft();
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().x, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVE_UP))
	{
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().y, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVE_DOWN))
	{
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().y, this->movementComponent.getMaxVelocity());
	}
}

inline void MageEnemy::updatePlayerImpact(const float& dt)
{
	//Player damage impact
	if (this->player->getDamageRange().getGlobalBounds().intersects(this->getGlobalBounds()))
	{
		if (this->player->isDealingDmg())
		{
			if (!this->physicalResistance)
			{
				if (std::rand() % 100 <= this->player->getStatsComponent()->critRate)
				{
					this->critImpact = true;
					this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical * 2);

					//Sound
					this->playImpactSounds("PLAYER_CRIT");
				}
				else
				{
					this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical);

					//Sound
					this->playImpactSounds("PLAYER_HIT");
				}
				this->hitImpact = true;
				this->isTakingDamage = true;
				this->healthBar.updateOffsetX();
			}
			else
			{
				//pop up text
			}
		}
	}

	//Skill damage impact
	if (this->player->usingSkill())
	{
		if (!this->magicalResistance)
		{
			if (*this->playerUsingSkill != this->skillReistance)
			{
				if (this->player->getSkillComponent()->getDamageArea().getGlobalBounds().intersects(this->getGlobalBounds()))
				{
					this->isTakingDamage = true;
					this->skillImpact = true;

					//Lose hp
					this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical +
						this->player->getStatsComponent()->currentSkillDamage);

					//Update health bar
					this->healthBar.updateOffsetX();

					//Play sound
					this->playSkillImpactSounds(*this->playerUsingSkill);
				}
			}
			else
			{
				//Pop up text
			}
		}
		else
		{
			//Pop up text
		}
	}
}


//Constructors
MageEnemy::MageEnemy(const MageEnemyType& type, const int& level, const float& x, const float& y, 
	sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept
	:Enemy(level, x, y, texture_sheet, player, sounds),
	type(type), healthBar(&this->statsComponent.hp), levelIcon(&level, &this->player->getStatsComponent()->level, this->player->getFont())
{
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

MageEnemy::~MageEnemy()
{
}

//Public functions
void MageEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact(dt);
	this->updateAttack(dt);
	this->updateMovement(dt);
	this->updateAnimations(dt);

	this->healthBar.update(dt, this->getPosition());
	this->levelIcon.update(dt, this->getPosition());

	this->hitboxComponent.update();
}

void MageEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->sprite, shader);
	//target.draw(this->castRange);
	//target.draw(this->innerRange);

	if (this->hitImpact)
	{
		target.draw(this->takeHitSprite.second);
	}
	if (this->critImpact)
	{
		target.draw(this->critHitSprite.second);
	}
	if (this->skillImpact)
	{
		target.draw(this->skillsImpactSprites[*this->playerUsingSkill].first);
	}

	this->healthBar.render(target);
	this->levelIcon.render(target);

	//this->hitboxComponent.render(target);
}
