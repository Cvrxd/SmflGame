#include "stdafx.h"
#include "BossEnemy.h"

//Init functions
inline void BossEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case BossType::NIGHTBORN:
		this->sprite.setScale(6.f, 6.f);

		//Sound keys
		this->soundTime = 6.f;
		this->skillSoundKey = "NIGHTBORN_SKILL";
		this->soundKey      = "NIGHTBORN_SOUND";

		//Skill variables
		this->skillSprite.second.setScale(4.f, 4.f);
		this->skilloffsetX = -40.f;
		this->skilloffsetY = -15.f;

		//Skill impact on player
		this->skillImpactSprtite.second.setScale(2.f, 3.f);
		this->skillImpactoffsetX = 80.f;
		this->skillImpactoffsetY = 50.f;

		//Skill core variables
		this->skillColdown     = 5.f;
		this->skillRangeRadius = 500.f;

		this->skillRange.setFillColor        (sf::Color::Transparent);
		this->skillRange.setRadius           (this->skillRangeRadius);
		this->skillRange.setOutlineThickness (1.f);
		this->skillRange.setOutlineColor     (sf::Color::Red);

		//Attack time
		this->attackCountMAX  = 2;
		this->attackColdown   = 3.f;

		//Resistance
		this->skillReistance = SkillType::DARK_BOLT;

		//Init components
		this->createHitboxComponent    (this->sprite, 200.f, 200.f, 120.f, 150.f);
		this->createMovementComponent  (170.f, 1000.f, 250.f);
		this->createAnimationComponent (texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]() 
		{
			sprite.setOrigin(80.f, 0.f);
			sprite.setScale(-6.f, 6.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(6.f, 6.f);
		};

		break;
	case BossType::FIRE_DEMON:

		this->sprite.setScale(4.f, 4.f);

		//Sound keys
		this->soundTime = 6.f;
		this->skillSoundKey = "FIRE_DEMON_SKILL";
		this->soundKey      = "FIRE_DEMON_SOUND";

		//Boss skill sprite
		this->skillSprite.second.setScale(5.f, 5.f);
		this->skilloffsetX = 30.f;
		this->skilloffsetY = 50.f;

		//Skill impact on player
		this->skillImpactSprtite.second.setScale(4.f, 4.f);
		this->skillImpactoffsetX = 100.f;
		this->skillImpactoffsetY = 120.f;

		//Skill core variables
		this->skillColdown     = 5.f;
		this->skillRangeRadius = 600.f;

		this->skillRange.setFillColor        (sf::Color::Transparent);
		this->skillRange.setRadius           (this->skillRangeRadius);
		this->skillRange.setOutlineThickness (1.f);
		this->skillRange.setOutlineColor     (sf::Color::Red);

		//Attack time
		this->attackCountMAX = 1;
		this->attackColdown  = 3.f;

		//Resistance
		this->magicalResistance = true;

		//Init components
		this->createHitboxComponent    (this->sprite, 470.f, 300.f, 260.f, 350.f);
		this->createMovementComponent  (130.f, 900.f, 230.f);
		this->createAnimationComponent (texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin (0.f, 0.f);
			sprite.setScale  (4.f, 4.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin (290.f, 0.f);
			sprite.setScale  (-4.f, 4.f);
		};

		break;

	case BossType::SAMURAI:

		this->sprite.setScale(3.2f, 3.2f);
		
		//Sound keys
		this->soundTime = 5.f;
		this->skillSoundKey = "SAMURAI_SKILL";
		this->soundKey      = "SAMURAI_SOUND";

		//Boss skill sprite
		this->skillSprite.second.setScale(4.f, 4.f);
		this->skilloffsetX = -5.f;
		this->skilloffsetY = 0.f;

		//Skill impact on player
		this->skillImpactSprtite.second.setScale(6.f, 6.f);
		this->skillImpactoffsetX = 50.f;
		this->skillImpactoffsetY = 200.f;

		//Skill core variables
		this->skillColdown     = 5.f;
		this->skillRangeRadius = 500.f;

		this->skillRange.setFillColor        (sf::Color::Transparent);
		this->skillRange.setRadius           (this->skillRangeRadius);
		this->skillRange.setOutlineThickness (1.f);
		this->skillRange.setOutlineColor     (sf::Color::Red);

		//Attack time
		this->attackCountMAX = 3;
		this->attackColdown  = 2.f;

		//Resistance
		this->skillReistance = SkillType::BLOOD_SPIKE;

		//Init components
		this->createHitboxComponent    (this->sprite, 250.f, 230.f, 150.f, 170.f);
		this->createMovementComponent  (200.f, 1200.f, 230.f);
		this->createAnimationComponent (texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin (200.f, 0.f);
			sprite.setScale  (-3.2f, 3.2f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin (0.f, 0.f);
			sprite.setScale  (3.2f, 3.2f);
		};
		break;
	default:
		break;
	}
}

inline void BossEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	//Skill effect on boss
	this->skillSprite.first.loadFromFile("Textures/animations/enemy_skills/boss_skill.png");

	//Skill efect on player
	switch (this->type)
	{
	case BossType::NIGHTBORN:

		this->skillImpactSprtite.first.loadFromFile("Textures/animations/enemy_skills/nightborn_skill.png");
		break;
	case BossType::FIRE_DEMON:

		this->skillImpactSprtite.first.loadFromFile("Textures/animations/enemy_skills/fire_demon_skill.png");
		break;
	case BossType::SAMURAI:

		this->skillImpactSprtite.first.loadFromFile("Textures/animations/enemy_skills/samurai_skill.png");
		break;
	default:
		break;
	}

	this->skillAnimation        = { &this->skillSprite.second, &this->skillSprite.first };
	this->skillImpactAniamtion  = { &this->skillImpactSprtite.second, &this->skillImpactSprtite.first };

	this->addAnimations();
}

inline void BossEnemy::addAnimations()
{
	//Boss skill using animatiom
	this->skillAnimation.addAnimation("PLAY", 0, 0, 8, 0, 48, 48, 10.f);

	//Unique animations
	switch (this->type)
	{
	case BossType::NIGHTBORN:
		this->animationComponent.addAnimation ("MOVE", 0, 1, 5, 1, 80, 80, 20.f);
		this->animationComponent.addAnimation ("ATTACK", 0, 2, 11, 2, 80, 80, 10.f);
		this->animationComponent.addAnimation ("TAKE_HIT", 0, 3, 4, 3, 80, 80, 10.f);
		this->animationComponent.addAnimation ("DEATH", 0, 4, 22, 4, 80, 80, 8.f);
		this->animationComponent.addAnimation ("IDLE", 0, 0, 8, 0, 80, 80, 10.f);

		this->skillImpactAniamtion.addAnimation("PLAY", 0, 0, 11, 0, 106, 32, 10.f);
		break;

	case BossType::FIRE_DEMON:
		this->animationComponent.addAnimation ("MOVE", 0, 1, 11, 1, 288, 160, 15.f);
		this->animationComponent.addAnimation ("ATTACK", 0, 2, 14, 2, 288, 160, 10.f);
		this->animationComponent.addAnimation ("TAKE_HIT", 0, 3, 4, 3, 288, 160, 10.f);
		this->animationComponent.addAnimation ("DEATH", 0, 4, 21, 4, 288, 160, 10.f);
		this->animationComponent.addAnimation ("IDLE", 0, 0, 5, 0, 288, 160, 13.f);

		this->skillImpactAniamtion.addAnimation("PLAY", 0, 0, 43, 0, 64, 64, 2.f);
		break;

	case BossType::SAMURAI:
		this->animationComponent.addAnimation ("MOVE", 0, 2, 7, 2, 200, 200, 10.f);
		this->animationComponent.addAnimation ("ATTACK", 0, 0, 5, 0, 200, 200, 13.f);
		this->animationComponent.addAnimation ("TAKE_HIT", 0, 3, 3, 3, 200, 200, 14.f);
		this->animationComponent.addAnimation ("DEATH", 0, 1, 5, 1, 200, 200, 15.f);
		this->animationComponent.addAnimation ("IDLE", 0, 4, 7, 4, 200, 200, 10.f);

		this->skillImpactAniamtion.addAnimation ("PLAY", 0, 0, 5, 0, 32, 64, 20.f);
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
	//Boss skill update
	if (this->skillTimer.getElapsedTime().asSeconds() > this->skillColdown &&
		this->player->getHitRange().getGlobalBounds().intersects(this->skillRange.getGlobalBounds()))
	{
		this->isUsingSkill = true;
		this->bossSkill    = true;

		this->skillTimer.restart();

		//Sound
		this->soundBox.playSound(this->skillSoundKey);
	}

	//Attacking coldown update
	if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()) && !this->isDead && !this->isUsingSkill)
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

	//Boss attaking animations
	if (this->isAttaking)
	{
		if (this->animationComponent.play("ATTACK", dt, true))
		{
			if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()) && !this->isDead)
			{
				if (std::rand() % 100 <= this->player->getStatsComponent()->missChance)
				{
					//Pop up text
					this->updatePopUpText("MISS");
				}
				else
				{
					this->player->loseHP(this->statsComponent.damagePhysical);
				}
			}
			this->isAttaking = false;
		}
	}

	//Boss skill update
	if (this->isUsingSkill)
	{
		this->stopVelocity();

		if (this->animationComponent.play("ATTACK", dt, true))
		{
			if (this->player->getHitRange().getGlobalBounds().intersects(this->skillRange.getGlobalBounds()) && !this->isDead)
			{
				this->player->loseHP(this->statsComponent.damagePhysical + this->statsComponent.damagePhysical / 2);

				this->bossSkillImpact = true;
			}

			this->isUsingSkill = false;
		}
	}

	//Skill impact on player
	if (this->bossSkillImpact)
	{
		this->skillImpactSprtite.second.setPosition(
			this->player->getPosition().x - this->skillImpactoffsetX, 
			this->player->getPosition().y - this->skillImpactoffsetY);

		if (this->skillImpactAniamtion.play("PLAY", dt, true))
		{
			this->bossSkillImpact = false;
		}
	}

	if (this->bossSkill)
	{
		this->skillSprite.second.setPosition(this->getPosition().x + this->skilloffsetX, this->getPosition().y + this->skilloffsetY);

		if (this->skillAnimation.play("PLAY", dt, true))
		{
			this->bossSkill = false;
		}
	}
}

inline void BossEnemy::updateMovement(const float& dt)
{
	//Skill range
	this->skillRange.setPosition(this->getPosition().x - this->skillRangeRadius, this->getPosition().y - this->skillRangeRadius);

	//Movement
	if (!this->getGlobalBounds().intersects(this->player->getGlobalBounds()))
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
	else
	{
		this->stopVelocity();
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
				this->updatePopUpText("IMMUNE");
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
BossEnemy::BossEnemy(const BossType& type, const int& level, const float& x, const float& y, 
	sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds) noexcept
	:Enemy(level, x, y, texture_sheet, player, sounds),
	type(type), healthBar(&this->statsComponent.hp), levelIcon(&level, &this->player->getStatsComponent()->level, this->player->getFont())
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->sprite.setPosition(x, y);
}

BossEnemy::~BossEnemy()
{
}

//Public Functions
void BossEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact (dt);
	this->updateAttack       (dt);
	this->updateMovement     (dt);
	this->updateAnimations   (dt);
	this->updateSound        ();

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

	if (this->bossSkill)
	{
		target.draw(this->skillSprite.second);
	}
	if (this->bossSkillImpact)
	{
		target.draw(this->skillImpactSprtite.second);
	}

	//Render pop up text
	this->renderPopUpText(target);

	//Enemy gui render
	this->healthBar.render(target);
	this->levelIcon.render(target);

	//Debug
	//target.draw(this->skillRange);
	//this->hitboxComponent.render(target);
}