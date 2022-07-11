# SmflGame

# About
This is top down 2D game made with sfml, c++ and GLSL shaders.

Short description of main game components:

# Main Menu State
In main menu three game difficulties is avaiable including saved records for each of them, Editor State, Settings State

# Settings State
Available settings: Resolution, V-Sync, FPS(Frames Per Second), Full screen mode

# Editor Sate
Map editor contains Texture selector for tile placing and tile deliting. Tile can be placed on top of another

Tyle types: DEFAULT, ABOVE, DAMAGING, LIGHT

ABOVE - tile renders above entities

DAMAGING - tile deals damage to entities

LIGHT - tile is affected by light shader

# Game State
Game time is no limited, game ends only if player dies mean player has 0 hp. If 0 enemies is alive next game wave starts with generating new enemies. Each 5th wave includes Boos Fight.

# Movement Component
Entities movement is based on velocity, acceleration values and Sfml Sprite position. Position is entity sprite coordinates(Vector2f) on sfml Window (sf::RenderWindow).

# Hitbox Component
Entities hinbox is based on Sfmlf RectangleShape and entity position on sfml Window (sf::RenderWindow).

# Sound Boxes
Each sound component contains volume functions(deacreaseVolume, increaseVolume, setVolume), and sounds function(playSounds, stopSounds, pauseSounds, playSound(key)).

Sounds Boxes: GuiSoundsBox(all GUI sounds), GameStateSoundBox(all GameState sounds, theme music), PlayerSoundBox(all player sounds, walking, running), EnemySoundBox(enemies sounds, player hit, player crit, player skills impact sounds), SkillsComponentSounds(all player skills sounds, potions sounds).

# Animation Component
Animations is based on sf::Texture, sf::Sprite, sf::FloatRect, animations is playing in for loop until finishes or interupts with other animation with priority. Animation with priority can not be canceled until is done.

# Shaders
VertexShader and FragmentShader. Simple shaders using GLSL.

# Enemies
Enemy class inherited from base class Entity. Each enemy has unique hitbox parameters, speed, cooldown between attacks and attacking range. Each enemy has resistances
Almost all enemies have unique sounds with cooldown on it. StatsComponents has base stats parameters(Hp, Damage, Lvl).

Components: MovementComponent, HitboxComponent, AnimationCompopnent, StatsComponent, PopUptextComponent(for pop up text).

PopUpTexts: MISS, IMMUNE(for resistance), CRIT(for player crit).

Enemy Resistances: resistance to particular player skill, magick resistance, physical resistance.

Mele Enemy: Inherited from base class Enemy. Has simple following AI to chase player until intersection with attack range, unique attack cooldown with speed.

Boss Enemy: Inherited from base class Enemy. Has simple following AI like Mele Enemies, unique skill with animation, sound and cooldown.

Mage Enemy: Inherited from base class Enemy. AI is based on player position. If player intersects mage inner range, enemy starts running to increase distance. If player does not intersects inner range and intersects attack range, mage attacks. If player is too far from mage, enemy chase him.

Destroying Enemy: Inherited from base class Enemy. Has simple following AI like Mele Enemies. After intersection with player hit range, exploads and deals damage to area.

# Enemies Genetarion Interface
If no enemies alive, new wave starts. Enemies generation is working in different threads to increase perfomance of this action. Generation is based on current wave count, difficulty and random value. 

# Player
Components: MovementComponent, HitboxComponent, AnimationCompopnent, StatsComponent, SkillsComponent.

Player class inherited from base class Entity. Controls and keybinds for player is in Configs/gamestate_keybinds.ini. StatsComponents has base stats parameters(Hp, Mp, Armor, exp, lvl, critRate, missChance, physicalDamage, magickalDamage, crystals, coins). Player SoundBox contains playerSounds(walking, running).

# Stats Component
Sctruct that contains base stat parameters for Entity: Hp, HpMax, Mp, MpMax, Armor, ArmorMax, exp, expNext, lvl, critRate, missChance, physicalDamage, magickalDamage, coins, crysrals.
Functions: loseHp(value), gainHp(value), loseArmor(value), gainArmor(value), loseMp(value), gainMp(value), gainExp(value), loseExp(value), gainCrystals(value), loseCrystals(value), gainCoins(value), loseCoins(value). For player also has additional info about stats gained from items.

# Skills Componet
Components: PopUptextComponent, AnimationComponent(for each skill), SoundBox(sounds for each skill)

Has info of all available skills and player skills/lvls. Maintain skills and potions cooldown, effects, aniamtions.

# Tile Map
Contains vector<vector<Tile>> for tile map. Each tile has position based on sf::Vector2f(positon on window).

Funtions: updateColiision(looking for tiles with collision parameter in certain area around enity, updating collision with this tiles if needed), update(), render(rendering tiles wich position is on screen).

# Tile Traps Component
Component for GameState. Each trap has AniamtionComponent based on TrapType. Update intersection with player hitbox afted trap animations is done.

# GUI
Button class, DropDownList(for SettingsState), TextureSelector(for EditorState).

PauseMenu(GameState, EditorState), GameOverMenu(GameState).

# Enemy GUI
Has EnemyHealtBar, EnemyLvlIcon. 

# Player GUI
Gemeral player GUI. Player stats bars, skill slots, lvl icon, record info, crystals, coins info.

# SkillsMenu
GUI element provides ability to unlock skills, and updagrade player stats. Has info of player current stats. 

# SkillsLevelingComponent
GUI element provides ability to upgrade player skills. Has skills lvl/damage info.

# ItemsMenu
GUI element provides ability to unlock and upgrade player items. Has info of items stats and lvls.

# Technologies
C++ 17, SFML, Multithreading sfml/std, GLSL

# Instalation
Release version of project is available on my itch.io page. Link: sculptor.itch.io/dungeon-arena. Or in repository website section.



