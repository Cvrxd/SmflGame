#include "stdafx.h"
#include "EditorState.h"

///////// Initialisation //////////

void EditorState::initVariables()
{
}

void EditorState::initBackground()
{
	
}

// Keybinds init from ini
void EditorState::initKeybinds()
{
	std::ifstream ifs("Configs/editorstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key_value = "";

		while (ifs >> key >> key_value)
		{
			this->keybinds[key] = this->supportedKeys->at(key_value);
		}
	}

	ifs.close();
}

//fonts
void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("COULD NOT LOAD FONT");
	}
}

//buttons init
void EditorState::initButtons()
{
	
}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();	  //init fonts 
	this->initKeybinds(); //init key binds from ini
	this->initButtons();  //init buttons 
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Functions 

// update
void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
	}
}

void EditorState::updateButtons()
{
	//updates all buttons
	for (auto& el : this->buttons)
	{
		el.second->update(this->mousPosView);
	}
}

void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();
}

//render
void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& el : this->buttons)
	{
		el.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderButtons(*target);

	//REMOVE LATER JUST DEBUG!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousPosView.x, this->mousPosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y));

	target->draw(mouseText);*/
}
