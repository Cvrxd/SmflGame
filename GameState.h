#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "BossEnemy.h"
#include "MeleEnemy.h"
#include "MageEnemy.h"
#include "DestroyingEnemy.h"
#include "MapTrapsComonent.h"
#include "EnemiesGenarationInterface.h"
#include "GameOverMenu.h"

#define BOSSWAVE 5

class State;
class PauseMenu;
class GameOverMenu;
class TileMap;
class PlayerGUI;
class Enemy;
class BossEnemy;
class MeleEnemy;
class MageEnemy;
class DestroyingEnemy;
class MapTrapsComonent;

struct RecordInfo
{
	size_t wavesCount = 0;
	size_t kills      = 0;
	size_t bossKills  = 0;
	size_t crystals   = 0;
	size_t coins      = 0;
};

class GameState : public State
{
private:
	using MeleEnemiesTextures        = std::unordered_map<MeleEnemyType, sf::Texture>;
	using MageEnemiesTextures        = std::unordered_map<MageEnemyType, sf::Texture>;
	using DestroyingEnemiesTextures  = std::unordered_map<DestroyingEnemyType, sf::Texture>;
	using BossesEnemiesTextures      = std::unordered_map<BossType, sf::Texture>;
	using VolumeButtons              = std::pair<std::unique_ptr<GUI::Button>, std::unique_ptr<GUI::Button>>;

	//Variables 
	const unsigned int diffcultyLvl  = 1;
	const unsigned int trapsCount    = 15;
	int                wavesCount    = 0;
	size_t             totalEnemies  = 0;

	bool gameOverMenuActive = false;
	bool skillMenuActive    = false;
	bool itemsMenuActive    = false;

	bool guiRenderFlag  = true;

	bool bossFight      = false;

	//Player buff
	bool isBuffed       = false;

	//Record info
	RecordInfo&        recordInfo;

	//Core
	sf::RenderTexture  renderTexture;
	sf::Sprite         renderSprite;
	sf::Vector2i       viewGridPosition;

	sf::View     view;
	sf::Font     font;
	sf::Shader   core_shader;

	PlayerGUI    playerGUI;
	TileMap      tileMap;
	Player       player;

	//Menu
	GameOverMenu gameOverMenu;
	SkillsMenu   skillsMenu;
	ItemsMune    itemsMenu;
	PauseMenu    pauseMenu;

	//Gui
	VolumeButtons     volumeButtons;
	sf::Text          volumeText;

	//Components
	MapTrapsComonent mapTrapsComponent;

	//Sounds
	EnemySoundBox            enemiesSoundBox;
	GuiSoundsBox             guiSounBox;
	GameStateSoundBox        gameStateSoundBox;

	//Enemies textures
	MeleEnemiesTextures        meleEnemiesTextures;
	MageEnemiesTextures        mageEnemiesTextures;
	DestroyingEnemiesTextures  destroyingEnemiestextures;
	BossesEnemiesTextures      bossesEnemiesTextures;

	//Entities
	std::vector<BossEnemy>          bosses;
	std::vector<MeleEnemy>          meleEnemies;
	std::vector<MageEnemy>          mageEnemies;
	std::vector<DestroyingEnemy>    destroyingEnemies;

	//Enemies generation Interfaces
	EnemiesGenerationI<BossEnemy>        bossesGenerationI;
	EnemiesGenerationI<MeleEnemy>        meleEnemiesGenerationI;
	EnemiesGenerationI<MageEnemy>        mageEnemiesGenerationI;
	EnemiesGenerationI<DestroyingEnemy>  destroyingEnemiesGenerationI;

	//Threads
	sf::Thread magesUpdateThread;
	sf::Thread meleEnemiesUpdateThread;
	sf::Thread destroyingEnemiesUpdateThread;
	sf::Thread bossesEnemiesUpdateThread;

	//Init functions
	void initRenderTextures  ();
	void initView            ();
	void initFonts           ();
	void initKeybinds        ()   override;
	void initTextures        ();
	void initPauseMenu       ();
	void initShaders         ();
	void initPlayers         ();
	void initPlayerGUI       ();
	void initTileMap         ();
	void initSounds          ();
	void createTraps         ();

	//Update functions
	void gameOverUpdate          ();
	void updateGameWave          ();
	void updateVolumeGui         ();
	void updatePauseMenuButtons  ();
	void updateVolumeText        ();
	void updateView              (const float& dt);
	void updatePlayerInput       (const float& dt);
	void updateInput             (const float& dt)     override;
	void updateTileMap           (const float& dt);

	//Enemis update
	void updateEnemies           (const float& dt);
	void updateDestroyingEnemis  ();
	void updateMeleEnemies       ();
	void updateBossEnemies       ();
	void updateMageEnemies       ();

	//Enemies generation functions
	void generateMeleEnemies       ();
	void generateMageEnemies       ();
	void generateDestroyingEnemies ();
	void generateBossEnemies       ();

	//Render functions
	void renderPauseMenuGui (sf::RenderTarget& target);
	
	//Render enemies
	void renderEnemies          ();

	//Separete render
	void renderDestroyingEnemis ();
	void renderMeleEnemies      ();
	void renderBossEnemies      ();
	void renderMageEnemies      ();


	//Sounds functions
	void pauseSounds    ();
	void resumeSounds   ();

	void increaseVolume ();
	void decreaseVolume ();

public:
	GameState (StateData* state_data, RecordInfo& recordInfo, const unsigned int& difficultyLvl = 1);
	virtual ~GameState() override;

	//Functions
	void updateTopState()                              override;

	void update  (const float& dt)                     override;
	void render  (sf::RenderTarget* target = nullptr)  override;
};
