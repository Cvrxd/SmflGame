#include "stdafx.h"
#include "MainMenuState.h"

//Initialisation
inline void MainMenuState::initVariables()
{

}

inline void MainMenuState::initSounds()
{
	//Init background music
	this->sounds.music.openFromFile ("Sounds/main_menu/main_menu.ogg");
	this->sounds.music.setVolume    (5.f);
	this->sounds.music.setLoop      (true);
	
	//Play background music
	this->sounds.music.play();

	//Click sound
	this->sounds.clickSound.first.loadFromFile ("Sounds/main_menu/click.wav");
	this->sounds.clickSound.second.setBuffer   (this->sounds.clickSound.first);
	this->sounds.clickSound.second.setVolume   (10.f);
}

inline void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Textures/background/mainmenu_background.png"))
	{
		throw("Failed to load mainmenu_background.png");
	}

	this->background.setTexture(&this->backgroundTexture); 
}

inline void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Configs/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key       = "";
		std::string key_value = "";

		while (ifs >> key >> key_value)
		{
			this->keybinds[key] = this->supportedKeys->at(key_value);
		}
	}

	ifs.close();
}

inline void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

inline void MainMenuState::initGUI()
{
	//Text
	this->difficultyText.setFont          (this->font);
	this->difficultyText.setCharacterSize (50);
	this->difficultyText.setFillColor     (sf::Color::White);
	this->difficultyText.setString        ("Difficulty: ");

	this->difficultyText.setPosition(
		static_cast<float>(this->window->getSize().x) - 550.f, 
		static_cast<float>(this->window->getPosition().y) + 100.f);

	this->difficultyLvlText.setFont             (this->font);
	this->difficultyLvlText.setCharacterSize    (50);
	this->difficultyLvlText.setFillColor        (sf::Color::Magenta);
	this->difficultyLvlText.setString           ("Normal");
	this->difficultyLvlText.setOutlineThickness (2.f);
	this->difficultyLvlText.setOutlineColor     (sf::Color::White);

	this->difficultyLvlText.setPosition(this->difficultyText.getPosition().x + 300.f, this->difficultyText.getPosition().y);

	//Buttons
	this->buttons["GAME_STATE"] = std::make_unique<GUI::Button>(100.f, 100.f, 300.f, 70.f,
		&this->font, "New Game", 70);

	this->buttons["SETTINGS_STATE"] = std::make_unique<GUI::Button>(100.f, 250.f, 300.f, 70.f,
		&this->font, "Settings", 70);

	this->buttons["EDITOR_STATE"] = std::make_unique<GUI::Button>(100.f, 400.f, 250.f, 70.f,
		&this->font, "Editor", 70);

	this->buttons["EXIT_STATE"] = std::make_unique<GUI::Button>(100.f, 550.f, 180.f, 75.f,
		&this->font, "Quit", 70);

	this->buttons["DIFFICULTY_LESS"] = std::make_unique<GUI::Button>(this->difficultyLvlText.getPosition().x - 30.f, this->difficultyLvlText.getPosition().y + 50.f,
		100.f, 75.f,
		&this->font, "<-", 60,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

	this->buttons["DIFFICULTY_MORE"] = std::make_unique<GUI::Button>(this->difficultyLvlText.getPosition().x + 80.f, this->difficultyLvlText.getPosition().y + 50.f,
		100.f, 75.f,
		&this->font, "->", 60,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
}

inline void MainMenuState::initRecrodsInfo()
{
	//Swith records info button
	this->buttons["RECORDS"] = std::make_unique<GUI::Button>(this->difficultyText.getPosition().x, this->difficultyText.getPosition().y + 150.f,
		180.f, 75.f,
		&this->font, "Records", 50);

	//Texts
	//this->texts[""]
}

inline void MainMenuState::loadRecordInfo()
{
	std::ifstream ifile("Saves/Records/normal_record.txt");

	if (ifile.is_open())
	{
		ifile >> this->normalRecordInfo.bossKills >> this->normalRecordInfo.kills >> this->normalRecordInfo.wavesCount >>
			this->normalRecordInfo.coins >> this->normalRecordInfo.crystals;
	}
	else
	{
		throw("UNABLE TO OPEN Saves/Records/normal_record.txt");
	}

	ifile.close();
	ifile.open("Saves/Records/hard_record.txt");

	if (ifile.is_open())
	{
		ifile >> this->hardRecordInfo.bossKills >> this->hardRecordInfo.kills >> this->hardRecordInfo.wavesCount >>
			this->hardRecordInfo.coins >> this->hardRecordInfo.crystals;
	}
	else
	{
		throw("UNABLE TO OPEN Saves/Records/hard_record.txt");
	}

	ifile.close();
	ifile.open("Saves/Records/insane_record.txt");

	if (ifile.is_open())
	{
		ifile >> this->insaneRecordInfo.bossKills >> this->insaneRecordInfo.kills >> this->insaneRecordInfo.wavesCount >>
			this->insaneRecordInfo.coins >> this->insaneRecordInfo.crystals;
	}
	else
	{
		throw("UNABLE TO OPEN Saves/Records/insane_record.txt");
	}

	ifile.close();
}

//Savings functions
inline void MainMenuState::saveRecordInfo()
{
	std::ofstream ofile("Saves/Records/normal_record.txt");

	if (ofile.is_open())
	{
		ofile << this->normalRecordInfo.bossKills << ' ' << this->normalRecordInfo.kills << ' ' << this->normalRecordInfo.wavesCount << ' ' <<
			this->normalRecordInfo.coins << ' ' << this->normalRecordInfo.crystals;
	}
	else
	{
		throw("UNABLE TO OPEN Saves/Records/normal_record.txt");
	}

	ofile.close();
	ofile.open("Saves/Records/hard_record.txt");

	if (ofile.is_open())
	{
		ofile << this->hardRecordInfo.bossKills << ' ' << this->hardRecordInfo.kills << ' ' << this->hardRecordInfo.wavesCount << ' ' <<
			this->hardRecordInfo.coins << ' ' << this->hardRecordInfo.crystals;
	}
	else
	{
		throw("UNABLE TO OPEN Saves/Records/hard_record.txt");
	}

	ofile.close();
	ofile.open("Saves/Records/insane_record.txt");

	if (ofile.is_open())
	{
		ofile << this->insaneRecordInfo.bossKills << ' ' << this->insaneRecordInfo.kills << ' ' << this->insaneRecordInfo.wavesCount << ' ' <<
			this->insaneRecordInfo.coins << ' ' << this->insaneRecordInfo.crystals;
	}
	else
	{
		throw("UNABLE TO OPEN Saves/Records/insane_record.txt");
	}

	ofile.close();
}

//Update functions
inline void MainMenuState::updateInput(const float& dt)
{

}

inline void MainMenuState::updateGUI()
{
	//Updates all buttons
	for (auto& el : this->buttons)
	{
		el.second->update(this->mousePosWindow);
	}

	//Decrease difficulty button
	if (this->buttons["DIFFICULTY_LESS"]->isPressed() && this->getKeyTime())
	{
		this->sounds.clickSound.second.play();

		if (--this->difficultyLvl <= 1)
		{
			this->difficultyLvl = 1;
		}

		this->updateText();
	}

	//Increase difficulty button
	else if (this->buttons["DIFFICULTY_MORE"]->isPressed() && this->getKeyTime())
	{
		this->sounds.clickSound.second.play();

		if (++this->difficultyLvl == 4)
		{
			this->difficultyLvl = 3;
		}

		this->updateText();
	}

	//New game start
	else if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		switch (this->difficultyLvl)
		{
		case 1:
			this->states->push(new GameState(this->stateData, this->normalRecordInfo, this->difficultyLvl));
			break;
		case 2:
			this->states->push(new GameState(this->stateData, this->hardRecordInfo, this->difficultyLvl));
			break;
		case 3:
			this->states->push(new GameState(this->stateData, this->insaneRecordInfo, this->difficultyLvl));
			break;
		default:
			this->states->push(new GameState(this->stateData, this->normalRecordInfo, this->difficultyLvl));
			break;
		}

		this->sounds.music.stop();
	}

	//Settings
	else if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	else if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		this->states->push(new EditorState(this->stateData));
	}

	//Quit game
	else if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();
		this->sounds.music.pause();

		//Save record info
		this->saveRecordInfo();

		this->endState();
	}

	//Records
	else if (this->buttons["RECORDS"]->isPressed())
	{
		this->sounds.clickSound.second.play();
		
		//Swithc game mode record

	}
}

inline void MainMenuState::updateText()
{
	switch (this->difficultyLvl)
	{
	case 1:
		this->difficultyLvlText.setFillColor(sf::Color::Magenta);

		this->difficultyLvlText.setString("Normal");
		break;
	case 2:
		this->difficultyLvlText.setFillColor(sf::Color::Red);

		this->difficultyLvlText.setString("Hard");
		break;
	case 3:
		this->difficultyLvlText.setFillColor(sf::Color::Black);

		this->difficultyLvlText.setString("Insane");
		break;
	default:
		this->difficultyLvlText.setFillColor(sf::Color::White);

		this->difficultyLvlText.setString("???");
		break;
	}
}

inline void MainMenuState::updateRecordInfo()
{
	if (this->buttons["RECORDS"]->getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePosWindow)))
	{
		
	}
}

//Render functions
inline void MainMenuState::renderGUI(sf::RenderTarget& target)
{
	//Text
	target.draw(this->difficultyText);
	target.draw(this->difficultyLvlText);

	//Buttons
	for (auto& el : this->buttons)
	{
		el.second->render(target);
	}
}

//Constructor
MainMenuState::MainMenuState(StateData* state_data) noexcept
	: State(state_data)
{
	//State type
	this->type = STATE_TYPE::MAIN_MENU_STATE;

	//Init functions
	this->initVariables   ();
	this->initSounds      ();
	this->initBackground  ();
	this->initFonts       ();	   
	this->initKeybinds    (); 
	this->initGUI         ();
	this->loadRecordInfo  ();
	this->initRecrodsInfo ();
}

MainMenuState::~MainMenuState()
{
}

//Public functions 
void MainMenuState::updateTopState()
{
	this->updateGuiPosition ();
	this->playMusic         ();
}

void MainMenuState::updateGuiPosition()
{
	this->difficultyText.setPosition(
		static_cast<float>(this->window->getSize().x) - 550.f,
		static_cast<float>(this->window->getPosition().y) + 100.f);

	this->difficultyLvlText.setPosition(
		this->difficultyText.getPosition().x + 300.f,
		this->difficultyText.getPosition().y);

	this->buttons["DIFFICULTY_LESS"]->setPosition(
		this->difficultyLvlText.getPosition().x - 30.f,
		this->difficultyLvlText.getPosition().y + 50.f);

	this->buttons["DIFFICULTY_MORE"]->setPosition(
		this->difficultyLvlText.getPosition().x + 80.f,
		this->difficultyLvlText.getPosition().y + 50.f);
}

void MainMenuState::playMusic()
{
	if (this->sounds.music.getStatus() != sf::Music::Playing)
	{
		this->sounds.music.play();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateKeyTime       (dt);
	this->updateInput         (dt);
	this->updateMousePosition ();
	this->updateGUI           ();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(this->background);

	this->renderGUI(*target);

	//REMOVE LATER JUST DEBUG!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousPosView.x, this->mousPosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y));

	target->draw(mouseText);*/
}