#pragma once
#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	//Variables
	sf::Clock damageTimer;

	bool isAttacking = false;
	bool isHit = false;
	bool dealDMG = false;
	bool isTakingHit = false;
	bool isUsingSkill = false;

	int currentHitAnimation;

	sf::CircleShape hitRange;
	sf::RectangleShape damageRange;
	std::vector<std::pair<sf::Texture, sf::Sprite>> sprites;

	//Components
	std::vector<AnimationComponent> hitAnimations;

	AnimationComponent animationComponent;
	StatsComponent statsComponent;
	SkillsComponent skillsComponent;

	//Initialisation functios
	void initVariables();
	void createAnimationComponent(sf::Texture& texture_sheet);
	void addAnimations();
	void initComponents(sf::Texture& texture_sheet);
public:
	Player(const float& x, const float& y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Accessors
	const bool& isDealingDmg();
	StatsComponent* getStatsComponent();
	SkillsComponent* getSkillComponent();
	const sf::CircleShape& getHitRange();
	const sf::RectangleShape& getDamageRange();

	//Stats functions
	void gainEXP(const unsigned& exp);
	void gainHP(const int& hp);
	void loseHP(const int& hp);
	void gainMP(const int& mp);
	void loseMP(const int& mp);
	void gainArmor(const int& armor);

	void addItem(const Items& item);

	void addPotions(const Potions& potion_type);
	void usePotions(const Potions& potion_type);

	//Functions
	void updateAttack(const float& dt, sf::Vector2f mouse_pos_view);
	void updateRegularKeyboard(const float& dt, sf::Vector2f mouse_pos_view);
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

