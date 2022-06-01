#include "stdafx.h"
#include "PlayerGUI.h"

//==================================
//PlayerGUI=========================
//==================================

//Initialisation
inline void PlayerGUI::initVariables()
{
	this->skillComponent = this->player.getSkillComponent();

	//Posions
	this->mpPotions = &this->skillComponent->getMpPotions();
	this->hpPotions = &this->skillComponent->getHpPotions();

	//Coins Cruystals
	this->coins = &this->statsComponent.coins;
	this->crystals = &this->statsComponent.crystals;
}

inline void PlayerGUI::initStatBars()
{
	this->textures["BAR_BORDER"].loadFromFile("Textures/hud/game_hud/border.png");
	this->textures["HP_BAR"].loadFromFile("Textures/hud/game_hud/hp.png");
	
	sf::Image image;

	image.loadFromFile("Textures/hud/game_hud/mana.png");
	image.createMaskFromColor(sf::Color::White);
	this->textures["MANA_BAR"].loadFromImage(image);

	image.loadFromFile("Textures/hud/game_hud/armor.png");
	image.createMaskFromColor(sf::Color::White);
	this->textures["ARMOR_BAR"].loadFromImage(image);

	this->textures["POTIONS"].loadFromFile("Textures/hud/inventory_hud/items32_simple_transparent2.png");
	
	//Borders
	this->bars.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		this->bars[i].first.setTexture(&this->textures["BAR_BORDER"]);
		this->bars[i].first.setPosition(sf::Vector2f(130.f, static_cast<float>(35 + 20 * (i * 3))));
		this->bars[i].first.setSize(sf::Vector2f(static_cast<float>(450 - (i * 60)), 45.f));

		this->bars[i].second.setPosition(sf::Vector2f(135.f, static_cast<float> (5 + 35 + 20 * (i * 3))));
		this->bars[i].second.setSize(sf::Vector2f(static_cast<float>(450 - (i * 60)), 35.f));
	}

	this->bars[0].second.setTexture(&this->textures["HP_BAR"]);
	this->bars[1].second.setTexture(&this->textures["MANA_BAR"]);
	this->bars[2].second.setTexture(&this->textures["ARMOR_BAR"]);
}

inline void PlayerGUI::initQuickSlotBars()
{
	//Quick slot bars textures
	this->quickSlotBars.resize(7);
	
	for (int i = 0; i < 7; ++i)
	{
		this->quickSlotBars[i].first.setSize(sf::Vector2f(48.f, 48.f));
		this->quickSlotBars[i].first.setFillColor(sf::Color(200,200, 200, 100));
		this->quickSlotBars[i].first.setPosition(static_cast<float>(650 + (i * 100)), 920.f);
		this->quickSlotBars[i].first.setOutlineColor(sf::Color::White);
		this->quickSlotBars[i].first.setOutlineThickness(1.f);
	}

	for (int i = 5; i < 7; ++i)
	{
		this->quickSlotBars[i].second.setPosition(this->quickSlotBars[i].first.getPosition().x + 3, this->quickSlotBars[i].first.getPosition().y + 3);
		this->quickSlotBars[i].first.setFillColor(sf::Color::Transparent);
		//this->quickSlotBars[i].second.setOutlineColor(sf::Color::White);
		//this->quickSlotBars[i].second.setOutlineThickness(1.f);
		this->quickSlotBars[i].second.setSize(sf::Vector2f(44.f, 44.f));
		this->quickSlotBars[i].second.setTexture(&this->textures["POTIONS"]);

	}
	this->quickSlotBars[5].second.setTextureRect(sf::IntRect(224, 0, 32, 32));
	this->quickSlotBars[6].second.setTextureRect(sf::IntRect(192, 0, 32, 32));

}

inline void PlayerGUI::initTextsIcons()
{
	//Textures
	this->textures["ICON_SHEET"].loadFromFile("Textures/hud/game_hud/icons.png");
	this->textures["QUICK_SLOT_HUD"].loadFromFile("Textures/hud/game_hud/arrows.png");
	this->textures["COIN"].loadFromFile("Textures/hud/game_hud/coin.png");
	this->textures["CRYSTAL"].loadFromFile("Textures/hud/game_hud/crystals.png");

	//Game icons
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setTexture(&this->textures["QUICK_SLOT_HUD"]);
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setTextureRect(sf::IntRect(0, 0, 50, 84));
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setSize(sf::Vector2f(60, 100));
	this->iconsSprites["QUICK_SLOT_ARROW_LEFT"].setPosition(520, 895);

	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setTexture(&this->textures["QUICK_SLOT_HUD"]);
	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setTextureRect(sf::IntRect(165, 0, 48, 84));
	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setSize(sf::Vector2f(60, 100));
	this->iconsSprites["QUICK_SLOT_ARROW_RIGHT"].setPosition(1380, 895);

	this->iconsSprites["LEVEL"].setTexture(&this->textures["ICON_SHEET"]);
	this->iconsSprites["LEVEL"].setTextureRect(sf::IntRect(158,54,32,29));
	this->iconsSprites["LEVEL"].setSize(sf::Vector2f(100, 100));
	this->iconsSprites["LEVEL"].setPosition(10,20);

	this->iconsSprites["EXP"].setTexture(&this->textures["ICON_SHEET"]);
	this->iconsSprites["EXP"].setTextureRect(sf::IntRect(149, 87, 40, 11));
	this->iconsSprites["EXP"].setSize(sf::Vector2f(120, 50));
	this->iconsSprites["EXP"].setPosition(1, 120);

	//Exp, LVL, coins text
	this->texts["LEVEL"].setFont(this->font);
	this->texts["LEVEL"].setString(std::to_string(this->statsComponent.level));
	this->texts["LEVEL"].setCharacterSize(65);
	this->texts["LEVEL"].setPosition(45, 25);

	this->texts["EXP"].setFont(this->font);
	this->texts["EXP"].setFillColor(sf::Color::Black);
	this->texts["EXP"].setString(std::to_string(this->statsComponent.exp));
	this->texts["EXP"].setCharacterSize(27);
	this->texts["EXP"].setPosition(55, 122);

	this->texts["COIN"].setFont(this->font);
	this->texts["COIN"].setFillColor(sf::Color::White);
	this->texts["COIN"].setString(std::to_string(*this->coins));
	this->texts["COIN"].setCharacterSize(35);
	this->texts["COIN"].setPosition(65, 220);

	this->texts["CRYSTAL"].setFont(this->font);
	this->texts["CRYSTAL"].setFillColor(sf::Color::White);
	this->texts["CRYSTAL"].setString(std::to_string(*this->crystals));
	this->texts["CRYSTAL"].setCharacterSize(35);
	this->texts["CRYSTAL"].setPosition(65, 300);

	//Potions count
	this->texts["MP_POTIONS"].setFont(this->font);
	this->texts["MP_POTIONS"].setFillColor(sf::Color::White);
	this->texts["MP_POTIONS"].setCharacterSize(30);
	this->texts["MP_POTIONS"].setPosition(this->quickSlotBars[5].first.getPosition().x + 20, this->quickSlotBars[5].first.getPosition().y - 50);
	this->texts["MP_POTIONS"].setString(std::to_string(*this->mpPotions));

	this->texts["HP_POTIONS"].setFont(this->font);
	this->texts["HP_POTIONS"].setFillColor(sf::Color::White);
	this->texts["HP_POTIONS"].setCharacterSize(30);
	this->texts["HP_POTIONS"].setPosition(this->quickSlotBars[6].first.getPosition().x + 20, this->quickSlotBars[6].first.getPosition().y - 50);
	this->texts["HP_POTIONS"].setString(std::to_string(*this->hpPotions));

	//Quick slot text
	for (int i = 0; i < 7; ++i)
	{
		this->texts["SLOT" + std::to_string(i)].setFont(this->font);
		this->texts["SLOT" + std::to_string(i)].setFillColor(sf::Color::White);
		this->texts["SLOT" + std::to_string(i)].setCharacterSize(25);
		this->texts["SLOT" + std::to_string(i)].setString(std::to_string(i+1));
		this->texts["SLOT" + std::to_string(i)].setPosition(static_cast<float>(650 + (i * 100))+ 5, 915.f);
	}
	
	this->texts["SLOT4"].setString("F");
	this->texts["SLOT5"].setString("Q");
	this->texts["SLOT6"].setString("E");
}

inline void PlayerGUI::initAniamtions()
{
	this->sprites["COIN"].setScale(2.f, 2.f);
	this->sprites["COIN"].setPosition(this->texts["COIN"].getPosition().x - 40, this->texts["COIN"].getPosition().y + 7);
	this->animationComponent["COIN"] = { &this->sprites["COIN"], &this->textures["COIN"] };
	this->animationComponent["COIN"].addAnimation("PLAY", 0, 0, 4, 0, 16, 16, 15.f);

	this->sprites["CRYSTAL"].setScale(2.f, 2.f);
	this->sprites["CRYSTAL"].setPosition(this->texts["CRYSTAL"].getPosition().x - 40, this->texts["CRYSTAL"].getPosition().y + 7);
	this->animationComponent["CRYSTAL"] = { &this->sprites["CRYSTAL"], &this->textures["CRYSTAL"] };
	this->animationComponent["CRYSTAL"].addAnimation("PLAY", 0, 0, 3, 0, 16, 16, 15.f);
}

void PlayerGUI::initBuffSkill()
{
	this->quickSlotBars[4].second.setTexture(this->skillsIcons->at(8).second.getTexture());
	this->quickSlotBars[4].second.setPosition(this->quickSlotBars[4].first.getPosition());
	this->quickSlotBars[4].second.setSize(sf::Vector2f(48, 48));
}

void PlayerGUI::setPotionsCount(int& hp, int& mp)
{
	this->hpPotions = &hp;
	this->mpPotions = &mp;
}

void PlayerGUI::initSkillIcons(std::vector<std::pair<SkillType, sf::RectangleShape>>* skillsIcons) 
{
	this->skillsIcons = skillsIcons;
}

//Constructor
PlayerGUI::PlayerGUI(Player& player, sf::Font& font) noexcept
	:player(player), font(font), statsComponent(*this->player.getStatsComponent())
{
	this->initVariables();
	this->initStatBars();
	this->initQuickSlotBars();
	this->initTextsIcons();
	this->initAniamtions();
}

PlayerGUI::~PlayerGUI()
{
}

//Accessors
sf::Texture& PlayerGUI::getCrystalsTexture()
{
	return this->textures["CRYSTAL"];
}

sf::Texture& PlayerGUI::getCoinsTexture()
{
	return this->textures["COIN"];
}

//Functions
void PlayerGUI::addItem()
{
}

void PlayerGUI::addSkill(const SkillType& type)
{
	if (this->index > 3) index = 0;

	this->quickSlotBars[index].second = std::find_if(this->skillsIcons->begin(), this->skillsIcons->end(),
		[&type](std::pair<SkillType, sf::RectangleShape>& temp) {return temp.first == type; }).operator*().second;

	this->quickSlotBars[index].second.setPosition(this->quickSlotBars[index].first.getPosition());

	this->skillComponent->addSkill(type, index);

	++this->index;
}

inline void PlayerGUI::updateAnimations(const float& dt)
{
	for (auto& el : this->animationComponent)
	{
		el.second.play("PLAY", dt, true);
	}
}

inline void PlayerGUI::updateBars()
{
	this->bars[0].second.setSize(sf::Vector2f(
		this->bars[0].first.getSize().x / this->statsComponent.hpMAX * this->statsComponent.hp - 10,
		this->bars[0].second.getSize().y));

	this->bars[1].second.setSize(sf::Vector2f(
		this->bars[1].first.getSize().x / this->statsComponent.magickaMAX * this->statsComponent.magicka - 10,
		this->bars[1].second.getSize().y));

	this->bars[2].second.setSize(sf::Vector2f(
		this->bars[2].first.getSize().x / this->statsComponent.armorMAX * this->statsComponent.armor - 10,
		this->bars[2].second.getSize().y));
}

inline void PlayerGUI::updateTextIcons()
{
	if (this->statsComponent.level == 10)
	{
		this->texts["LEVEL"].setPosition(30, 25);
	}

	if (this->statsComponent.exp < 10)
	{
		this->texts["EXP"].setPosition(55, 122);
	}
	else if(this->statsComponent.exp >= 10 && this->statsComponent.exp < 100)
	{
		this->texts["EXP"].setPosition(50, 122);
	}
	else
	{
		this->texts["EXP"].setPosition(40, 122);
	}

	this->texts["LEVEL"].setString(std::to_string(this->statsComponent.level));
	this->texts["EXP"].setString(std::to_string(this->statsComponent.exp));
	this->texts["CRYSTAL"].setString(std::to_string(this->statsComponent.crystals));
	this->texts["COIN"].setString(std::to_string(this->statsComponent.coins));

	this->texts["MP_POTIONS"].setString(std::to_string(*this->mpPotions));
	this->texts["HP_POTIONS"].setString(std::to_string(*this->hpPotions));
}

void PlayerGUI::update(const float& dt)
{
	this->updateAnimations(dt);
	this->updateBars();
	this->updateTextIcons();
}

inline void PlayerGUI::renderQuickSlotBars(sf::RenderTarget& target)
{
	//Rendering skill bars
	if (this->skillComponent->getKeyTime() && this->statsComponent.magicka != 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			target.draw(this->quickSlotBars[i].first);
			target.draw(this->quickSlotBars[i].second);
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			target.draw(this->quickSlotBars[i].second);
			target.draw(this->quickSlotBars[i].first);
		}
	}

	//rendering buff slot
	if (this->skillComponent->getBuffKeyTime() && this->statsComponent.magicka != 0)
	{
		target.draw(this->quickSlotBars[4].first);
		target.draw(this->quickSlotBars[4].second);
	}
	else
	{
		target.draw(this->quickSlotBars[4].second);
		target.draw(this->quickSlotBars[4].first);
	}

	//Rendering postions
	target.draw(this->quickSlotBars[5].second);
	target.draw(this->quickSlotBars[5].first);

	target.draw(this->quickSlotBars[6].second);
	target.draw(this->quickSlotBars[6].first);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderQuickSlotBars(target);

	//Render sprites
	for (auto& el : this->sprites)
	{
		target.draw(el.second);
	}

	//Render bars
	for (auto& el : this->bars)
	{
		target.draw(el.second);
		target.draw(el.first);
	}

	//Render icons
	for (auto& el : this->iconsSprites)
	{
		target.draw(el.second);
	}

	//Render text
	for (auto& el : this->texts)
	{
		target.draw(el.second);
	}

}

void PlayerGUI::skillsMenUpdate(const float& dt)
{
	this->updateAnimations(dt);
	this->updateTextIcons();
}

//===============================================
//SkillsLevelingComponent========================
//===============================================

//Init functions
inline void SkillsLevelingComponent::initVariables(std::vector<std::pair<SkillType, sf::RectangleShape>>& originalSkillsIcons,
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>>& quickSlotBars)
{
	this->originalSkillsIcons = &originalSkillsIcons;
	this->quickSlotBars = &quickSlotBars;
	this->playerSkills = &this->skillsComponent.getPlayerSkills();

	this->crystalsSprites.reserve(4);
	this->crystalsAnimations.reserve(4);
}

void SkillsLevelingComponent::initSkill(const SkillType& type)
{
	//Skill levels
	this->skillLevels[type] = 1;

	//Icon
	this->skillsIcons[type].setTexture(this->quickSlotBars->at(this->unlockSkillsCount).second.getTexture());
	this->skillsIcons[type].setSize(this->quickSlotBars->at(this->unlockSkillsCount).second.getSize());
	this->skillsIcons[type].setOutlineThickness(1.f);
	this->skillsIcons[type].setOutlineColor(sf::Color::White);

	this->skillsIcons[type].setPosition(this->originalSkillsIcons->at(4).second.getPosition().x,
		this->originalSkillsIcons->at(4).second.getPosition().y + this->offsetY + 70.f * ++this->unlockSkillsCount);

	//Button
	this->buttons[type] = new GUI::Button(this->skillsIcons[type].getPosition().x + 50, this->skillsIcons[type].getPosition().y - 5,
		150.f, 45.f,
		&this->font, "Upgrade", 35,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//Text
	this->texts[type].setPosition(this->skillsIcons[type].getPosition().x + 230, this->skillsIcons[type].getPosition().y + 5);
	this->texts[type].setFillColor(sf::Color::White);
	this->texts[type].setCharacterSize(30);
	this->texts[type].setFont(this->font);
	this->texts[type].setString(std::to_string(this->skillLevels[type] * 10) + "   damage:" + std::to_string(this->skillLevels[type]));

	//Crystal animations
	this->crystalsSprites[type].setScale(2.f, 2.f);
	this->crystalsSprites[type].setPosition(this->texts[type].getPosition().x + 30, this->texts[type].getPosition().y + 5);

	this->crystalsAnimations[type] = { &this->crystalsSprites[type], &this->playerGUI.getCrystalsTexture() };
	this->crystalsAnimations[type].addAnimation("PLAY", 0, 0, 3, 0, 16, 16, 15.f);
}

//Other functions
inline void SkillsLevelingComponent::updateKeyTime(const float& dt)
{
	this->keyTime += 100.f * dt;
}

inline void SkillsLevelingComponent::updateSkillColor(const SkillType& type, const sf::Color& color)
{
	//Skill leveling menu icon color
	this->skillsIcons[type].setOutlineThickness(3.f);
	this->skillsIcons[type].setOutlineColor(color);

	//Skill menu icon color
	auto skill_menu_icon = std::find_if(this->originalSkillsIcons->begin(), this->originalSkillsIcons->end(), [&type](const std::pair<SkillType, sf::RectangleShape>& temp)
		{
			return temp.first == type;
		});
	skill_menu_icon.operator*().second.setOutlineThickness(3.f);
	skill_menu_icon.operator*().second.setOutlineColor(color);

	//Quick slot icon color
	int index;
	for (int i = 0; i < 4; ++i)
	{
		if (this->playerSkills->at(i).first == type)
		{
			index = i;
			break;
		}
	}
	this->quickSlotBars->at(index).second.setOutlineThickness(3.f);
	this->quickSlotBars->at(index).second.setOutlineColor(color);
	this->quickSlotBars->at(index).first.setOutlineThickness(3.f);
	this->quickSlotBars->at(index).first.setOutlineColor(color);
}

inline void SkillsLevelingComponent::playSound(const std::string& sound)
{
	this->guiSounds.sounds[sound].second.play();
}

//Constructors
SkillsLevelingComponent::SkillsLevelingComponent(SkillsComponent& skillsComponent, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds) noexcept
	:skillsComponent(skillsComponent), playerGUI(playerGUI), font(font), guiSounds(guiSounds)
{
}

SkillsLevelingComponent::~SkillsLevelingComponent()
{
	for (auto& el : this->buttons)
	{
		delete el.second;
	}
}

inline void SkillsLevelingComponent::upgradeSkill(const SkillType& type)
{
	if (this->playerGUI.statsComponent.crystals >= this->skillLevels[type] * 10 && this->playerGUI.statsComponent.skillPoints != 0
		&& this->skillLevels[type] != this->skillMaxLevel)
	{
		++this->skillLevels[type];
		--this->playerGUI.statsComponent.skillPoints;

		//Losing crystals
		this->playerGUI.statsComponent.loseCrystals(this->skillLevels[type] * 10);

		//Skills component update
		this->skillsComponent.upgradeSkill(type);

		//Changing color depending on skill level
		switch (this->skillLevels[type])
		{
		case 2:
			this->updateSkillColor(type, sf::Color::Green);
			break;
		case 3:
			this->updateSkillColor(type, sf::Color::Yellow);
			break;
		case 4:
			this->updateSkillColor(type, sf::Color::Magenta);
			break;
		case 5:
			this->updateSkillColor(type, sf::Color::Red);
			break;
		default:
			break;
		}
		
		//Updating text for next level
		this->updateTexts();

		//Sound
		this->playSound("UPGRADE_SKILL");
	}
}

//Functions
inline void SkillsLevelingComponent::updateButtons(sf::Vector2i& mousePosWindow, const float& dt)
{
	for (auto& el : this->buttons)
	{
		el.second->update(mousePosWindow);

		if (el.second->isPressed())
		{
			this->playSound("CLICK");

			if (this->keyTime >= this->keyTimeMax)
			{
				this->upgradeSkill(el.first);
				this->keyTime = 0.f;
			}
			
		}
	}

}

inline void SkillsLevelingComponent::updateTexts()
{
	for (auto& el : this->texts)
	{
		if (this->skillLevels[el.first] == this->skillMaxLevel)
		{
			this->buttons[el.first]->getSfText().setString("Max level");

			el.second.setString("      damage:" + std::to_string(this->skillLevels[el.first]));
		}
		else
		{
			el.second.setString(std::to_string(this->skillLevels[el.first] * 10) + "   damage:" + std::to_string(this->skillLevels[el.first]));
		}
	}
}

inline void SkillsLevelingComponent::updateAnimations(const float& dt)
{
	for (auto& el : this->crystalsAnimations)
	{
		el.second.play("PLAY", dt, true);
	}
}

void SkillsLevelingComponent::update(sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeyTime(dt);
	this->updateButtons(mousePosWindow, dt);
	this->updateAnimations(dt);
}

void SkillsLevelingComponent::render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow)
{
	//Render skill icons
	for (auto& el : this->skillsIcons)
	{
		target.draw(el.second);
	}

	//Render buttons
	for (auto& el : this->buttons)
	{
		el.second->render(target);

		if (el.second->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			target.draw(this->texts[el.first]);
			target.draw(this->crystalsSprites[el.first]);
		}
	}
}

//==================================
//Skills menu=======================
//==================================

//Init functions
inline void SkillsMenu::initBackground(const float& x, const float& y)
{
	//Background
	this->background.setSize(sf::Vector2f(x / 1.5f, y / 1.7f));
	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(x / 2.f - this->background.getSize().x / 2.f, y / 2.f - this->background.getSize().y / 2.f);

	//Stat icons
	this->statIcons.resize(7);
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

}

inline void SkillsMenu::initTexts()
{
	this->texts.resize(11);

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

	this->texts[2].setString("MP: " + std::to_string(this->player.getStatsComponent()->magicka) + "/" + std::to_string(this->player.getStatsComponent()->magickaMAX));
	this->texts[2].setPosition(sf::Vector2f(this->statIcons[2].getPosition().x + 50, this->statIcons[2].getPosition().y));

	this->texts[3].setString("Armor: " + std::to_string(this->player.getStatsComponent()->armor) + "/" + std::to_string(this->player.getStatsComponent()->armorMAX));
	this->texts[3].setPosition(sf::Vector2f(this->statIcons[3].getPosition().x + 50, this->statIcons[3].getPosition().y));

	this->texts[4].setString("Physical damage: " + std::to_string(this->player.getStatsComponent()->damagePhysical));
	this->texts[4].setPosition(sf::Vector2f(this->statIcons[4].getPosition().x + 50, this->statIcons[4].getPosition().y));

	this->texts[5].setString("Magical damage: " + std::to_string(this->player.getStatsComponent()->damageMagical));
	this->texts[5].setPosition(sf::Vector2f(this->statIcons[5].getPosition().x + 50, this->statIcons[5].getPosition().y));

	this->texts[9].setString("Crit rate: " + std::to_string(this->player.getStatsComponent()->critRate));
	this->texts[9].setPosition(sf::Vector2f(this->statIcons[6].getPosition().x + 50, this->statIcons[6].getPosition().y));

	this->texts[6].setString("Stat points: " + std::to_string(this->player.getStatsComponent()->statsPoints));
	this->texts[6].setPosition(sf::Vector2f(this->statIcons[5].getPosition().x, this->statIcons[5].getPosition().y + 150));

	this->texts[7].setString("Skill points: " + std::to_string(this->player.getStatsComponent()->skillPoints));
	this->texts[7].setPosition(sf::Vector2f(this->texts[6].getPosition().x, this->texts[6].getPosition().y + 55));

	this->texts[8].setString("Skills");
	this->texts[8].setCharacterSize(40);
	this->texts[8].setPosition(sf::Vector2f(this->background.getSize().x - 100, this->texts[0].getPosition().y - 20));

}

inline void SkillsMenu::initSkillIcons()
{
	this->skillsIcons.resize(this->skillsSize);
	
	for (int i = 0,  x = static_cast<int>(this->texts[8].getPosition().x) + 100, y = static_cast<int>(this->texts[8].getPosition().y); 
		i < this->skillsIcons.size() - 1; ++i, x+=100)
	{
		this->skillsIcons[i].second.setSize(sf::Vector2f(48, 48));
		this->skillsIcons[i].second.setFillColor(sf::Color::White);
		this->skillsIcons[i].second.setOutlineThickness(1.f);
		this->skillsIcons[i].second.setOutlineColor(sf::Color(200,200,200,200));

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

inline void SkillsMenu::initButtons()
{
	this->buttons["HP_UP"] = new GUI::Button(this->statIcons[0].getPosition().x + 200, this->statIcons[0].getPosition().y + 28,
		70.f, 50.f,
		&this->font, "+", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["MP_UP"] = new GUI::Button(this->statIcons[1].getPosition().x + 200, this->statIcons[1].getPosition().y + 28,
		70.f, 50.f,
		&this->font, "+", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ARMOR_UP"] = new GUI::Button(this->statIcons[2].getPosition().x + 200, this->statIcons[2].getPosition().y + 28,
		70.f, 50.f,
		&this->font, "+", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	for (auto& el : this->skillsIcons)
	{
		this->unclockButtons[el.first] = new GUI::Button(el.second.getPosition().x, el.second.getPosition().y,
			48.f, 48.f,
			&this->font, " ", 50,
			sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 100), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 100)
		);
	}
}

//Other functions
const bool SkillsMenu::getKeyTime() const 
{
	return this->keyTime >= this->keyTimeMax;
}

inline void SkillsMenu::updateKeyTime(const float& dt)
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

inline void SkillsMenu::playSound(const std::string& sound)
{
	this->guiSounds.sounds[sound].second.play();
}

//Constructor
SkillsMenu::SkillsMenu(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& guiSounds, const float& x, const float& y) noexcept
	:player(player), playerGUI(playerGUI), font(font), guiSounds(guiSounds), keyTime(0.f), keyTimeMax(10.f), skillsSize(9),
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
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	for (auto it = this->unclockButtons.begin(); it != unclockButtons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions
void SkillsMenu::unlockSkill(const SkillType& type)
{
	this->playSound("UNLOCK_SKILL");

	this->playerGUI.addSkill(type);
	this->skillsLevelingComponent.initSkill(type);
}

inline void SkillsMenu::updateText()
{
	//Update player stats text
	this->texts[0].setString("EXP: " + std::to_string(this->player.getStatsComponent()->exp) + "/" + std::to_string(this->player.getStatsComponent()->expNext));
	this->texts[1].setString("HP: " + std::to_string(this->player.getStatsComponent()->hp) + "/" + std::to_string(this->player.getStatsComponent()->hpMAX));
	this->texts[2].setString("MP: " + std::to_string(this->player.getStatsComponent()->magicka) + "/" + std::to_string(this->player.getStatsComponent()->magickaMAX));
	this->texts[3].setString("Armor: " + std::to_string(this->player.getStatsComponent()->armor) + "/" + std::to_string(this->player.getStatsComponent()->armorMAX));
	this->texts[4].setString("Physical damage : " + std::to_string(this->player.getStatsComponent()->damagePhysical));
	this->texts[5].setString("Magical damage: " + std::to_string(this->player.getStatsComponent()->damageMagical));
	this->texts[9].setString("Crit rate: " + std::to_string(int(this->player.getStatsComponent()->critRate)) + '%');


	//Skill and Stat points
	this->texts[6].setString("Stat points: " + std::to_string(this->player.getStatsComponent()->statsPoints));
	this->texts[7].setString("Skill points: " + std::to_string(this->player.getStatsComponent()->skillPoints));

}

inline void SkillsMenu::updateButtons(sf::Vector2i& mousePosWindow)
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
			++this->player.getStatsComponent()->magicka;
			++this->player.getStatsComponent()->magickaMAX;
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
				this->playSound("CLICK");

				if (this->player.getStatsComponent()->skillPoints > 0)
				{
					this->unlockSkill(it.operator*().first);
					--this->player.getStatsComponent()->skillPoints;

					if (it == --this->unclockButtons.end())
					{
						delete it.operator*().second;
						this->unclockButtons.erase(it);
						break;
					}
					else
					{
						delete it.operator*().second;
						it = this->unclockButtons.erase(it);
					}

					++this->unlockSkillsCount;
				}
			}
		}
	}
}

void SkillsMenu::update(sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeyTime(dt);
	this->updateButtons(mousePosWindow);
	this->updateText();

	//SKills leveling component
	this->skillsLevelingComponent.update(mousePosWindow, dt);
}

inline void SkillsMenu::renderButtons(sf::RenderTarget& target)
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

//==================================
//Items menu========================
//==================================

//Init functions
inline void ItemsMune::initVariables()
{
	this->playerStats = this->player.getStatsComponent();
}

inline void ItemsMune::initTextures()
{
	this->textures["ITEMS"].loadFromFile("Textures/hud/inventory_hud/items32_simple_transparent.png");
	this->textures["COIN"].loadFromFile("Textures/hud/game_hud/coin.png");
}

inline void ItemsMune::initBackground(const float& x, const float& y)
{
	//Background
	this->background.setSize(sf::Vector2f(x / 1.5f, y / 1.7f + 50));
	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(x / 2.f - this->background.getSize().x / 2.f, y / 2.f - this->background.getSize().y / 2.f);
}

inline void ItemsMune::initItemsIcons()
{
	//Set textures && rect
	itemsIcons[Items::HELMET].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::HELMET].setTextureRect(sf::IntRect(128, 64, 32, 32));

	itemsIcons[Items::ARMOR].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::ARMOR].setTextureRect(sf::IntRect(128 + 32, 64, 32, 32));

	itemsIcons[Items::GLOVES].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::GLOVES].setTextureRect(sf::IntRect(128 + 32 * 2, 64, 32, 32));

	itemsIcons[Items::BOOTS].setSize(sf::Vector2f(32, 32));
	itemsIcons[Items::BOOTS].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::BOOTS].setTextureRect(sf::IntRect(128 + 32 * 3, 64, 32, 32));

	itemsIcons[Items::SWORD].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::SWORD].setTextureRect(sf::IntRect(64, 32, 32, 32));
	
	itemsIcons[Items::STAFF].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::STAFF].setTextureRect(sf::IntRect(224, 0, 32, 32));

	itemsIcons[Items::RING].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::RING].setTextureRect(sf::IntRect(64, 32 * 3, 32, 32));

	itemsIcons[Items::NECKLASE].setTexture(&this->textures["ITEMS"]);
	itemsIcons[Items::NECKLASE].setTextureRect(sf::IntRect(64 + 32, 32 * 3, 32, 32));


	float x = this->background.getPosition().x + 50.f;
	float y = this->background.getPosition().y + 110.f;

	for (auto& el : this->itemsIcons)
	{
		el.second.setSize(sf::Vector2f(32, 32));
		el.second.setOutlineColor(sf::Color::White);
		el.second.setOutlineThickness(1.f);
		el.second.setPosition(x, y);
		
		y += 70;
	}
}

inline void ItemsMune::initTexts()
{
	this->texts["ITEMS_STATS"].setCharacterSize(37);
	this->texts["ITEMS_STATS"].setFillColor(sf::Color::White);
	this->texts["ITEMS_STATS"].setFont(this->font);
	this->texts["ITEMS_STATS"].setString("Items Stats");
	this->texts["ITEMS_STATS"].setPosition(this->background.getPosition().x + 50.f, this->background.getPosition().y + 30.f);

	this->texts["UPGRADE_ITEMS"].setCharacterSize(37);
	this->texts["UPGRADE_ITEMS"].setFillColor(sf::Color::White);
	this->texts["UPGRADE_ITEMS"].setFont(this->font);
	this->texts["UPGRADE_ITEMS"].setString("Items");
	this->texts["UPGRADE_ITEMS"].setPosition(this->background.getSize().x - 100.f, this->background.getPosition().y + 30.f);
}	

inline void ItemsMune::initButtons()
{
	for (auto& el : this->itemsIcons)
	{
		this->unclockButtons[el.first] = new GUI::Button(el.second.getPosition().x + 50, el.second.getPosition().y - 10,
			110.f, 40.f,
			&this->font, "Unlock", 30,
			sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
	}
}

inline void ItemsMune::initAnimations()
{
	for (auto& el : this->unclockButtons)
	{
		this->coinsSprites[el.first].setScale(2.f, 2.f);
		this->coinsSprites[el.first].setPosition(this->itemsIcons[el.first].getPosition().x + 170,
			this->itemsIcons[el.first].getPosition().y + 2);

		this->coinsAnimations[el.first] = { &this->coinsSprites[el.first], &this->textures["COIN"] };
		this->coinsAnimations[el.first].addAnimation("PLAY", 0, 0, 4, 0, 16, 16, 15.f);
	}
}

//Update functions
inline void ItemsMune::updateKeyTime(const float& dt)
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

inline void ItemsMune::updateText()
{
	
}

inline void ItemsMune::updateAnimations(const float& dt)
{
	for (auto& el : this->coinsAnimations)
	{
		el.second.play("PLAY", dt, true);
	}
}

inline void ItemsMune::unlockItem(const Items& item)
{

}

//Render functions
inline void ItemsMune::renderIcons(sf::RenderTarget& target)
{
	for (auto& el : this->itemsIcons)
	{
		target.draw(el.second);
	}
}

//Sound
inline void ItemsMune::playSound(const std::string& sound)
{
	this->guiSounds.sounds[sound].second.play();
}

//Constructors
ItemsMune::ItemsMune(Player& player, PlayerGUI& playerGUI, sf::Font& font, GuiSoundsBox& sounds, const float& x, const float& y) noexcept
	: player(player), playerGui(playerGUI), font(font), guiSounds(sounds), // references
	keyTime(0), keyTimeMax(20.f) // key time
{
	this->initVariables();
	this->initTextures();
	this->initBackground(x, y);
	this->initItemsIcons();
	this->initTexts();
	this->initButtons();
	this->initAnimations();
}

ItemsMune::~ItemsMune()
{
	for (auto& el : this->unclockButtons)
	{
		delete el.second;
	}
	for (auto& el : this->upgradeButtons)
	{
		delete el.second;
	}
}

inline void ItemsMune::renderText(sf::RenderTarget& target)
{
	for (auto& el : this->texts)
	{
		target.draw(el.second);
	}
}

//Functions
inline void ItemsMune::updateButtons(sf::Vector2i& mousePosWindow)
{
	//Updating buttons
	for (auto& el : this->unclockButtons)
	{
		el.second->update(mousePosWindow);

		//Is pressed
		if (el.second->isPressed())
		{
			//Sound
			this->playSound("CLICK");

			//
		}

	}
	for (auto& el : this->upgradeButtons)
	{
		el.second->update(mousePosWindow);

		//Is pressed
		if (el.second->isPressed())
		{
			//Sound
			this->playSound("CLICK");

			//
		}
	}
}

inline void ItemsMune::renderButtons(sf::RenderTarget& target, sf::Vector2i& mousePosWindow)
{
	//Render unlock buttons
	for (auto& el : this->unclockButtons)
	{
		el.second->render(target);

		if (el.second->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			target.draw(this->upgradeTexts[el.first]);
			target.draw(this->coinsSprites[el.first]);
		}
	}

	//Render upgrade buttons
	for (auto& el : this->upgradeButtons)
	{
		el.second->render(target);

		if (el.second->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			target.draw(this->upgradeTexts[el.first]);
			target.draw(this->coinsSprites[el.first]);
		}
	}
}

void ItemsMune::update(sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateAnimations(dt);
	this->updateButtons(mousePosWindow);
}

void ItemsMune::render(sf::RenderTarget& target, sf::Vector2i& mousePosWindow)
{
	target.draw(this->background);

	this->renderButtons(target, mousePosWindow);
	this->renderText(target);
	this->renderIcons(target);
}
