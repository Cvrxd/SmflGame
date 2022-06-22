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
class MapTrapsComonent;

struct RecordInfo
{
	size_t wavesCount = 0;
	size_t kills = 0;
	size_t bossKills = 0;
	size_t crystals = 0;
	size_t coins = 0;
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
	const unsigned int diffcultyLvl = 1;
	const unsigned int trapsCount   = 15;
	int                wavesCount   = 0;

	bool skillMenuActive = false;
	bool itemsMenuActive = false;

	bool bossFight       = false;

	//Player buff
	bool isBuffed        = false;

	//record info
	RecordInfo&        recordInfo;

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

	//Components
	MapTrapsComonent   mapTrapsComponent;

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
	void createTraps         ();

	//Update functions
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
	void updateDestroyingEnemis  (const float& dt);
	void updateMeleEnemies       (const float& dt);
	void updateBossEnemies       (const float& dt);
	void updateMageEnemies       (const float& dt);

	//Enemies generation functions
	void generateMeleEnemies       ();
	void generateMageEnemies       ();
	void generateDestroyingEnemies ();
	void generateBossEnemies       ();

	//Render functions
	void renderPauseMenuGui (sf::RenderTarget& target);
	void renderEnemies      (sf::RenderTarget& target);

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
