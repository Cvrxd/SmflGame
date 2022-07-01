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

# Enemies
Each enemy has unique hitbox parameters, speed, cooldown between attacks and attacking range. Each enemy has resistances
Almost all enemies have unique sounds with cooldown on it

Enemy Resistances: resistance to particular player skill, magick resistance, physical resistance.

Mele Enemy: has simple following AI to chase player until intersection with attack range, unique attack cooldown with speed.
Boss Enemy: has simple following AI like Mele Enemies, unique skill with animation, sound and cooldown.
Mage Enemy: AI is based on player position. If player intersects mage inner range, enemy starts running to increase distance. If player does not intersects inner range and intersects attack range, mage attacks. If player is too far from mage, enemy chase him.
Destroying Enemy: has simple following AI like Mele Enemies. After intersection with player hit range, exploads and deals damage to area.

# Player




