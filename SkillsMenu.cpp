#include "stdafx.h"
#include "PlayerGUI.h"

//Init functions
void SkillsMenu::initBackground(const float& x, const float& y) noexcept
{
	//Background
	this->background.setSize(sf::Vector2f(x / 1.5f, y / 1.7f));
	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(x / 2.f - this->background.getSize().x / 2.f, y / 2.f - this->background.getSize().y / 2.f);

	//Stat icons
	this->statIcons.resize(8);
	this->textures["STAT_ICONS"].loadFromFile("Textures/hud/inventory_hud/items32_simple_transparent.png");

	int i = 0;
	for (auto& el : this->statIcons)
	{
		el.setSize(sf::Vector2f(32, 32));
		el.setTexture(&this->textures["STAT_ICONS"]);
		el.setPosition(this->background.getPosition().x + 50, this->background.getPosition().y + (++i) * 55);
	}

	this->statIcons[0].setTextureRect(sf::IntRect(64, 128, 32, 32)); //Level icon
	this->statIcons[1].setTextureRect(sf::IntRect(96, 32, 32, 32));	 //Hp icon
	this->statIcons[2].setTextureRect(sf::IntRect(96, 128, 32, 32)); //Mp icon
	this->statIcons[3].setTextureRect(sf::IntRect(160, 96, 32, 32)); //Armor icon
	this->statIcons[4].setTextureRect(sf::IntRect(64, 32, 32, 32)); //Phys damage icon
	this->statIcons[5].setTextureRect(sf::IntRect(224, 0, 32, 32)); //Magika damage icon
	this->statIcons[6].setTextureRect(sf::IntRect(128, 32, 32, 32)); //Crit rate icon
	this->statIcons[7].setTextureRect(sf::IntRect(160, 32, 32, 32)); //Miss cnahce icon 
}

void SkillsMenu::initTexts() noexcept
{
	this->texts.resize(12);

	for (auto& el : this->texts)
	{
		el.setFont(this->font);
		el.setCharacterSize(27);
		el.setFillColor(sf::Color::White);
	}

	//Stats text
	this->texts[0].setString("EXP: " + std::to_string(this->player.getStatsComponent()->exp) + "/" + std::to_string(this->player.getStatsComponent()->expNext));
	this->texts[0].setPosition(sf::Vector2f(this->statIcons[0].getPosition().x + 50, this->statIcons[0].getPosition().y));

	this->texts[1].setString("HP: " + std::to_string(this->player.getStatsComponent()->hp) + "/" + std::to_string(this->player.getStatsComponent()->hpMAX));
	this->texts[1].setPosition(sf::Vector2f(this->statIcons[1].getPosition().x + 50, this->statIcons[1].getPosition().y));

	this->texts[2].setString("MP: " + std::to_string(this->player.getStatsComponent()->mp) + "/" + std::to_string(this->player.getStatsComponent()->mpMAX));
	this->texts[2].setPosition(sf::Vector2f(this->statIcons[2].getPosition().x + 50, this->statIcons[2].getPosition().y));

	this->texts[3].setString("Armor: " + std::to_string(this->player.getStatsComponent()->armor) + "/" + std::to_string(this->player.getStatsComponent()->armorMAX));
	this->texts[3].setPosition(sf::Vector2f(this->statIcons[3].getPosition().x + 50, this->statIcons[3].getPosition().y));

	this->texts[4].setString("Physical damage: " + std::to_string(this->player.getStatsComponent()->damagePhysical));
	this->texts[4].setPosition(sf::Vector2f(this->statIcons[4].getPosition().x + 50, this->statIcons[4].getPosition().y));

	this->texts[5].setString("Magical damage: " + std::to_string(this->player.getStatsComponent()->damageMagical));
	this->texts[5].setPosition(sf::Vector2f(this->statIcons[5].getPosition().x + 50, this->statIcons[5].getPosition().y));

	this->texts[9].setString("Crit rate: " + std::to_string(this->player.getStatsComponent()->critRate));
	this->texts[9].setPosition(sf::Vector2f(this->statIcons[6].getPosition().x + 50, this->statIcons[6].getPosition().y));

	this->texts[10].setString("Miss chance: " + std::to_string(this->player.getStatsComponent()->missChance));
	this->texts[10].setPosition(sf::Vector2f(this->statIcons[6].getPosition().x + 50, this->statIcons[6].getPosition().y + 50));

	this->texts[6].setString("Stat points: " + std::to_string(this->player.getStatsComponent()->statsPoints));
	this->texts[6].setPosition(sf::Vector2f(this->statIcons[5].getPosition().x, this->statIcons[5].getPosition().y + 180));

	this->texts[7].setString("Skill points: " + std::to_string(this->player.getStatsComponent()->skillPoints));
	this->texts[7].setPosition(sf::Vector2f(this->texts[6].getPosition().x, this->texts[6].getPosition().y + 55));

	this->texts[8].setString("Skills");
	this->texts[8].setCharacterSize(40);
	this->texts[8].setPosition(sf::Vector2f(this->background.getSize().x - 100, this->texts[0].getPosition().y - 20));

}

void SkillsMenu::initSkillIcons() noexcept
{
	this->skillsIcons.resize(this->skillsSize);

	for (int i = 0, x = static_cast<int>(this->texts[8].getPosition().x) + 100, y = static_cast<int>(this->texts[8].getPosition().y);
		i < this->skillsIcons.size() - 1; ++i, x += 100)
	{
		this->skillsIcons[i].second.setSize(sf::Vector2f(48, 48));
		this->skillsIcons[i].second.setFillColor(sf::Color::White);
		this->skillsIcons[i].second.setOutlineThickness(1.f);
		this->skillsIcons[i].second.setOutlineColor(sf::Color(200, 200, 200, 200));

		if (i % 4 == 0)
		{
			y += 100;
			x = static_cast<int>(this->texts[8].getPosition().x) - 100;
		}
		this->skillsIcons[i].second.setPosition(static_cast<float>(x), static_cast<float>(y));
	}

	this->textures["THUNDER_STRIKE"].loadFromFile("Textures/skills/skill_icons2.png");
	this->skillsIcons[0].first = SkillType::THUNDER_STRIKE;
	this->skillsIcons[0].second.setTexture(&this->textures["THUNDER_STRIKE"]);

	this->textures["DARK_BOLT"].loadFromFile("Textures/skills/skill_icons51.png");
	this->skillsIcons[1].first = SkillType::DARK_BOLT;
	this->skillsIcons[1].second.setTexture(&this->textures["DARK_BOLT"]);

	this->textures["POISON_CLAW"].loadFromFile("Textures/skills/skill_icons39.png");
	this->skillsIcons[2].first = SkillType::POISON_CLAW;
	this->skillsIcons[2].second.setTexture(&this->textures["POISON_CLAW"]);

	this->textures["DARK_POSION"].loadFromFile("Textures/skills/skill_icons50.png");
	this->skillsIcons[3].first = SkillType::DARK_POSION;
	this->skillsIcons[3].second.setTexture(&this->textures["DARK_POSION"]);

	this->textures["BLOOD_SPIKE"].loadFromFile("Textures/skills/skill_icons42.png");
	this->skillsIcons[4].first = SkillType::BLOOD_SPIKE;
	this->skillsIcons[4].second.setTexture(&this->textures["BLOOD_SPIKE"]);

	this->textures["FIRE_EXPLOSION"].loadFromFile("Textures/skills/skill_icons3.png");
	this->skillsIcons[5].first = SkillType::FIRE_EXPLOSION;
	this->skillsIcons[5].second.setTexture(&this->textures["FIRE_EXPLOSION"]);

	this->textures["LIGHTNING_STRIKE"].loadFromFile("Textures/skills/skill_icons23.png");
	this->skillsIcons[6].first = SkillType::LIGHTNING_STRIKE;
	this->skillsIcons[6].second.setTexture(&this->textures["LIGHTNING_STRIKE"]);

	this->textures["HOLY_STRIKE"].loadFromFile("Textures/skills/skill_icons6.png");
	this->skillsIcons[7].first = SkillType::HOLY_STRIKE;
	this->skillsIcons[7].second.setTexture(&this->textures["HOLY_STRIKE"]);

	this->textures["BUFF"].loadFromFile("Textures/skills/skill_icons41.png");
	this->skillsIcons[8].first = SkillType::BUFF;
	this->skillsIcons[8].second.setTexture(&this->textures["BUFF"]);
}

void SkillsMenu::initButtons() noexcept
{
	this->buttons["HP_UP"] = std::make_unique<GUI::Button>(this->statIcons[0].getPosition().x + 200, this->statIcons[0].getPosition().y + 28,
		70.f, 50.f, &this->font, "+", 50);

	this->buttons["MP_UP"] = std::make_unique<GUI::Button>(this->statIcons[1].getPosition().x + 200, this->statIcons[1].getPosition().y + 28,
		70.f, 50.f, &this->font, "+", 50);

	this->buttons["ARMOR_UP"] = std::make_unique<GUI::Button>(this->statIcons[2].getPosition().x + 200, this->statIcons[2].getPosition().y + 28,
		70.f, 50.f, &this->font, "+", 50);

	for (auto& el : this->skillsIcons)
	{
		this->unclockButtons[el.first] = std::make_unique<GUI::Button>(el.second.getPosition().x, el.second.getPosition().y,
			48.f, 48.f,
			&this->font, " ", 50,
			sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 100), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 100)
			);
	}
}

//Update functions
void SkillsMenu::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 100.f * dt;
	}
	else
	{
		this->keyTime = 0;
	}
}

void SkillsMenu::updateText()
{
	//Update player stats text
	this->texts[0].setString("EXP: " + std::to_string(this->player.getStatsComponent()->exp) + "/" + std::to_string(this->player.getStatsComponent()->expNext));
	this->texts[1].setString("HP: " + std::to_string(this->player.getStatsComponent()->hp) + "/" + std::to_string(this->player.getStatsComponent()->hpMAX));
	this->texts[2].setString("MP: " + std::to_string(this->player.getStatsComponent()->mp) + "/" + std::to_string(this->player.getStatsComponent()->mpMAX));
	this->texts[3].setString("Armor: " + std::to_string(this->player.getStatsComponent()->armor) + "/" + std::to_string(this->player.getStatsComponent()->armorMAX));
	this->texts[4].setString("Physical damage : " + std::to_string(this->player.getStatsComponent()->damagePhysical));
	this->texts[5].setString("Magical damage: " + std::to_string(this->player.getStatsComponent()->damageMagical));
	this->texts[9].setString("Crit rate: " + std::to_string(int(this->player.getStatsComponent()->critRate)) + '%');
	this->texts[10].setString("Miss chance: " + std::to_string(int(this->player.getStatsComponent()->missChance)) + '%');


	//Skill and Stat points
	this->texts[6].setString("Stat points: " + std::to_string(this->player.getStatsComponent()->statsPoints));
	this->texts[7].setString("Skill points: " + std::to_string(this->player.getStatsComponent()->skillPoints));

}

void SkillsMenu::updateButtons(sf::Vector2i& mousePosWindow)
{
	//Update all buttons
	if (this->player.getStatsComponent()->statsPoints != 0)
	{
		for (auto& el : this->buttons)
		{
			el.second->update(mousePosWindow);
		}
	}

	for (auto& el : this->unclockButtons)
	{
		el.second->update(mousePosWindow);
	}

	//Is button pressed
	if (this->buttons["HP_UP"]->isPressed() && this->getKeyTime())
	{
		if (this->player.getStatsComponent()->statsPoints > 0)
		{
			++this->player.getStatsComponent()->hp;
			++this->player.getStatsComponent()->hpMAX;
			--this->player.getStatsComponent()->statsPoints;

			this->playSound("CLICK");
		}


	}
	else if (this->buttons["MP_UP"]->isPressed() && this->getKeyTime())
	{
		if (this->player.getStatsComponent()->statsPoints > 0)
		{
			++this->player.getStatsComponent()->mp;
			++this->player.getStatsComponent()->mpMAX;
			--this->player.getStatsComponent()->statsPoints;

			this->playSound("CLICK");
		}
	}
	else if (this->buttons["ARMOR_UP"]->isPressed() && this->getKeyTime())
	{
		if (this->player.getStatsComponent()->statsPoints > 0)
		{
			++this->player.getStatsComponent()->armor;
			++this->player.getStatsComponent()->armorMAX;
			--this->player.getStatsComponent()->statsPoints;

			this->playSound("CLICK");
		}
	}

	int i = 0;

	if (this->unlockSkillsCount != 4)
	{
		for (auto it = this->unclockButtons.begin(); it != this->unclockButtons.end(); ++it, ++i)
		{
			if (it.operator*().second->isPressed() && this->getKeyTime())
			{
				//Sound
				this->playSound("CLICK");

				if (this->player.getStatsComponent()->skillPoints > 0)
				{
					//Unlock
					this->unlockSkill(it.operator*().first);

					//--Player skill points
					--this->player.getStatsComponent()->skillPoints;

					//Delete button
					if (it == --this->unclockButtons.end())
					{
						this->unclockButtons.erase(it);
						break;
					}
					else
					{
						it = this->unclockButtons.erase(it);
					}

					++this->unlockSkillsCount;
				}
			}
		}
	}
}

//Render functions
void SkillsMenu::renderButtons(sf::RenderTarget& target)
{
	if (this->player.getStatsComponent()->statsPoints != 0)
	{
		for (auto& el : this->buttons)
		{
			el.second->render(target);
		}
	}
	for (auto& el : this->unclockButtons)
	{
		el.second->render(target);
	}
}

//Sound functions
void SkillsMenu::playSound(const std::string& sound)
{
	this->guiSounds.sounds[sound].second.play();
}

//Constructor
SkillsMenu::SkillsMenu(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds, const float& x, const float& y) noexcept
	:player(player),
	playerGUI(playerGUI),
	font(font),
	guiSounds(guiSounds),
	keyTime(0.f), keyTimeMax(10.f), skillsSize(9),
	skillsLevelingComponent(*this->player.getSkillComponent(), playerGUI, font, guiSounds)
{
	this->initBackground(x, y);
	this->initTexts();
	this->initSkillIcons();
	this->initButtons();

	//Init other components variables
	this->playerGUI.initSkillIcons(&this->skillsIcons);
	this->playerGUI.initBuffSkill();
	this->skillsLevelingComponent.initVariables(this->skillsIcons, this->playerGUI.quickSlotBars);
}

SkillsMenu::~SkillsMenu()
{
}

//Accessors
const bool SkillsMenu::getKeyTime() const
{
	return this->keyTime >= this->keyTimeMax;
}

//Public unctions
void SkillsMenu::stopSonds()
{
	this->guiSounds.stopSounds();
}

void SkillsMenu::unlockSkill(const SkillType& type)
{
	this->playSound("UNLOCK_SKILL");

	this->playerGUI.addSkill(type);
	this->skillsLevelingComponent.initSkill(type);
}

void SkillsMenu::update(sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeyTime(dt);
	this->updateButtons(mousePosWindow);
	this->updateText();

	//SKills leveling component
	this->skillsLevelingComponent.update(mousePosWindow, dt);
}

void SkillsMenu::render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow)
{
	target.draw(this->background);

	for (auto& el : this->statIcons)
	{
		target.draw(el);
	}
	for (auto& el : this->texts)
	{
		target.draw(el);
	}
	for (auto& el : this->skillsIcons)
	{
		target.draw(el.second);
	}

	this->renderButtons(target);

	//SKills leveling component
	this->skillsLevelingComponent.render(target, mousePosWindow);
}
