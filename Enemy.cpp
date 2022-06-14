#include "stdafx.h"
#include "Enemy.h"

//Initialisation
void Enemy::initSkillsImpactTextures()
{
	//Take hit sprites
	this->takeHitSprite.first.loadFromFile("Textures/animations/hit/hit02.png");
	this->takeHitSprite.second.setScale(3.f, 3.f);
	this->takeHitAnimation = { &this->takeHitSprite.second, &this->takeHitSprite.first };

	//Crit hit
	this->critHitSprite.first.loadFromFile("Textures/animations/hit/crit.png");
	this->critHitSprite.second.setScale(2.5f, 2.5f);
	this->critHitAnimation = { &this->critHitSprite.second, &this->critHitSprite.first };

	//Skills textures and sptites
	this->skillsImpactSprites[SkillType::BLOOD_SPIKE].second.loadFromFile("Textures/animations/hit/skill_hit.png");;
	this->skillsImpactSprites[SkillType::BLOOD_SPIKE].first.setScale(4.f, 4.f);
	this->skillsImpactAnimations[SkillType::BLOOD_SPIKE] = { &this->skillsImpactSprites[SkillType::BLOOD_SPIKE].first, &this->skillsImpactSprites[SkillType::BLOOD_SPIKE].second };
	this->offsets[SkillType::BLOOD_SPIKE] = 40;

	this->skillsImpactSprites[SkillType::POISON_CLAW].second.loadFromFile("Textures/animations/hit/poison_hit.png");;
	this->skillsImpactSprites[SkillType::POISON_CLAW].first.setScale(4.f, 4.f);
	this->skillsImpactAnimations[SkillType::POISON_CLAW] = { &this->skillsImpactSprites[SkillType::POISON_CLAW].first, &this->skillsImpactSprites[SkillType::POISON_CLAW].second };
	this->offsets[SkillType::POISON_CLAW] = 120;

	this->skillsImpactSprites[SkillType::DARK_BOLT].second.loadFromFile("Textures/animations/hit/dark_hit.png");;
	this->skillsImpactSprites[SkillType::DARK_BOLT].first.setScale(4.5f, 4.5f);
	this->skillsImpactAnimations[SkillType::DARK_BOLT] = { &this->skillsImpactSprites[SkillType::DARK_BOLT].first, &this->skillsImpactSprites[SkillType::DARK_BOLT].second };
	this->offsets[SkillType::DARK_BOLT] = 80;

	this->skillsImpactSprites[SkillType::THUNDER_STRIKE].second.loadFromFile("Textures/animations/hit/thunder_hit.png");;
	this->skillsImpactSprites[SkillType::THUNDER_STRIKE].first.setScale(5.5f, 5.5f);
	this->skillsImpactAnimations[SkillType::THUNDER_STRIKE] = { &this->skillsImpactSprites[SkillType::THUNDER_STRIKE].first, &this->skillsImpactSprites[SkillType::THUNDER_STRIKE].second };
	this->offsets[SkillType::THUNDER_STRIKE] = 40;

	this->skillsImpactSprites[SkillType::DARK_POSION].second.loadFromFile("Textures/animations/hit/dark_hit2.png");;
	this->skillsImpactSprites[SkillType::DARK_POSION].first.setScale(4.f, 4.f);
	this->skillsImpactAnimations[SkillType::DARK_POSION] = { &this->skillsImpactSprites[SkillType::DARK_POSION].first, &this->skillsImpactSprites[SkillType::DARK_POSION].second };
	this->offsets[SkillType::DARK_POSION] = 170;

	this->skillsImpactSprites[SkillType::FIRE_EXPLOSION].second.loadFromFile("Textures/animations/hit/fire_hit.png");;
	this->skillsImpactSprites[SkillType::FIRE_EXPLOSION].first.setScale(4.f, 4.f);
	this->skillsImpactAnimations[SkillType::FIRE_EXPLOSION] = { &this->skillsImpactSprites[SkillType::FIRE_EXPLOSION].first, &this->skillsImpactSprites[SkillType::FIRE_EXPLOSION].second };
	this->offsets[SkillType::FIRE_EXPLOSION] = 40;

	this->skillsImpactSprites[SkillType::HOLY_STRIKE].second.loadFromFile("Textures/animations/hit/holy_hit.png");;
	this->skillsImpactSprites[SkillType::HOLY_STRIKE].first.setScale(4.f, 4.f);
	this->skillsImpactAnimations[SkillType::HOLY_STRIKE] = { &this->skillsImpactSprites[SkillType::HOLY_STRIKE].first, &this->skillsImpactSprites[SkillType::HOLY_STRIKE].second };
	this->offsets[SkillType::HOLY_STRIKE] = 110;

	this->skillsImpactSprites[SkillType::LIGHTNING_STRIKE].second.loadFromFile("Textures/animations/hit/spark.png");;
	this->skillsImpactSprites[SkillType::LIGHTNING_STRIKE].first.setScale(5.f, 5.f);
	this->skillsImpactAnimations[SkillType::LIGHTNING_STRIKE] = { &this->skillsImpactSprites[SkillType::LIGHTNING_STRIKE].first, &this->skillsImpactSprites[SkillType::LIGHTNING_STRIKE].second };
	this->offsets[SkillType::LIGHTNING_STRIKE] = 0;
}

void Enemy::initImpactAnimations()
{	
	//Take hit animations
	this->takeHitAnimation.addAnimation("TAKE_HIT1", 0, 0, 4, 0, 64, 64, 4.f);
	this->takeHitAnimation.addAnimation("TAKE_HIT2", 0, 1, 4, 1, 64, 64, 4.f);

	//Crit animations
	this->critHitAnimation.addAnimation("CRIT", 0, 0, 13, 0, 128, 128, 4.f);

	//Skills impact animations
	this->skillsImpactAnimations[SkillType::BLOOD_SPIKE].addAnimation("SKILL_IMPACT", 0, 0, 14, 0, 64, 49, 5.f);
	this->skillsImpactAnimations[SkillType::POISON_CLAW].addAnimation("SKILL_IMPACT", 0, 0, 39, 0, 96, 96, 1.f);
	this->skillsImpactAnimations[SkillType::DARK_BOLT].addAnimation("SKILL_IMPACT", 0, 0, 7, 0, 64, 64, 9.f);
	this->skillsImpactAnimations[SkillType::THUNDER_STRIKE].addAnimation("SKILL_IMPACT", 0, 0, 4, 0, 32, 32, 9.f);
	this->skillsImpactAnimations[SkillType::DARK_POSION].addAnimation("SKILL_IMPACT", 0, 0, 15, 0, 140, 93, 8.f);
	this->skillsImpactAnimations[SkillType::FIRE_EXPLOSION].addAnimation("SKILL_IMPACT", 0, 0, 3, 0, 48, 48, 9.f);
	this->skillsImpactAnimations[SkillType::HOLY_STRIKE].addAnimation("SKILL_IMPACT", 0, 0, 27, 0, 96, 96, 4.f);
	this->skillsImpactAnimations[SkillType::LIGHTNING_STRIKE].addAnimation("SKILL_IMPACT", 0, 0, 6, 0, 32, 32, 7.f);
}

//Init functions
void Enemy::initStats()
{
	this->statsComponent.hp = 3 * this->statsComponent.level;
	this->statsComponent.armor = 0;

	this->statsComponent.damagePhysical = this->statsComponent.level / 5 + 1;
	this->statsComponent.damageMagical = this->statsComponent.level / 5 + 1;
}

void Enemy::initPopUpTextComponent()
{
	this->popUpTextComponent.addText ("IMMUNE", sf::Color::White, 40);
	this->popUpTextComponent.addText ("CRIT", sf::Color::Red, 40);
	this->popUpTextComponent.addText ("MISS", sf::Color(200, 200, 200), 40);
}

//Update functions 
void Enemy::updatePopUpText(const std::string& key)
{
	this->popUpTextKey = key;
	this->popUpTextComponent.prepareText(this->popUpTextKey);
	this->popUpTextTimer.restart();
	this->showPopUpText = true;
}

void Enemy::updateSound()
{
	if (this->soundTime < this->soundTimer.getElapsedTime().asSeconds() && !this->isDead)
	{
		this->soundTimer.restart();

		this->soundBox.playSound(this->soundKey);
	}
}

//Render functions
void Enemy::renderPopUpText(sf::RenderTarget& target)
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
			this->popUpTextComponent.popUpText(target, this->popUpTextKey, this->getPosition());
		}
	}
}

//Constructor
Enemy::Enemy(const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player, EnemySoundBox& sounds)noexcept
	:statsComponent(level),
	animationComponent(&this->sprite, &texture_sheet), 
	player(player), textureSheet(&texture_sheet), soundBox(sounds),
	popUpTextComponent(player->getFont()),
	attackCount(0), attackCountMAX(INT_MAX), attackColdown(0)
{
	this->playerUsingSkill = &this->player->getUsingSkilltype();
	this->playerUsingSkillDmg = &this->player->getUsingSkilldamage();

	this->initStats();
	this->initSkillsImpactTextures();
	this->initImpactAnimations();
	this->initPopUpTextComponent();
}

Enemy::~Enemy()
{
}

//Accessors
const bool& Enemy::dead()
{
	return this->isDead;
}

//Functions
void Enemy::pauseSounds()
{
	this->soundBox.pauseSounds();
}

void Enemy::resumeSounds()
{
	this->soundBox.resumeSounds();
}
