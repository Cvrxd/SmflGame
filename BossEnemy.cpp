#include "stdafx.h"
#include "BossEnemy.h"

//Init functions
inline void BossEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case NIGHTBORN:
		this->sprite.setScale(4.f, 4.f);

		//Take hit sprites
		this->takeHitSprite.first.loadFromFile("Textures/animations/hit/hit02.png");
		this->takeHitSprite.second.setScale(3.f, 3.f);

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
	default:
		break;
	}
}

inline void BossEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->takeHitAnimation = { &this->takeHitSprite.second, &this->takeHitSprite.first };

	this->addAnimations();
}

inline void BossEnemy::addAnimations()
{
	switch (this->type)
	{
	case NIGHTBORN:
		//Regular animations
		this->animationComponent.addAnimation("IDLE", 0, 0, 8, 0, 80, 80, 10.f);
		this->animationComponent.addAnimation("MOVE", 0, 1, 5, 1, 80, 80, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 2, 11, 2, 80, 80, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 4, 3, 80, 80, 8.f);
		this->animationComponent.addAnimation("DEATH", 0, 4, 22, 4, 80, 80, 8.f);

		//Take hit animations
		this->takeHitAnimation.addAnimation("TAKE_HIT1", 0, 0, 4, 0, 64, 64, 7.f);
		this->takeHitAnimation.addAnimation("TAKE_HIT2", 0, 1, 4, 1, 64, 64, 7.f);

		break;
	default:
		break;
	}
}

//Constructors
BossEnemy::BossEnemy(const BossType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player)
	:Enemy(level, x, y, texture_sheet, player), 
	type(type)
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

BossEnemy::BossEnemy(BossEnemy&& other)
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
	this->takingHit = other.takingHit;
	this->type = other.type;
	this->takeHitAnimation = other.takeHitAnimation;
	this->takeHitSprite = other.takeHitSprite;

	other.player = nullptr;
}

BossEnemy::~BossEnemy()
{
}

//Functions
inline void BossEnemy::updateAttack(const float& dt)
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
	if (this->player->getPosition().y < this->getPosition().y)
	{
		this->move(0.f, -1.f, dt);
	}
	else if (this->player->getPosition().y > this->getPosition().y)
	{
		this->move(0, 1.f, dt);
	}
}

inline void BossEnemy::updateAnimations(const float& dt)
{
	if (this->takingHit)
	{
		this->takeHitSprite.second.setPosition(this->getPosition());

		this->stopVelocity();

		if (this->animationComponent.play("TAKE_HIT", dt, true))
		{
			this->takingHit = false;
		}

		if (this->takeHitAnimation.play("TAKE_HIT1", dt, true))
		{
			this->takeHitAnimation.play("TAKE_HIT2", dt, true);
		}
	}

	if (this->statsComponent.hp == 0)
	{
		this->stopVelocity();
		if (this->animationComponent.play("DEATH", dt, true))
		{
			this->player->addPotions(HEALTH);
			this->player->addPotions(MANA);
			this->player->gainEXP(this->statsComponent.level * 5);

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

inline void BossEnemy::updatePlayerImpact(const float& dt)
{
	//Player damage impact
	if (this->player->getDamageRange().getGlobalBounds().intersects(this->getGlobalBounds()))
	{
		if (this->player->isDealingDmg())
		{
			this->takingHit = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical);
		}
	}
	//Skill damage impact
	if (this->player->usingSkill())
	{
		if (this->player->getSkillComponent()->getDamageArea().getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			this->takingHit = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical);
		}
	}
}

void BossEnemy::enemyDead(const float& dt)
{

}

void BossEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact(dt);
	this->updateAttack(dt);
	this->updateMovement(dt);
	this->updateAnimations(dt);

	this->hitboxComponent.update();
}

void BossEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->sprite, shader);

	if (this->takingHit)
	{
		target.draw(this->takeHitSprite.second);
	}

	//this->hitboxComponent.render(target);
}