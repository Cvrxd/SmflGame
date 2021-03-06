#pragma once
template<typename KeyType>
class IMusicPlayer
{
private:
	using MusicMap = std::unordered_map<KeyType, sf::Music>;

	MusicMap& music;

	const float volumeModifier;
	const float volumeMax;

	float volume;

	IMusicPlayer()                                      = delete;
	IMusicPlayer(const IMusicPlayer& other)             = delete;
	IMusicPlayer(IMusicPlayer&& other)                  = delete;
	IMusicPlayer& operator =(const IMusicPlayer other)  = delete;
	IMusicPlayer& operator =(IMusicPlayer&& other)      = delete;

public:
	IMusicPlayer(MusicMap& music, const float& volume, const float& volumeMax, const float& volumeModifier = 0.15f);
	~IMusicPlayer();

	void stopMusic();
	void playMusic();
	void pauseMusic();

	void increaseVolume();
	void decreaseVolume();

	void setVolume(const float& volume);

	const float& getVolume() const;
	const float& getMaxVolume() const;
};

