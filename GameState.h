#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "BossEnemy.h"
#include "MeleEnemy.h"
#include "MageEnemy.h"
#include "DestroyingEnemy.h"

class State;
class PauseMenu;
class TileMap;
class PlayerGUI;
class Enemy;
class BossEnemy;
class MeleEnemy;
class MageEnemy;
class DestroyingEnemy;
class PopUpTextComponent;

class GameState : public State
{
private:
	using VolumeButtons = std::pair<std::unique_ptr<GUI::Button>, std::unique_ptr<GUI::Button>>;

	//Variables 
	const unsigned int diffcultyLvl = 1;

	bool skillMenuActive = false;
	bool itemsMenuActive = false;

	bool bossFight;
	//Player buff
	bool isBuffed        = false;

	//Core
	sf::RenderTexture  renderTexture;
	sf::Sprite         renderSprite;
	sf::Vector2i       viewGridPosition;

	sf::View    view;
	sf::Font    font;
	sf::Shader  core_shader;

	PlayerGUI   playerGUI;
	SkillsMenu  skillsMenu;
	ItemsMune   itemsMenu;
	PauseMenu   pauseMenu;
	TileMap     tileMap;
	Player      player;

	//Gui
	VolumeButtons volumeButtons;
	sf::Text      volumeText;

	//Pop up text
	PopUpTextComponent popUpTextComponent;

	//Entities
	std::vector<BossEnemy>          bosses;
	std::vector<MeleEnemy>          meleEnemies;
	std::vector<MageEnemy>          mageEnemies;
	std::vector<DestroyingEnemy>    destroyingEnemies;

	//Sounds
	EnemySoundBox     enemiesSounds;
	GuiSoundsBox      guiSounds;
	GameStateSoundBox gameMusic;

	//Init functions
	void initRenderTextures  ();
	void initView            ();
	void initFonts           ();
	void initKeybinds        ()   override;
	void initTextures        ();
	void initPauseMenu       ();
	void initShaders         ();
	void initPlayers         ();
	void initEnemies         ();
	void initPlayerGUI       ();
	void initTileMap         ();
	void initSounds          ();

	//Update functions
	void updateVolumeGui         ();
	void updatePauseMenuButtons  ();
	void updateVolumeText        ();
	void updateView              (const float& dt);
	void updatePlayerInput       (const float& dt);
	void updateInput             (const float& dt)     override;
	void updateTileMap           (const float& dt);

	//Enemis update
	void updateEnemies           (const float& dt);
	void updateDestroyingEnemis  (const float& dt);
	void updateMeleEnemies       (const float& dt);
	void updateBossEnemies       (const float& dt);
	void updateMageEnemies       (const float& dt);

	//Render functions
	void renderPauseMenuGui (sf::RenderTarget& target);
	void renderEnemies      (sf::RenderTarget& target);

	//Functions
	void pauseSounds  ();
	void resumeSounds ();

public:
	GameState (StateData* state_data, const unsigned int& difficultyLvl = 1);
	virtual ~GameState() override;

	//Functions
	void updateTopState()                              override;

	void update  (const float& dt)                     override;
	void render  (sf::RenderTarget* target = nullptr)  override;
};
