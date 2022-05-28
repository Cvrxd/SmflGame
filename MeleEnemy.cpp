#include "stdafx.h"
#include "MeleEnemy.h"

//Init functions
inline void MeleEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case MeleEnemyType::MIMIC:
		this->sprite.setScale(3.f, 3.f);

		//Init components
		this->createHitboxComponent(this->sprite, 70.f, 120.f, 130.f, 100.f);
		this->createMovementComponent(80.f, 600.f, 100.f);
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
	case MeleEnemyType::BRINGER_OF_DEATH:
		this->sprite.setScale(3.f, 3.f);

		//Init components
		this->createHitboxComponent(this->sprite, 250.f, 120.f, 100.f, 200.f);
		this->createMovementComponent(150.f, 850.f, 200.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(200.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		break;
	case MeleEnemyType::KNIGHT1:
		this->sprite.setScale(2.5f, 2.5f);

		//Init components
		this->createHitboxComponent(this->sprite, 200.f, 150.f, 120.f, 150.f);
		this->createMovementComponent(200.f, 1000.f, 350.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(200.f, 0.f);
			sprite.setScale(-2.5f, 2.5f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(2.5f, 2.5f);
		};
		break;
	case MeleEnemyType::HUNTRESS:
		this->sprite.setScale(3.f, 3.f);

		//Init components
		this->createHitboxComponent(this->sprite, 170.f, 150.f, 100.f, 150.f);
		this->createMovementComponent(180.f, 1000.f, 200.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(150.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		break;

	case MeleEnemyType::MARTIAL_HERO1:
		this->sprite.setScale(2.7f, 2.7f);

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
	case MeleEnemyType::MARTIAL_HERO2:
		this->sprite.setScale(2.6f, 2.6f);

		//Init components
		this->createHitboxComponent(this->sprite, 200.f, 180.f, 100.f, 150.f);
		this->createMovementComponent(170.f, 1000.f, 200.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(200.f, 0.f);
			sprite.setScale(-2.6f, 2.6f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(2.6f, 2.6f);
		};
		break;
	case MeleEnemyType::MARTIAL_HERO3:
		this->sprite.setScale(3.f, 3.f);

		//Init components
		this->createHitboxComponent(this->sprite, 180.f, 100.f, 150.f, 160.f);
		this->createMovementComponent(170.f, 1000.f, 200.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(150.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
	break;
	default:
		break;
	}
}

inline void MeleEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->addAnimations();
}

inline void MeleEnemy::addAnimations()
{
	switch (this->type)
	{
	case MeleEnemyType::MIMIC:
		this->animationComponent.addAnimation("MOVE", 0, 1, 3, 1, 108, 108, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 3, 0, 108, 108, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 1, 2, 108, 108, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 2, 3, 2, 108, 108, 20.f);
		break;
	case MeleEnemyType::BRINGER_OF_DEATH:
		this->animationComponent.addAnimation("MOVE", 0, 0, 7, 0, 140, 93, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 1, 9, 1, 140, 93, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 2, 2, 140, 93, 20.f);
		this->animationComponent.addAnimation("DEATH", 2, 2, 11, 2, 140, 93, 15.f);
		break;
	case MeleEnemyType::KNIGHT1:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 180, 180, 13.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 6, 0, 180, 180, 11.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 3, 3, 180, 180, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 10, 1, 180, 180, 11.f);
		break;
	case MeleEnemyType::HUNTRESS:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 150, 150, 13.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 4, 0, 150, 150, 11.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 2, 3, 150, 150, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 7, 1, 150, 150, 11.f);
		break;
	case MeleEnemyType::MARTIAL_HERO1:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 200, 200, 10.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 5, 0, 200, 200, 13.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 3, 3, 200, 200, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 5, 1, 200, 200, 15.f);
		break;
	case MeleEnemyType::MARTIAL_HERO2:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 200, 200, 10.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 3, 0, 200, 200, 19.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 2, 3, 200, 200, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 6, 1, 200, 200, 15.f);
		break;
	case MeleEnemyType::MARTIAL_HERO3:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 126, 126, 10.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 6, 0, 126, 126, 16.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 2, 3, 126, 126, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 10, 1, 126, 126, 15.f);
	default:
		break;
	}
}

//Constructors
MeleEnemy::MeleEnemy(const MeleEnemyType& type, const int& level, const float& x, const float& y, 
	sf::Texture& texture_sheet, Player* player)
	:Enemy(level, x, y, texture_sheet, player),
	type(type), healthBar(&this->statsComponent.hp), levelIcon(&level, &this->player->getStatsComponent()->level, this->player->getFont())
{
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

MeleEnemy::~MeleEnemy()
{
}

//Functions
inline void MeleEnemy::updateAttack(const float& dt)
{
	if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()) && !this->isDead)
	{
		this->isAttaking = true;
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

inline void MeleEnemy::updateMovement(const float& dt)
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

inline void MeleEnemy::updateAnimations(const float& dt)
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
			this->player->gainCoins(3 * this->statsComponent.level);
			this->player->gainEXP(this->statsComponent.level * 2);
			
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

inline void MeleEnemy::updatePlayerImpact(const float& dt)
{
	//Player damage impact
	if (this->player->getDamageRange().getGlobalBounds().intersects(this->getGlobalBounds()))
	{
		if (this->player->isDealingDmg())
		{
			if (std::rand() % 100 <= this->player->getStatsComponent()->critRate)
			{
				this->critImpact = true;
				this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical * 2);
			}
			else
			{
				this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical);
			}

			this->hitImpact = true;
			this->isTakingDamage = true;
			this->healthBar.updateOffsetX();
		}
	}
	//Skill damage impact
	if (this->player->usingSkill())
	{
		if (this->player->getSkillComponent()->getDamageArea().getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			this->isTakingDamage = true;
			this->skillImpact = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical + 
				this->player->getStatsComponent()->currentSkillDamage);

			this->healthBar.updateOffsetX();
		}
	}
}

void MeleEnemy::enemyDead(const float& dt)
{

}

void MeleEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
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

void MeleEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
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