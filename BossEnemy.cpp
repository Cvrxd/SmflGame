#include "stdafx.h"
#include "BossEnemy.h"

//Init functions
inline void BossEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case BossType::NIGHTBORN:
		this->sprite.setScale(4.f, 4.f);

		//Attack time
		this->attackCountMAX = 2;
		this->attackColdown = 2.f;

		//Resistance
		this->skillReistance = SkillType::DARK_BOLT;

		//Init components
		this->createHitboxComponent(this->sprite, 100.f, 100.f, 100.f, 100.f);
		this->createMovementComponent(150.f, 900.f, 250.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]() 
		{
			sprite.setOrigin(80.f, 0.f);
			sprite.setScale(-4.f, 4.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(4.f, 4.f);
		};

		break;
	case BossType::FIRE_DEMON:
		this->sprite.setScale(4.f, 4.f);

		//Attack time
		this->attackCountMAX = 1;
		this->attackColdown = 1.f;

		//Resistance
		this->magicalResistance = true;

		//Init components
		this->createHitboxComponent(this->sprite, 300.f, 300.f, 300.f, 350.f);
		this->createMovementComponent(100.f, 800.f, 230.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(4.f, 4.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(250.f, 0.f);
			sprite.setScale(-4.f, 4.f);
		};

		break;

	case BossType::SAMURAI:
		this->sprite.setScale(2.7f, 2.7f);
		
		//Attack time
		this->attackCountMAX = 3;
		this->attackColdown = 2.f;

		//Resistance
		this->skillReistance = SkillType::BLOOD_SPIKE;

		//Init components
		this->createHitboxComponent(this->sprite, 200.f, 150.f, 100.f, 150.f);
		this->createMovementComponent(200.f, 1200.f, 230.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(200.f, 0.f);
			sprite.setScale(-2.7f, 2.7f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(2.7f, 2.7f);
		};
		break;
	default:
		break;
	}
}

inline void BossEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->addAnimations();
}

inline void BossEnemy::addAnimations()
{
	switch (this->type)
	{
	case BossType::NIGHTBORN:
		this->animationComponent.addAnimation("MOVE", 0, 1, 5, 1, 80, 80, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 2, 11, 2, 80, 80, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 4, 3, 80, 80, 10.f);
		this->animationComponent.addAnimation("DEATH", 0, 4, 22, 4, 80, 80, 8.f);
		break;
	case BossType::FIRE_DEMON:
		this->animationComponent.addAnimation("MOVE", 0, 1, 11, 1, 288, 160, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 2, 14, 2, 288, 160, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 4, 3, 288, 160, 10.f);
		this->animationComponent.addAnimation("DEATH", 0, 4, 21, 4, 288, 160, 10.f);
		break;

	case BossType::SAMURAI:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 200, 200, 10.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 5, 0, 200, 200, 13.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 3, 3, 200, 200, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 5, 1, 200, 200, 15.f);
		break;
	default:
		break;
	}
}

//Sound fucntions
inline void BossEnemy::playImpactSounds(const std::string& sound)
{
	this->soundBox.playSound(sound);
}

inline void BossEnemy::playSkillImpactSounds(const SkillType& type)
{
	this->soundBox.playSound(type);
}

//Update functions
inline void BossEnemy::updateAttack(const float& dt)
{
	//Attacking coldown update
	if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()) && !this->isDead)
	{
		if (this->attackCount == this->attackCountMAX)
		{
			this->attackTimer.restart();
			this->attackCount = 0;
		}
		else if(this->attackColdown <= this->attackTimer.getElapsedTime().asSeconds() && !this->isAttaking)
		{
			this->isAttaking = true;
			++this->attackCount;
		}
	}

	if (this->isAttaking)
	{
		if (this->animationComponent.play("ATTACK", dt, true))
		{
			if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()))
			{
				this->player->loseHP(this->statsComponent.damagePhysical);
			}
			this->isAttaking = false;
		}
	}
}

inline void BossEnemy::updateMovement(const float& dt)
{
	if (this->player->getPosition().x > this->getPosition().x)
	{
		this->move(1.f, 0.f, dt);
	}
	else if (this->player->getPosition().x < this->getPosition().x)
	{
		this->move(-1.f, 0.f, dt);
	}
	else
	{
		this->stopVelocityX();
	}

	if (this->player->getPosition().y < this->getPosition().y)
	{
		this->move(0.f, -1.f, dt);
	}
	else if (this->player->getPosition().y > this->getPosition().y)
	{
		this->move(0, 1.f, dt);
	}
	else
	{
		this->stopVelocityY();
	}
}

inline void BossEnemy::updateAnimations(const float& dt)
{
	//taking damage animation
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

	//Death
	if (this->statsComponent.hp == 0)
	{
		this->stopVelocity();
		if (this->animationComponent.play("DEATH", dt, true))
		{
			this->player->addPotions(HEALTH);
			this->player->addPotions(MANA);

			this->player->gainCoins(5 * this->statsComponent.level);
			this->player->gainCrystals(5 * this->statsComponent.level);

			this->player->gainEXP(this->statsComponent.level * 5);

			this->isDead = true;
		}
	}

	//Movement animations
	if (this->movementComponent.getState(MOVING_RIGHT))
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

inline void BossEnemy::updatePlayerImpact(const float& dt)
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
				//Pop up text
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

					//Loose hp
					this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical +
						this->player->getStatsComponent()->currentSkillDamage);

					//Update health bar
					this->healthBar.updateOffsetX();

					//Sound
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
BossEnemy::BossEnemy(const BossType& type, const int& level, const float& x, const float& y, 
	sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept
	:Enemy(level, x, y, texture_sheet, player, sounds),
	type(type), healthBar(&this->statsComponent.hp), levelIcon(&level, &this->player->getStatsComponent()->level, this->player->getFont())
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

BossEnemy::~BossEnemy()
{
}

//Public Functions
void BossEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
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

void BossEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->sprite, shader);

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