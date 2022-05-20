#include "stdafx.h"
#include "PlayerGUI.h"

inline void PlayerGUI::initVariables()
{
	this->mpPotions = &this->player.getSkillComponent()->getMpPotions();
	this->hpPotions = &this->player.getSkillComponent()->getHpPotions();
}

//Player GUI
inline void PlayerGUI::initStatBars()
{
	this->textures["HP_BAR"].loadFromFile("Textures/hud/game_hud/hp.png");
	this->textures["MANA_BAR"].loadFromFile("Textures/hud/game_hud/mana.png");
	this->textures["ARMOR_BAR"].loadFromFile("Textures/hud/game_hud/armor.png");
	this->textures["BAR_BORDER"].loadFromFile("Textures/hud/game_hud/border.png");

	this->textures["POTIONS"].loadFromFile("Textures/hud/inventory_hud/items32_simple_transparent2.png");
	
	//Borders
	this->bars.resize(3);

	for (int i = 0; i < 3; ++i)
	{
		this->bars[i].first.setTexture(&this->textures["BAR_BORDER"]);
		this->bars[i].first.setPosition(sf::Vector2f(130.f, static_cast<float>(35 + 20 * (i * 3))));
		this->bars[i].first.setSize(sf::Vector2f(static_cast<float>(450 - (i * 80)), 40.f));

		this->bars[i].second.setPosition(sf::Vector2f(135.f, static_cast<float> (2 + 35 + 20 * (i * 3))));
		this->bars[i].second.setSize(sf::Vector2f(static_cast<float>(450 - (i * 80) - 10), 35.f));
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
	//Game icons
	this->textures["ICON_SHEET"].loadFromFile("Textures/hud/game_hud/icons.png");
	this->textures["QUICK_SLOT_HUD"].loadFromFile("Textures/hud/game_hud/arrows.png");

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

	//Exp and LVL text
	this->texts["LEVEL"].setFont(this->font);
	this->texts["LEVEL"].setString(std::to_string(this->player.getStatsComponent()->level));
	this->texts["LEVEL"].setCharacterSize(65);
	this->texts["LEVEL"].setPosition(45, 25);

	this->texts["EXP"].setFont(this->font);
	this->texts["EXP"].setFillColor(sf::Color::Black);
	this->texts["EXP"].setString(std::to_string(this->player.getStatsComponent()->exp));
	this->texts["EXP"].setCharacterSize(27);
	this->texts["EXP"].setPosition(55, 122);

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
		if (i == 5)
		{
			this->texts["SLOT" + std::to_string(i)].setString("Q");
		}
		if (i == 6)
		{
			this->texts["SLOT" + std::to_string(i)].setString("E");
		}
		this->texts["SLOT" + std::to_string(i)].setPosition(static_cast<float>(650 + (i * 100))+ 5, 915.f);

	}
}

inline void PlayerGUI::initItems()
{
	inventoryIcons["HELMET"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["HELMET"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["HELMET"].first.setPosition(1700, 100);
	inventoryIcons["HELMET"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["HELMET"].first.setOutlineThickness(1.f);

	inventoryIcons["ARMOR"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["ARMOR"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["ARMOR"].first.setPosition(1700, 100 + 64);
	inventoryIcons["ARMOR"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["ARMOR"].first.setOutlineThickness(1.f);

	inventoryIcons["GLOVES"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["GLOVES"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["GLOVES"].first.setPosition(1700, 100 + 64 * 2);
	inventoryIcons["GLOVES"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["GLOVES"].first.setOutlineThickness(1.f);

	inventoryIcons["BOOTS"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["BOOTS"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["BOOTS"].first.setPosition(1700, 100 + 64 * 3);
	inventoryIcons["BOOTS"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["BOOTS"].first.setOutlineThickness(1.f);

	inventoryIcons["SWORD"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["SWORD"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["SWORD"].first.setPosition(1700 - 64, 100 + 64 * 2);
	inventoryIcons["SWORD"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["SWORD"].first.setOutlineThickness(1.f);

	inventoryIcons["STAFF"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["STAFF"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["STAFF"].first.setPosition(1700 + 64, 100 + 64 * 2);
	inventoryIcons["STAFF"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["STAFF"].first.setOutlineThickness(1.f);

	inventoryIcons["RING"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["RING"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["RING"].first.setPosition(1700 - 64, 100 + 64);
	inventoryIcons["RING"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["RING"].first.setOutlineThickness(1.f);

	inventoryIcons["NECKLASE"].first.setSize(sf::Vector2f(32, 32));
	inventoryIcons["NECKLASE"].first.setFillColor(sf::Color(200, 200, 200, 100));
	inventoryIcons["NECKLASE"].first.setPosition(1700 + 64, 100 + 64);
	inventoryIcons["NECKLASE"].first.setOutlineColor(sf::Color::White);
	inventoryIcons["NECKLASE"].first.setOutlineThickness(1.f);
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
PlayerGUI::PlayerGUI(Player& player, sf::Font& font)
	:player(player), font(font), statsComponent(*this->player.getStatsComponent())
{
	this->initVariables();
	this->initStatBars();
	this->initQuickSlotBars();
	this->initTextsIcons();
	this->initItems();
}

PlayerGUI::~PlayerGUI()
{
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

	this->player.getSkillComponent()->addSkill(type, index);

	++this->index;
}

inline void PlayerGUI::updateBars()
{
	this->bars[0].second.setSize(sf::Vector2f(
		this->bars[0].first.getSize().x / this->player.getStatsComponent()->hpMAX * this->player.getStatsComponent()->hp - 10,
		this->bars[0].second.getSize().y));

	this->bars[1].second.setSize(sf::Vector2f(
		this->bars[1].first.getSize().x / this->player.getStatsComponent()->magickaMAX * this->player.getStatsComponent()->magicka - 10,
		this->bars[1].second.getSize().y));

	this->bars[2].second.setSize(sf::Vector2f(
		this->bars[2].first.getSize().x / this->player.getStatsComponent()->armorMAX * this->player.getStatsComponent()->armor - 10,
		this->bars[2].second.getSize().y));
}

inline void PlayerGUI::updateTextIcons()
{
	if (this->player.getStatsComponent()->level == 10)
	{
		this->texts["LEVEL"].setPosition(30, 25);
	}

	if (this->player.getStatsComponent()->exp < 10)
	{
		this->texts["EXP"].setPosition(55, 122);
	}
	else if(this->player.getStatsComponent()->exp >= 10 && this->player.getStatsComponent()->exp < 100)
	{
		this->texts["EXP"].setPosition(50, 122);
	}
	else
	{
		this->texts["EXP"].setPosition(40, 122);
	}

	this->texts["LEVEL"].setString(std::to_string(this->player.getStatsComponent()->level));
	this->texts["EXP"].setString(std::to_string(this->player.getStatsComponent()->exp));

	this->texts["MP_POTIONS"].setString(std::to_string(*this->mpPotions));
	this->texts["HP_POTIONS"].setString(std::to_string(*this->hpPotions));
}

void PlayerGUI::update(const float& dt)
{
	this->updateBars();
	this->updateTextIcons();
}

void PlayerGUI::render(sf::RenderTarget& target)
{
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

	//Render quick slots
	if (this->player.getSkillComponent()->getKeyTime() && this->statsComponent.magicka != 0)
	{
		for (auto& el : this->quickSlotBars)
		{
			target.draw(el.first);
			target.draw(el.second);
		}
	}
	else
	{
		for (auto& el : this->quickSlotBars)
		{
			target.draw(el.second);
			target.draw(el.first);
		}
	}

	//Render Inventory
	for (auto& el : this->inventoryIcons)
	{
		target.draw(el.second.first);
		target.draw(el.second.second);
	}

	//Render text
	for (auto& el : this->texts)
	{
		target.draw(el.second);
	}
}


//Skills Menu 

//Init functions
inline void SkillsMenu::initBackground(const float& x, const float& y)
{
	//Background
	this->background.setSize(sf::Vector2f(x / 1.5f, y / 1.7f));
	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(x / 2.f - this->background.getSize().x / 2.f, y / 2.f - this->background.getSize().y / 2.f);

	//Stat icons
	this->statIcons.resize(6);
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
}

inline void SkillsMenu::initTexts()
{
	this->texts.resize(10);

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

	this->texts[6].setString("Stat points: " + std::to_string(this->player.getStatsComponent()->statsPoints));
	this->texts[6].setPosition(sf::Vector2f(this->statIcons[5].getPosition().x, this->statIcons[5].getPosition().y + 100));

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
		i < this->skillsIcons.size(); ++i, x+=100)
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

	this->textures["RED_BLADES"].loadFromFile("Textures/skills/skill_icons43.png");
	this->skillsIcons[0].first = SkillType::RED_BLADES;
	this->skillsIcons[0].second.setTexture(&this->textures["RED_BLADES"]);

	this->textures["WATER_SPIKE"].loadFromFile("Textures/skills/skill_icons47.png");
	this->skillsIcons[1].first = SkillType::WATER_SPIKE;
	this->skillsIcons[1].second.setTexture(&this->textures["WATER_SPIKE"]);

	this->textures["THUNDER_STRIKE"].loadFromFile("Textures/skills/skill_icons2.png");
	this->skillsIcons[2].first = SkillType::THUNDER_STRIKE;
	this->skillsIcons[2].second.setTexture(&this->textures["THUNDER_STRIKE"]);

	this->textures["DARK_BOLT"].loadFromFile("Textures/skills/skill_icons51.png");
	this->skillsIcons[3].first = SkillType::DARK_BOLT;
	this->skillsIcons[3].second.setTexture(&this->textures["DARK_BOLT"]);

	this->textures["POISON_CLAW"].loadFromFile("Textures/skills/skill_icons39.png");
	this->skillsIcons[4].first = SkillType::POISON_CLAW;
	this->skillsIcons[4].second.setTexture(&this->textures["POISON_CLAW"]);

	this->textures["DARK_POSION"].loadFromFile("Textures/skills/skill_icons50.png");
	this->skillsIcons[5].first = SkillType::DARK_POSION;
	this->skillsIcons[5].second.setTexture(&this->textures["DARK_POSION"]);

	this->textures["BLOOD_SPIKE"].loadFromFile("Textures/skills/skill_icons42.png");
	this->skillsIcons[6].first = SkillType::BLOOD_SPIKE;
	this->skillsIcons[6].second.setTexture(&this->textures["BLOOD_SPIKE"]);

	this->textures["FIRE_EXPLOSION"].loadFromFile("Textures/skills/skill_icons3.png");
	this->skillsIcons[7].first = SkillType::FIRE_EXPLOSION;
	this->skillsIcons[7].second.setTexture(&this->textures["FIRE_EXPLOSION"]);

	this->textures["LIGHTNING_STRIKE"].loadFromFile("Textures/skills/skill_icons23.png");
	this->skillsIcons[8].first = SkillType::LIGHTNING_STRIKE;
	this->skillsIcons[8].second.setTexture(&this->textures["LIGHTNING_STRIKE"]);

	this->textures["HOLY_STRIKE"].loadFromFile("Textures/skills/skill_icons6.png");
	this->skillsIcons[9].first = SkillType::HOLY_STRIKE;
	this->skillsIcons[9].second.setTexture(&this->textures["HOLY_STRIKE"]);
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

//Constructor
SkillsMenu::SkillsMenu(Player& player, PlayerGUI& playerGUI, sf::Font& font, const float& x, const float& y)
	:player(player), playerGUI(playerGUI), font(font), keyTime(0.f), keyTimeMax(10.f), skillsSize(10)
{
	this->initBackground(x, y);
	this->initTexts();
	this->initSkillIcons();
	this->initButtons();
	this->playerGUI.initSkillIcons(&this->skillsIcons);
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
	this->playerGUI.addSkill(type);
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
	
	//Skill and Stat points
	this->texts[6].setString("Stat points: " + std::to_string(this->player.getStatsComponent()->statsPoints));
	this->texts[7].setString("Skill points: " + std::to_string(this->player.getStatsComponent()->skillPoints));

}

inline void SkillsMenu::updateButtons(sf::Vector2i& mousePosWindow)
{
	//Update all buttons
	for (auto& el : this->buttons)
	{
		el.second->update(mousePosWindow);
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
		}
	}
	else if (this->buttons["MP_UP"]->isPressed() && this->getKeyTime())
	{
		if (this->player.getStatsComponent()->statsPoints > 0)
		{
			++this->player.getStatsComponent()->magicka;
			++this->player.getStatsComponent()->magickaMAX;
			--this->player.getStatsComponent()->statsPoints;
		}
	}
	else if (this->buttons["ARMOR_UP"]->isPressed() && this->getKeyTime())
	{
		if (this->player.getStatsComponent()->statsPoints > 0)
		{
			++this->player.getStatsComponent()->armor;
			++this->player.getStatsComponent()->armorMAX;
			--this->player.getStatsComponent()->statsPoints;
		}
	}
	
	int i = 0;
	for (auto it = this->unclockButtons.begin(); it != this->unclockButtons.end(); ++it, ++i)
	{
		if (it.operator*().second->isPressed() && this->getKeyTime())
		{
			if (this->player.getStatsComponent()->skillPoints > 0)
			{
				this->unlockSkill(it.operator*().first);
				--this->player.getStatsComponent()->skillPoints;

				if (it == --this->unclockButtons.end())
				{
					std::cout << 1;
					delete it.operator*().second;
					this->unclockButtons.erase(it);
					break;
				}
				else
				{
					delete it.operator*().second;
					it = this->unclockButtons.erase(it);
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
}

inline void SkillsMenu::renderButtons(sf::RenderTarget& target)
{
	for (auto& el : this->buttons)
	{
		el.second->render(target);
	}
	for (auto& el : this->unclockButtons)
	{
		el.second->render(target);
	}
}

void SkillsMenu::render(sf::RenderTarget& target)
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
	
}