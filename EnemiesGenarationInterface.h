#pragma once

template<typename EnemyClass>
class EnemiesGenerationI
{
public:
	//Variables
	std::vector<EnemyClass>& enemies;

	//Constructors
	EnemiesGenerationI(std::vector<EnemyClass>& enemies)
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

	template<typename ...Args>
	void generate(Args&&... args)
	{
		this->enemies.emplace_back(std::forward<Args>(args)...);
	}
};