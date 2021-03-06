#include <stdafx.h>
#include "DestroyingEnemy.h"

//Init functions
inline void DestroyingEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	this->destroySoundKey = "DESTROY_ENEMY_SOUND";

	switch (this->type)
	{
	case DestroyingEnemyType::FIRE_SKULL:
		this->sprite.setScale(3.f, 3.f);

		//Init resistance
		this->skillReistance = SkillType::FIRE_EXPLOSION;
		this->physicalResistance = true;

		//Init components
		this->createHitboxComponent(this->sprite, 70.f, 120.f, 200.f, 200.f);
		this->createMovementComponent(80.f, 600.f, 100.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(100.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		break;

	case DestroyingEnemyType::FIRE_WORM:
		this->sprite.setScale(3.f, 3.f);

		//Init resistance
		this->skillReistance = SkillType::FIRE_EXPLOSION;
		//this->physicalResistance = true;

		//Init components
		this->createHitboxComponent(this->sprite, 70.f, 120.f, 150.f, 120.f);
		this->createMovementComponent(120.f, 800.f, 160.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(100.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		break;
	case DestroyingEnemyType::DRAGON:
		this->sprite.setScale(3.f, 3.f);

		//Init resistance
		this->skillReistance = SkillType::FIRE_EXPLOSION;
		this->physicalResistance = true;

		//Init components
		this->createHitboxComponent(this->sprite, 50.f, 40.f, 150.f, 120.f);
		this->createMovementComponent(160.f, 1000.f, 180.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(100.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
	default:
		break;
	}
}

inline void DestroyingEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	//Init destroying animations
	switch (this->type)
	{
	case DestroyingEnemyType::FIRE_SKULL:
		this->destroyingSprite.first.setScale(4.f, 4.f);
		this->destroyingSprite.second.loadFromFile("Textures/animations/hit/destroying1.png");
		this->destroyingAnimation = { &this->destroyingSprite.first, &this->destroyingSprite.second };
		break;
	case DestroyingEnemyType::FIRE_WORM:
		this->destroyingSprite.first.setScale(4.f, 4.f);
		this->destroyingSprite.second.loadFromFile("Textures/animations/hit/destroying1.png");
		this->destroyingAnimation = { &this->destroyingSprite.first, &this->destroyingSprite.second };
		break;
	case DestroyingEnemyType::DRAGON:
		this->destroyingSprite.first.setScale(4.f, 4.f);
		this->destroyingSprite.second.loadFromFile("Textures/animations/hit/destroying1.png");
		this->destroyingAnimation = { &this->destroyingSprite.first, &this->destroyingSprite.second };
	default:
		break;
	}

	this->addAnimations();
}

inline void DestroyingEnemy::addAnimations()
{
	switch (this->type)
	{
	case DestroyingEnemyType::FIRE_SKULL:
		this->animationComponent.addAnimation("MOVE", 0, 0, 7, 0, 96, 112, 15.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 7, 0, 96, 112, 20.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 0, 7, 0, 96, 112, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 0, 7, 0, 96, 112, 20.f);
		this->destroyingAnimation.addAnimation("DESTROY", 0, 0, 6, 0, 81, 66, 10.f);
		break;
	case DestroyingEnemyType::FIRE_WORM:
		this->animationComponent.addAnimation("MOVE", 0, 3, 8, 3, 90, 90, 11.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 15, 0, 90, 90, 15.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 2, 2, 90, 90, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 7, 1, 90, 90, 20.f);
		this->destroyingAnimation.addAnimation("DESTROY", 0, 0, 6, 0, 81, 66, 10.f);
		break;
	case DestroyingEnemyType::DRAGON:
		this->animationComponent.addAnimation("MOVE", 1, 0, 7, 0, 62, 72, 11.f);
		this->animationComponent.addAnimation("ATTACK", 8, 0, 15, 0, 60, 72, 15.f);
		this->animationComponent.addAnimation("TAKE_HIT", 14, 0, 17, 0, 60, 72, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 7, 1, 90, 60, 10.f);
		this->destroyingAnimation.addAnimation("DESTROY", 0, 0, 6, 0, 81, 66, 10.f);
		break;
	default:
		break;
	}
}

//Sound functions
inline void DestroyingEnemy::playImpactSounds(const std::string& sound)
{
	this->soundBox.playSound(sound);
}

inline void DestroyingEnemy::playSkillImpactSounds(const SkillType& type)
{
	this->soundBox.playSound(type);
}

//Update functions
inline void DestroyingEnemy::updateAttack(const float& dt)
{
	if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()) && !this->isDead)
	{
		this->statsComponent.hp = 0;

		//Sound
		this->soundBox.playSound(this->destroySoundKey);
	}
}

inline void DestroyingEnemy::updateMovement(const float& dt)
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

inline void DestroyingEnemy::updateAnimations(const float& dt)
{
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

		this->destroyingSprite.first.setPosition(this->getPosition().x - 50, this->getPosition().y - 50);

		if (this->destroyingAnimation.play("DESTROY", dt, true))
		{
			if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()))
			{
				this->player->loseHP(this->statsComponent.damageMagical * 2);
			}

			this->player->gainEXP(this->statsComponent.level * 2);

			++this->player->getKillsCount();

			this->isDead = true;
		}
	}

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

inline void DestroyingEnemy::updatePlayerImpact(const float& dt)
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

					//Pop up text
					this->updatePopUpText("CRIT");
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
				this->updatePopUpText("IMMUNE");
			}
		}
	}

	//Skill damage impact
	if (this->player->usingSkill())
	{
		if (*this->playerUsingSkill != this->skillReistance)
		{
			if (this->player->getSkillComponent()->getDamageArea().getGlobalBounds().intersects(this->getGlobalBounds()))
			{
				this->isTakingDamage = true;
				this->skillImpact = true;

				//Loosing hp 
				this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical +
					this->player->getStatsComponent()->currentSkillDamage);

				//Health bar update
				this->healthBar.updateOffsetX();

				//Playing sound
				this->playSkillImpactSounds(*this->playerUsingSkill);
			}
		}
		else
		{
			//Pop up text
			this->updatePopUpText("IMMUNE");
		}
	}
}

//Constructors
DestroyingEnemy::DestroyingEnemy(const DestroyingEnemyType& type, const int& level, const float& x, const float& y, 
	sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept
	:
	Enemy     (level, x, y, texture_sheet, player, sounds),
	type      (type), 
	healthBar (&this->statsComponent.hp), 
	levelIcon (&level, &this->player->getStatsComponent()->level, this->player->getFont())
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->sprite.setPosition(x, y);
}

DestroyingEnemy::~DestroyingEnemy()
{
}

//Public functions
void DestroyingEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact (dt);
	this->updateAttack       (dt);
	this->updateMovement     (dt);
	this->updateAnimations   (dt);

	this->healthBar.update   (dt, this->getPosition());
	this->levelIcon.update   (dt, this->getPosition());

	this->hitboxComponent.update();
}

void DestroyingEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (this->statsComponent.hp == 0 && !this->isDead)
	{
		target.draw(this->destroyingSprite.first);
	}
	else if(!this->isDead)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->player->getPosition());

		target.draw(this->sprite, shader);
	}

	if (this->critImpact)
	{
		target.draw(this->critHitSprite.second);
	}
	if (this->hitImpact)
	{
		target.draw(this->takeHitSprite.second);
	}
	if (this->skillImpact)
	{
		target.draw(this->skillsImpactSprites[*this->playerUsingSkill].first);
	}

	//Render pop up text
	this->renderPopUpText(target);

	this->healthBar.render(target);
	this->levelIcon.render(target);

	//this->hitboxComponent.render(target);
}