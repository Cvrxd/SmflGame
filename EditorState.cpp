#include "stdafx.h"
#include "EditorState.h"

///////// Initialisation //////////

void EditorState::initVariables()
{
	this->pauseMenu = NULL;
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
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
	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineThickness(1.f);
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150)); 
	this->selectorRect.setOutlineThickness(2.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setTexture(&this->tileMap->getTileTextureSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new GUI::TextureSelector(
		20.f, 20.f, 500.f, 500.f, this->stateData->gridSize, 
		this->tileMap->getTileTextureSheet(), this->font);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Textures/tiles/test.png");
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("COULD NOT LOAD FONT");
	}
}

void EditorState::initTexts()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(15);
	this->cursorText.setFillColor(sf::Color::White);
}

void EditorState::initButtons()
{
	
}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton("SAVE", 300.f, 40.f, "Save");
	this->pauseMenu->addButton("QUIT", 600.f, 40.f, "Quit");
}

//Constructor
EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();	  
	this->initTexts();
	this->initKeybinds(); 
	this->initPauseMenu();
	this->initButtons(); 
	this->initTileMap();
	this->initGUI();
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->tileMap;
	delete this->pauseMenu;
	delete this->textureSelector;
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
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, this->textureRect);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	//Remove a tile (bugs a bit) FIX LATER
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y);
			}
		}
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

void EditorState::updateGUI(const float& dt)
{
	//TextureSelector
	this->textureSelector->update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive())
	{
		//Selector rect
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
		this->selectorRect.setTextureRect(this->textureRect);
	}

	//Cursor text
	this->cursorText.setString(
		std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y) + '\n' + 
		std::to_string(this->mousePosGrid.x) + " " + std::to_string(this->mousePosGrid.y)
	);
	this->cursorText.setPosition(this->mousPosView.x + 100.f, this->mousPosView.y - 50.f);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
	if (this->pauseMenu->isButtonPressed("SAVE") && this->getKeyTime())
	{
		this->tileMap->saveToFile("map/game_map.txt");
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused)//Unpaused
	{
		this->updateGUI(dt);
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
	if (!this->textureSelector->getActive())
	{
		target.draw(this->selectorRect);
	}
	
	this->textureSelector->render(target);
	target.draw(this->cursorText);
	target.draw(this->sidebar);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->tileMap->render(*target);
	this->renderButtons(*target);
	this->renderGUI(*target);

	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}
}
