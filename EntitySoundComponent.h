#pragma once
class EntitySoundComponent
{
private:
	//Variables
	std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> sounds;

	//Movement sound to play
	sf::Sound* movementSound;

public:
	EntitySoundComponent() noexcept;
	~EntitySoundComponent();

	//Functions
	void addWalkingSound(const std::string& path);
	void addRunningSound(const std::string& path);

	void changeMovementSound(const bool& running);
	void changeMovementVolume(const bool& increase);

	void pauseMovementSound();
	void unpauseMovementSound();
};

