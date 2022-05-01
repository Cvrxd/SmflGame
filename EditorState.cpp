#include "stdafx.h"
#include "EditorState.h"

///////// Initialisation //////////

void EditorState::initVariables()
{
	this->pauseMenu = NULL;
}

void EditorState::initBackground()
{
	
}

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

void EditorState::initGUI()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("COULD NOT LOAD FONT");
	}
}

void EditorState::initButtons()
{
	
}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	//this->pauseMenu->addButton("CONTINUE", 400.f, -20.f, "Continue");
	this->pauseMenu->addButton("QUIT", 600.f, 40.f, "Quit");
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();	  
	this->initKeybinds(); 
	this->initPauseMenu();
	this->initButtons(); 
	this->initGUI();
	this->initTileMap();
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->tileMap;
	delete this->pauseMenu;
}

// Functions 

// update
void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpausedState();
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Add a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y);
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

void EditorState::updateGUI()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused)//Unpaused
	{
		this->updateGUI();
		this->updateButtons();
		this->updateEditorInput(dt);
	}
	else //Paused
	{
		this->pauseMenu->update(this->mousPosView);
		this->updatePauseMenuButtons();
	}

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

void EditorState::renderGUI(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderButtons(*target);
	this->renderGUI(*target);
	this->tileMap->render(*target);

	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}

	//REMOVE LATER JUST DEBUG!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousPosView.x, this->mousPosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y));
	target->draw(mouseText);
}
