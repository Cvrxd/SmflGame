#include "stdafx.h"
#include "MageEnemy.h"

//Init functions
inline void MageEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case MageEnemyType::DARK_MAGE:
		this->sprite.setScale(3.f, 3.f);
		
		//Init spell cast range
		this->castRange.setRadius(300.f);
		this->castRange.setFillColor(sf::Color::Transparent);
		this->castRange.setOutlineColor(sf::Color::Red);
		this->castRange.setOutlineThickness(1.f);

		this->innerRange.setRadius(150.f);
		this->innerRange.setFillColor(sf::Color::Transparent);
		this->innerRange.setOutlineColor(sf::Color::Green);
		this->innerRange.setOutlineThickness(1.f);

		//Init components
		this->createHitboxComponent(this->sprite, 70.f, 120.f, 100.f, 100.f);
		this->createMovementComponent(80.f, 600.f, 100.f);
		this->createAnimationComponent(texture_sheet);
		this->initImpactAnimations();

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
		this->animationComponent.addAnimation("MOVE", 0, 1, 3, 1, 108, 108, 20.f);
		this->animationComponent.addAnimation("CAST", 0, 0, 3, 0, 108, 108, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 1, 2, 108, 108, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 2, 3, 2, 108, 108, 20.f);
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
	this->skillImpactAnimation = other.skillImpactAnimation;
	this->skillImpactSprite = other.skillImpactSprite;
	this->takeHitAnimation = other.takeHitAnimation;
	this->takeHitSprite = other.takeHitSprite;

	other.player = nullptr;
}

MageEnemy::~MageEnemy()
{
}

//Functions
inline void MageEnemy::updateAttack(const float& dt)
{
	if (this->player->getHitRange().getGlobalBounds().intersects(this->castRange.getGlobalBounds()) && !this->isDead)
	{
		this->isAttaking = true;
	}

	if (this->isAttaking)
	{
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
	if (this->player->getHitRange().getGlobalBounds().intersects(this->innerRange.getGlobalBounds()) && this->player->getPosition().x < this->getPosition().x)
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

	this->castRange.setPosition(this->getPosition().x - 300, this->getPosition().y - 300);
	this->innerRange.setPosition(this->getPosition().x - 150, this->getPosition().y - 150);
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
		this->skillImpactSprite.second.setPosition(this->getPosition().x - 40, this->getPosition().y - 50);

		if (this->skillImpactAnimation.play("SKILL_IMPACT", dt, true))
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
	target.draw(this->castRange);
	target.draw(this->innerRange);

	if (this->hitImpact)
	{
		target.draw(this->takeHitSprite.second);
	}
	if (this->skillImpact)
	{
		target.draw(this->skillImpactSprite.second);
	}

	this->hitboxComponent.render(target);
}
