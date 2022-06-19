#pragma once
#include"AnimationComponent.h"
#include"Player.h"

enum class TrapType { FIRE_TRAP = 0, SPIKE_TRAP, BEAR_TRAP };

class MapTrapsComonent
{
private:
	//Trap structure
	class Trap
	{
	private:
		//Vraibles
		int         damage;
		bool        playAnimation;
		TrapType    type;
		sf::Sprite  sprite;

		AnimationComponent animationComponent;

		//Init functions
		void initAnimations(sf::Texture& texture);

	public:
		//Constructors
		Trap(const sf::Vector2f& position, const TrapType& type, sf::Texture& texture, const int& damage) noexcept;
		Trap(Trap&& other) noexcept;
		~Trap();

		//Operators
		Trap& operator=(Trap&& other) noexcept;

		//Accesors
		const int& getDamage() const;

		//Functions
		bool updateAnimation (const float& dt);

		bool update          (const float& dt, const sf::FloatRect& playerBounds);
		void render          (sf::RenderTarget& target);
	};

	using TrapsTextures = std::unordered_map<TrapType, sf::Texture>;
	using TrapsVector   = std::vector<Trap>;

	//Variables
	int      gameDifficulty;
	int      trapsCount;
	Player&  player;

	TrapsTextures trapsTextures;
	TrapsVector   traps;

	//Functions
	void initTextures();

public:
	MapTrapsComonent(Player& player, const int& gameDifficulty, const int& trapsCount);
	~MapTrapsComonent();

	//Functions
	void addTrap(const float& x, const float& y, const TrapType& trap_type);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

