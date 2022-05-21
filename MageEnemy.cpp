
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
		this->animationComponent.addAnimation("MOVE", 0, 1, 7, 1, 250, 250, 20.f);
		this->animationComponent.addAnimation("CAST", 0, 3, 15, 3, 250, 250, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 2, 2, 250, 250, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 0, 6, 0, 250, 250, 15.f);
		break;
	case MageEnemyType::FIRE_MAGE:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 150, 150, 20.f);
		this->animationComponent.addAnimation("CAST", 0, 0, 7, 0, 150, 150, 15.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 3, 3, 150, 150, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 6, 1, 150, 150, 15.f);
		break;
	default:
		break;
	}
}

//Constructors
MageEnemy::MageEnemy(const MageEnemyType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player)
	:Enemy(level, x, y, texture_sheet, player),
	type(type)
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

MageEnemy::MageEnemy(MageEnemy&& other)
	:Enemy(this->statsComponent.level, this->getPosition().x, this->getPosition().y, *this->textureSheet, this->player)
{
	this->animationComponent = other.animationComponent;
	this->dropComponent = other.dropComponent;
	this->hitboxComponent = other.hitboxComponent;
	this->isAttaking = other.isAttaking;
	this->isDead = other.isDead;
	this->movementComponent = other.movementComponent;
	this->setOriginLeft = other.setOriginLeft;
	this->setOriginRight = other.setOriginRight;
	this->sprite = other.sprite;
	this->statsComponent = other.statsComponent;
	this->hitImpact = other.hitImpact;
	this->skillImpact = other.skillImpact;
	this->type = other.type;
	//
	this->takeHitAnimation = other.takeHitAnimation;
	this->takeHitSprite = other.takeHitSprite;
	this->castR = other.castR;
	this->castRange = other.castRange;
	this->ineerR = other.ineerR;
	this->innerRange = other.innerRange;

	other.player = nullptr;
}

MageEnemy::~MageEnemy()
{
}

//Functions
inline void MageEnemy::updateAttack(const float& dt)
{
	if (this->player->getHitRange().getGlobalBounds().intersects(this->castRange.getGlobalBounds()) && 
		!this->player->getHitRange().getGlobalBounds().intersects(this->innerRange.getGlobalBounds()) && !this->isDead)
	{
		this->isAttaking = true;
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

	//Plyaer skill
	if (this->skillImpact)
	{
		this->skillsImpactSprites[this->player->getUsingSkilltype()].first.setPosition(this->getPosition().x - 40, this->getPosition().y - 50);

		if (this->skillsImpactAnimations[this->player->getUsingSkilltype()].play("SKILL_IMPACT", dt, true))
		{
			this->skillImpact = false;
		}
	}

	if (this->statsComponent.hp == 0)
	{
		this->stopVelocity();
		if (this->animationComponent.play("DEATH", dt, true))
		{
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

inline void MageEnemy::updatePlayerImpact(const float& dt)
{
	//Player damage impact
	if (this->player->getDamageRange().getGlobalBounds().intersects(this->getGlobalBounds()))
	{
		if (this->player->isDealingDmg())
		{
			this->isTakingDamage = true;
			this->hitImpact = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical);
		}
	}
	//Skill damage impact
	if (this->player->usingSkill())
	{
		if (this->player->getSkillComponent()->getDamageArea().getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			this->isTakingDamage = true;
			this->skillImpact = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical);
		}
	}
}

void MageEnemy::enemyDead(const float& dt)
{

}

void MageEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact(dt);
	this->updateAttack(dt);
	this->updateMovement(dt);
	this->updateAnimations(dt);

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
	if (this->skillImpact)
	{
		target.draw(this->skillsImpactSprites[this->player->getUsingSkilltype()].first);
	}

	//this->hitboxComponent.render(target);
}
