#include <stdafx.h>
#include <Gui/PlayerGui/PlayerGUI.h>
//Init functions
void ItemsMune::initVariables() noexcept
{
	this->playerStats = this->player.getStatsComponent();
}

void ItemsMune::initTextures() noexcept
{
	this->textures["ITEMS"].loadFromFile("Textures/hud/inventory_hud/items32_simple_transparent.png");
	this->textures["COIN"].loadFromFile("Textures/hud/game_hud/coin.png");
}

void ItemsMune::initBackground(const float& x, const float& y) noexcept
{
	//Background
	this->background.setSize(sf::Vector2f(x / 1.5f, y / 1.7f + 50));
	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(x / 2.f - this->background.getSize().x / 2.f, y / 2.f - this->background.getSize().y / 2.f);
}

void ItemsMune::initItemsIcons() noexcept
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

void ItemsMune::initTexts() noexcept
{
	//Main text
	this->mainText.first.setCharacterSize(37);
	this->mainText.first.setFillColor(sf::Color::White);
	this->mainText.first.setFont(this->font);
	this->mainText.first.setString("Items Stats");
	this->mainText.first.setPosition(this->background.getPosition().x + 100.f, this->background.getPosition().y + 30.f);

	this->mainText.second.setCharacterSize(37);
	this->mainText.second.setFillColor(sf::Color::White);
	this->mainText.second.setFont(this->font);
	this->mainText.second.setString("Items");
	this->mainText.second.setPosition(this->background.getSize().x - 100.f, this->background.getPosition().y + 30.f);

	//Items text
	for (auto& el : this->itemsIcons)
	{
		this->upgradeTexts[el.first].setCharacterSize(30);
		this->upgradeTexts[el.first].setFillColor(sf::Color::White);
		this->upgradeTexts[el.first].setFont(this->font);
		this->upgradeTexts[el.first].setString("50");
		this->upgradeTexts[el.first].setPosition(el.second.getPosition().x + 175.f, el.second.getPosition().y - 2);
	}
}

void ItemsMune::initButtons() noexcept
{
	for (auto& el : this->itemsIcons)
	{
		this->unclockButtons[el.first] = std::make_unique<GUI::Button>(
			el.second.getPosition().x + 50, el.second.getPosition().y - 10,
			110.f, 40.f, &this->font, "Unlock", 30);
	}
}

void ItemsMune::initAnimations() noexcept
{
	for (auto& el : this->unclockButtons)
	{
		this->coinsSprites[el.first].setScale(2.f, 2.f);

		this->coinsSprites[el.first].setPosition(this->itemsIcons[el.first].getPosition().x + 210,
			this->itemsIcons[el.first].getPosition().y + 2);

		this->coinsAnimations[el.first] = { &this->coinsSprites[el.first], &this->textures["COIN"] };
		this->coinsAnimations[el.first].addAnimation("PLAY", 0, 0, 4, 0, 16, 16, 15.f);
	}
}

void ItemsMune::initOffsets() noexcept
{
	this->offsetX = this->mainText.second.getPosition().x - 100.f;
	this->offsetY = this->itemsIcons.begin().operator*().second.getPosition().y;
}

//Update functions
void ItemsMune::updateItemGrade(const Items& item, const sf::Color& color)
{
	//Color update
	this->itemsIcons[item].setOutlineThickness(3.f);
	this->upgradeItemsIcons[item].setOutlineThickness(3.f);

	this->itemsIcons[item].setOutlineColor(color);
	this->upgradeItemsIcons[item].setOutlineColor(color);

	//Stats text update
	if (item == Items::NECKLASE && item == Items::RING)
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Mp: " + std::to_string(this->itemsLvl[item]));
	}
	else if (item == Items::SWORD)
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Damage: " + std::to_string(this->itemsLvl[item])
			+ " Crit rate: " + std::to_string(this->itemsLvl[item]) + '%');
	}
	else if (item == Items::STAFF)
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Magical Damage: " + std::to_string(this->itemsLvl[item]));
	}
	else
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Armor: " + std::to_string(this->itemsLvl[item]));
	}

	//Upgrade text update
	this->upgradeTexts[item].setString(std::to_string(this->itemsLvl[item] * 20));
}

//Update functions
void ItemsMune::updateKeyTime(const float& dt)
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

void ItemsMune::updateAnimations(const float& dt)
{
	for (auto& el : this->coinsAnimations)
	{
		el.second.play("PLAY", dt, true);
	}
}

void ItemsMune::unlockItem(const Items& item)
{
	//Item lvl
	this->itemsLvl[item] = 1;
	++this->unlockedItemsCount;
	this->playerStats->upgradeItem(item, this->itemsLvl[item]);

	//Stat text
	this->statsTexts[item].setCharacterSize(30);
	this->statsTexts[item].setFillColor(sf::Color::White);
	this->statsTexts[item].setFont(this->font);
	this->statsTexts[item].setPosition(this->itemsIcons[item].getPosition().x + 70, this->itemsIcons[item].getPosition().y);

	if (item == Items::NECKLASE && item == Items::RING)
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Mp: " + std::to_string(this->itemsLvl[item]));
	}
	else if (item == Items::SWORD)
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Damage: " + std::to_string(this->itemsLvl[item])
			+ " Crit rate: " + std::to_string(this->itemsLvl[item]) + '%');
	}
	else if (item == Items::STAFF)
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Magical Damage: " + std::to_string(this->itemsLvl[item]));
	}
	else
	{
		this->statsTexts[item].setString("lvl:" + std::to_string(this->itemsLvl[item]) + "  Armor: " + std::to_string(this->itemsLvl[item]));
	}

	//Create another icon
	this->upgradeItemsIcons[item].setOutlineThickness(1.f);
	this->upgradeItemsIcons[item].setOutlineColor(sf::Color::White);
	this->upgradeItemsIcons[item].setSize(this->itemsIcons[item].getSize());
	this->upgradeItemsIcons[item].setTexture(this->itemsIcons[item].getTexture());
	this->upgradeItemsIcons[item].setTextureRect(this->itemsIcons[item].getTextureRect());
	this->upgradeItemsIcons[item].setPosition(this->offsetX, this->offsetY);

	//Create upgrade button
	this->upgradeButtons[item] = std::make_unique<GUI::Button>(this->offsetX + 40.f, this->offsetY - 12.f,
		110.f, 40.f,
		&this->font, "Upgrade", 30,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

	//Move coins sprites
	this->coinsSprites[item].setPosition(this->offsetX + 220.f, this->offsetY);

	//Move upgrade text
	this->upgradeTexts[item].setPosition(this->offsetX + 180.f, this->offsetY - 4.f);
	this->upgradeTexts[item].setString(std::to_string(this->itemsLvl[item] * 20));

	//Update offset
	this->offsetY += 70.f;
}

void ItemsMune::upgradeItem(const Items& item)
{
	++this->itemsLvl[item];

	switch (this->itemsLvl[item])
	{
	case 2:
		this->updateItemGrade(item, sf::Color::Green);
		this->playerStats->upgradeItem(item, this->itemsLvl[item]);
		break;
	case 3:
		this->updateItemGrade(item, sf::Color::Yellow);
		this->playerStats->upgradeItem(item, this->itemsLvl[item]);
		break;
	case 4:
		this->updateItemGrade(item, sf::Color::Magenta);
		this->playerStats->upgradeItem(item, this->itemsLvl[item]);
		break;
	case 5:
		this->updateItemGrade(item, sf::Color::Red);
		this->playerStats->upgradeItem(item, this->itemsLvl[item]);
		break;
	default:
		break;
	}

	//If max level
	if (this->itemsLvl[item] == this->maxLevel)
	{
		this->upgradeButtons[item]->setText("MAX level");
		this->upgradeTexts[item].setString("");
	}
}

void ItemsMune::updateButtons(sf::Vector2i& mousePosWindow)
{
	//Unlock items buttons
	for (auto it = this->unclockButtons.begin(); it != this->unclockButtons.end(); ++it)
	{
		it.operator*().second->update(mousePosWindow);

		if (it.operator*().second->isPressed() && this->keyTime >= this->keyTimeMax)
		{
			this->playSound("CLICK");

			if (this->playerStats->coins >= this->itemUnlockCost)
			{
				//Sound
				this->playSound("UNLOCK_ITEM");

				//Unlock
				this->unlockItem(it.operator*().first);

				//Player lose coins
				this->playerStats->loseCoins(this->itemUnlockCost);

				//Delete unlock button
				if (it == --this->unclockButtons.end())
				{
					this->unclockButtons.erase(it);
					break;
				}
				else
				{
					it = this->unclockButtons.erase(it);
				}
			}
		}
	}

	//Upgrade buttons
	for (auto& el : this->upgradeButtons)
	{
		el.second->update(mousePosWindow);

		//Is pressed
		if (el.second->isPressed() && this->keyTime >= this->keyTimeMax)
		{
			//Sound
			this->playSound("CLICK");

			//Upgrade item
			if (this->playerStats->coins >= this->itemsLvl[el.first] * this->itemCostModidfier && this->itemsLvl[el.first] != this->maxLevel)
			{
				//Sound
				this->playSound("UPGRADE_ITEM");

				//Upgrade
				this->playerStats->loseCoins(this->itemsLvl[el.first] * this->itemCostModidfier);
				this->upgradeItem(el.first);
			}
		}
	}
}

//Render functions
void ItemsMune::renderButtons(sf::RenderTarget& target, sf::Vector2i& mousePosWindow)
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

void ItemsMune::renderIcons(sf::RenderTarget& target)
{
	for (auto& el : this->itemsIcons)
	{
		target.draw(el.second);
	}

	for (auto& el : this->upgradeItemsIcons)
	{
		target.draw(el.second);
	}
}

void ItemsMune::renderText(sf::RenderTarget& target)
{
	target.draw(this->mainText.first);
	target.draw(this->mainText.second);

	for (auto& el : this->statsTexts)
	{
		target.draw(el.second);
	}
}

//Sound functions
void ItemsMune::playSound(const std::string& sound)
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
	this->initOffsets();
}

ItemsMune::~ItemsMune()
{
}

//Public functions
void ItemsMune::stopSounds()
{
	this->guiSounds.stopSounds();
}

void ItemsMune::update(sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeyTime(dt);
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
