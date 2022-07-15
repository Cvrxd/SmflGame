#include "stdafx.h"
#include "PlayerGUI.h"


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
		this->quickSlotBars[i].first.setPosition(static_cast<float>(static_cast<float>(this->window.getSize().x) * 33.f / 100.f + (i * 100)), 920.f);
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
	this->iconsShapes["QUICK_SLOT_ARROW_LEFT"].setTexture(&this->textures["QUICK_SLOT_HUD"]);
	this->iconsShapes["QUICK_SLOT_ARROW_LEFT"].setTextureRect(sf::IntRect(0, 0, 50, 84));
	this->iconsShapes["QUICK_SLOT_ARROW_LEFT"].setSize(sf::Vector2f(60, 100));
	//this->iconsShapes["QUICK_SLOT_ARROW_LEFT"].setPosition(static_cast<float>(this->window.getSize().x) * 27.f / 100.f, 895);

	this->iconsShapes["QUICK_SLOT_ARROW_RIGHT"].setTexture(&this->textures["QUICK_SLOT_HUD"]);
	this->iconsShapes["QUICK_SLOT_ARROW_RIGHT"].setTextureRect(sf::IntRect(165, 0, 48, 84));
	this->iconsShapes["QUICK_SLOT_ARROW_RIGHT"].setSize(sf::Vector2f(60, 100));
	//this->iconsShapes["QUICK_SLOT_ARROW_RIGHT"].setPosition(static_cast<float>(this->window.getSize().x) * 70.f / 100.f, 895);

	this->iconsShapes["LEVEL"].setTexture(&this->textures["ICON_SHEET"]);
	this->iconsShapes["LEVEL"].setTextureRect(sf::IntRect(158,54,32,29));
	this->iconsShapes["LEVEL"].setSize(sf::Vector2f(100, 100));
	this->iconsShapes["LEVEL"].setPosition(10,20);

	this->iconsShapes["EXP"].setTexture(&this->textures["ICON_SHEET"]);
	this->iconsShapes["EXP"].setTextureRect(sf::IntRect(149, 87, 40, 11));
	this->iconsShapes["EXP"].setSize(sf::Vector2f(120, 50));
	this->iconsShapes["EXP"].setPosition(1, 120);

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
		this->texts["SLOT" + std::to_string(i)].setPosition(static_cast<float>(static_cast<float>(this->window.getSize().x) * 33.f / 100.f + (i * 100))+ 5, 915.f);
	}
	
	this->texts["SLOT4"].setString("F");
	this->texts["SLOT5"].setString("Q");
	this->texts["SLOT6"].setString("E");

	this->iconsShapes["QUICK_SLOT_ARROW_RIGHT"].setPosition(this->texts["SLOT6"].getPosition().x + 100.f, 895);
	this->iconsShapes["QUICK_SLOT_ARROW_LEFT"].setPosition(this->texts["SLOT0"].getPosition().x - 100.f, 895);
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

inline void PlayerGUI::initInfoText(const unsigned int& difficulty)
{
	switch (difficulty)
	{
	case 1:
		this->infoText.setFillColor(sf::Color::Magenta);
		break;
	case 2:
		this->infoText.setFillColor(sf::Color::Red);
		break;
	case 3:
		this->infoText.setFillColor(sf::Color::Black);
		break;
	default:
		this->infoText.setFillColor(sf::Color::White);
		break;
	}

	this->infoText.setOutlineThickness (2.f);
	this->infoText.setOutlineColor     (sf::Color::White);
	this->infoText.setFont             (this->font);
	this->infoText.setCharacterSize    (40);
	this->infoText.setString           ("Wave: " + std::to_string(this->wavesCount) + "\nKills: " + std::to_string(this->player.getKillsCount()));

	this->infoText.setPosition(
		static_cast<float>(this->window.getSize().x) - 250.f,
		static_cast<float>(this->window.getPosition().y) + 100.f);
}

//Update functions
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
		this->bars[1].first.getSize().x / this->statsComponent.mpMAX * this->statsComponent.mp - 10,
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
	else if (this->statsComponent.exp >= 10 && this->statsComponent.exp < 100)
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

inline void PlayerGUI::updateInfoText()
{
	this->infoText.setString("Wave: " + std::to_string(this->wavesCount) + "\nKills: " + std::to_string(this->player.getKillsCount()));
}

//Render functions
inline void PlayerGUI::renderQuickSlotBars(sf::RenderTarget& target)
{
	//Rendering skill bars
	if (this->skillComponent->getKeyTime() && this->statsComponent.mp != 0)
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
	if (this->skillComponent->getBuffKeyTime() && this->statsComponent.mp != 0)
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

inline void PlayerGUI::renderInfoText(sf::RenderTarget& target)
{
	target.draw(this->infoText);
}

inline void PlayerGUI::renderStatBars(sf::RenderTarget& target)
{
	//Rendering stat bars
	if (this->statsComponent.hp > 0)
	{
		target.draw(this->bars[0].second);
	}
	if (this->statsComponent.mp > 0)
	{
		target.draw(this->bars[1].second);
	}
	if (this->statsComponent.armor > 0)
	{
		target.draw(this->bars[2].second);
	}

	//Bars borders render
	target.draw(this->bars[0].first);
	target.draw(this->bars[1].first);
	target.draw(this->bars[2].first);
}

//Constructor
PlayerGUI::PlayerGUI(Player& player, sf::Font& font, sf::RenderWindow& window, const int& wavesCount, const unsigned int& difficulty) noexcept
	:
	player(player), font(font), window(window), wavesCount(wavesCount), 
	statsComponent(*this->player.getStatsComponent())
{
	this->initVariables     ();
	this->initStatBars      ();
	this->initQuickSlotBars ();
	this->initTextsIcons    ();
	this->initAniamtions    ();
	this->initInfoText      (difficulty);
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

//Public functions
void PlayerGUI::initBuffSkill()
{
	this->quickSlotBars[4].second.setTexture  (this->skillsIcons->at(8).second.getTexture());
	this->quickSlotBars[4].second.setPosition (this->quickSlotBars[4].first.getPosition());
	this->quickSlotBars[4].second.setSize     (sf::Vector2f(48, 48));
}

void PlayerGUI::setPotionsCount(int& hp, int& mp)
{
	this->hpPotions = &hp;
	this->mpPotions = &mp;
}

void PlayerGUI::initSkillIcons(vectorSkillTypeShape* skillsIcons)
{
	this->skillsIcons = skillsIcons;
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

void PlayerGUI::upgradePlayerBuff(const int& level)
{
	switch (level)
	{
	case 2:
		this->quickSlotBars[4].first.setOutlineThickness(3.f);
		this->quickSlotBars[4].first.setOutlineColor(sf::Color::Green);
		this->quickSlotBars[4].second.setOutlineThickness(3.f);
		this->quickSlotBars[4].second.setOutlineColor(sf::Color::Green);
		break;
	case 3:
		this->quickSlotBars[4].first.setOutlineThickness(3.f);
		this->quickSlotBars[4].first.setOutlineColor(sf::Color::Yellow);
		this->quickSlotBars[4].second.setOutlineThickness(3.f);
		this->quickSlotBars[4].second.setOutlineColor(sf::Color::Yellow);
		break;
	case 4:
		this->quickSlotBars[4].first.setOutlineThickness(3.f);
		this->quickSlotBars[4].first.setOutlineColor(sf::Color::Magenta);
		this->quickSlotBars[4].second.setOutlineThickness(3.f);
		this->quickSlotBars[4].second.setOutlineColor(sf::Color::Magenta);
		break;
	case 5:
		this->quickSlotBars[4].first.setOutlineThickness(3.f);
		this->quickSlotBars[4].first.setOutlineColor(sf::Color::Red);
		this->quickSlotBars[4].second.setOutlineThickness(3.f);
		this->quickSlotBars[4].second.setOutlineColor(sf::Color::Red);
		break;
	default:
		break;
	}
}

void PlayerGUI::update(const float& dt)
{
	this->updateAnimations (dt);
	this->updateBars       ();
	this->updateTextIcons  ();
	this->updateInfoText   ();
}

void PlayerGUI::render(sf::RenderTarget& target, const bool& showInfoText)
{
	this->renderQuickSlotBars (target);
	this->renderStatBars      (target);

	//Render sprites
	for (auto& el : this->sprites)
	{
		target.draw(el.second);
	}

	//Render icons
	for (auto& el : this->iconsShapes)
	{
		target.draw(el.second);
	}

	//Render text
	for (auto& el : this->texts)
	{
		target.draw(el.second);
	}

	if (showInfoText)
	{
		this->renderInfoText(target);
	}

}

void PlayerGUI::skillsMenUpdate(const float& dt)
{
	this->updateAnimations (dt);
	this->updateTextIcons  ();
}

void PlayerGUI::itemsMenuUpdate(const float& dt)
{
	this->updateAnimations (dt);
	this->updateTextIcons  ();
}

