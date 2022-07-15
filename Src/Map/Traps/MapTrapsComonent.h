#pragma once
#include"AnimationComponent.h"
#include"Player.h"

static constexpr float TRAPS_VOLUME_MODIFIER = 15.f;

enum class TrapType { FIRE_TRAP = 0, SPIKE_TRAP, BEAR_TRAP };

class MapTrapsComonent
{
private:
	//Trap
	class Trap
	{
	private:
		//Vraibles
		int          damage;
		bool         playAnimation = true;
		TrapType     type;
		sf::Sprite   sprite;
		sf::Texture& texture;

		AnimationComponent animationComponent;

		//Init functions
		void initAnimations();

	public:
		//Constructors
		Trap(const sf::Vector2f& position, const TrapType& type, sf::Texture& texture, const int& damage) noexcept;
		~Trap();

		//Accesors
		const int&      getDamage () const;
		const TrapType& getType   () const;

		//Functions
		bool updateAnimation (const float& dt);

		bool update          (const float& dt, const sf::FloatRect& playerBounds);
		void render          (sf::RenderTarget& target);
	};

	using TrapsTextures    = std::unordered_map<TrapType, sf::Texture>;
	using TrapsVector      = std::vector<Trap>;
	using TrapSoundsMap    = std::unordered_map<TrapType, std::pair<sf::SoundBuffer, sf::Sound>>;

	//Variables
	unsigned int      gameDifficulty;
	unsigned int      trapsCount;
	const float       trapVolume;

	Player&  player;

	TrapSoundsMap sounds;
	TrapsTextures trapsTextures;
	TrapsVector   traps;

	//Functions
	void initTextures();
	void initSounds  ();

	//Sound funtions
	void playTrapSound(const TrapType& sound);

public:
	MapTrapsComonent(Player& player, const unsigned int& gameDifficulty, const unsigned int& trapsCount);
	~MapTrapsComonent();

	//Sound functions
	void stopSounds  ();
	void playSounds  ();
	void pauseSounds ();

	void increaseSoundsVolume ();
	void decreaseSoundsVolume ();
	void setSoundsVolume      (const float& volume);

	//Functions
	void addTrap (const float& x, const float& y, const TrapType& trap_type);

	void update  (const float& dt);
	void render  (sf::RenderTarget& target);
};

