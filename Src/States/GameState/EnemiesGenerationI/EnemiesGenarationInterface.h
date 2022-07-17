#pragma once
#include <Entities/Enemies/Enemy.h>

template<typename EnemyClass>
class EnemiesGenerationI
{
public:
	//Variables
	std::vector<EnemyClass>& enemies;


	//Constructor
	EnemiesGenerationI(std::vector<EnemyClass>& enemies) noexcept
		:enemies(enemies)
	{

	}
	~EnemiesGenerationI()
	{
	}

	//Functions
	void clear()
	{
		this->enemies.clear();
	}

	void reserve(const size_t& amount)
	{
		this->enemies.reserve(amount);
	}

	//Generating enemy position
	static sf::Vector2f generatePosition(const sf::Vector2f& tilemapMaxSizeF, const float& gridSize)
	{
		float x = static_cast<float>(std::rand() % (static_cast<int>(tilemapMaxSizeF.x)));

		if (x <= (gridSize * 3.f))
		{
			x += (gridSize * 3.f);
		}
		else if (x + (gridSize * 3.f) >= tilemapMaxSizeF.x)
		{
			x -= (gridSize * 3.f);
		}

		float y = static_cast<float>(std::rand() % (static_cast<int>(tilemapMaxSizeF.y)));

		if (y <= (gridSize * 3.f))
		{
			y += (gridSize * 3.f);
		}
		else if (y + (gridSize * 3.f) >= tilemapMaxSizeF.y)
		{
			y -= (gridSize * 3.f);
		}

		return sf::Vector2f(x, y);
	}

	//Generate amount of enemies
	static int generateAmount(const int& wavesCount, const unsigned int& difficulty, const int& baseAmount)
	{
		return  baseAmount + difficulty + (wavesCount / 5);
	}

	//Generate enemy lvl
	static int generateLvl(const int& wavesCount, const unsigned int& difficulty, const int& modifier)
	{
		return wavesCount + (difficulty * (std::rand() % modifier));
	}

	//Emplace back enemy
	template<typename ...EnemyData>
	void generate(EnemyData&&... enemyData)
	{
		this->enemies.emplace_back(std::forward<EnemyData>(enemyData)...);
	}
};