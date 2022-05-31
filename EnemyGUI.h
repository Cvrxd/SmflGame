#pragma once

namespace EnemyGUI
{
	class EnemyHealthBar
	{
	private:
		//Variables
		int hpMAX;
		float offsetX = 0;
		const int* hp;

		sf::RectangleShape healthRect;
		sf::RectangleShape backgroundRect;

		sf::Texture healthTexture;
		sf::Texture backgroundTexture;

		void initTextures();
	public:
		EnemyHealthBar(const int* hp) noexcept;
		~EnemyHealthBar();

		//Functions
		void updateOffsetX();
		void update(const float& dt, const sf::Vector2f& position);
		void render(sf::RenderTarget& target);
	};

	class EnemyLevelIcon
	{
	private:
		//Variables
		const int* lvl;
		const int* playerLvl;

		float offsetX = 45.f;

		sf::RectangleShape backgroundRect;
		sf::Texture backgroundTexture;

		sf::Text lvlText;

		void initVariables(const sf::Font& font);
	public:
		EnemyLevelIcon(const int* lvl, const int* playerLvl, const sf::Font& font) noexcept;
		~EnemyLevelIcon();

		//Functions
		void updateText();
		void updateOffsetX();
		void update(const float& dt, const sf::Vector2f& position);
		void render(sf::RenderTarget& target);
	};
	
}

