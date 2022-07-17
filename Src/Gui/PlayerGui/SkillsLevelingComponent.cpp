#include <stdafx.h>
#include <Gui/PlayerGui/PlayerGUI.h>

//Init functions
void SkillsLevelingComponent::initVariables(VectorSkillIcons& originalSkillsIcons, VectorQuickSlotBars& quickSlotBars)
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
	this->buttons[type] = std::make_unique<GUI::Button>(
		this->skillsIcons[type].getPosition().x + 50, this->skillsIcons[type].getPosition().y - 5,
		150.f, 45.f, &this->font, "Upgrade", 35);

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

//Update functions
void SkillsLevelingComponent::updateButtons(sf::Vector2i& mousePosWindow, const float& dt)
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

void SkillsLevelingComponent::updateTexts()
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

void SkillsLevelingComponent::updateAnimations(const float& dt)
{
	for (auto& el : this->crystalsAnimations)
	{
		el.second.play("PLAY", dt, true);
	}
}

void SkillsLevelingComponent::updateKeyTime(const float& dt)
{
	this->keyTime += 100.f * dt;
}

void SkillsLevelingComponent::updateSkillColor(const SkillType& type, const sf::Color& color)
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
	int index = 0;

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

void SkillsLevelingComponent::upgradeSkill(const SkillType& type)
{
	if (this->playerGUI.statsComponent.crystals >= this->skillLevels[type] * this->skillCostModifier && this->playerGUI.statsComponent.skillPoints != 0
		&& this->skillLevels[type] != this->skillMaxLevel)
	{
		++this->skillLevels[type];
		--this->playerGUI.statsComponent.skillPoints;

		//Losing crystals
		this->playerGUI.statsComponent.loseCrystals(this->skillLevels[type] * this->skillCostModifier);

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
	}
}

//Sound functions
 void SkillsLevelingComponent::playSound(const std::string& sound)
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

}

//Public functions
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
