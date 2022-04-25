#pragma once
#include"Player.h"

class State
{
protected:
	//Core variables
	std::stack<State*>* states;

	sf::RenderWindow* window = nullptr;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousPosView; 
	
	//Resourses
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();


	// end state
	const bool& getQuit() const;

	virtual void endState();

	// update functions
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePosition();
	virtual void update(const float& dt) = 0;;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

