# SmflGame

# About
This is top down 2D game made with sfml, c++ and GLSL shaders

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
Each enemy has unique hitbox parameters, speed, cooldown between attacks and attacking range. Each enemy has resistances
Almost all enemies have unique sounds with cooldown on it.

Components: MovementComponent, HitboxComponent, AnimationCompopnent, StatsComponen.

Enemy Resistances: resistance to particular player skill, magick resistance, physical resistance.

Mele Enemy: has simple following AI to chase player until intersection with attack range, unique attack cooldown with speed.

Boss Enemy: has simple following AI like Mele Enemies, unique skill with animation, sound and cooldown.

Mage Enemy: AI is based on player position. If player intersects mage inner range, enemy starts running to increase distance. If player does not intersects inner range and intersects attack range, mage attacks. If player is too far from mage, enemy chase him.

Destroying Enemy: has simple following AI like Mele Enemies. After intersection with player hit range, exploads and deals damage to area.

# Enemies Genetarion Interface
If no enemies alive, new wave starts. Enemies generation is working in different threads to increase perfomance of this action. Generation is based on current wave count, difficulty and random value. 

# Player
Player

# Stats Component

# Skills Componet

# Items Component

# Tile Map

# Collision

# Tile Traps

# GUI

# Technologies
C++ 17, SFML, Multithreading sfml/std, GLSL

# Instalation
Instalation.exe and screeshots is available on my itch.io page. Link: sculptor.itch.io/dungeon-arena



