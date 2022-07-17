#pragma once

template<typename KeyType>
class ISoundsPlayer
{
private:
	using SoundsMap  = std::unordered_map<KeyType, std::pair<sf::SoundBuffer, sf::Sound>>;

	SoundsMap&   sounds;

	const float volumeModifier;
	const float volumeMax;

	float volume;

public:
	ISoundsPlayer(SoundsMap& sounds, const float& volume, const float& volumeMax, const float& volumeModifier = 0.15f);
	~ISoundsPlayer();

	void stopSounds();
	void playSounds();
	void pauseSounds();

	void increaseVolume();
	void decreaseVolume();

	void setVolume(const float& volume);

	const float& getVolume() const;
	const float& getMaxVolume() const;
};

