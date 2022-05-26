#pragma once
#include "Entity.h"
#include "PlayerGUI.h"

class Entity;
class PlayerGUI;

class Player : public Entity
{
private:
	//Variables
	bool& isBuffed;

	bool isAttacking = false;
	bool isHit = false;
	bool dealDMG = false;
	bool isTakingHit = false;
	bool isUsingSkill = false;

	int currentHitAnimation;

	int currentskillDamage = 1;

	std::string moveKey;
	std::string dashKey;
	std::string* currentKey;

	PlayerGUI* playerGUI = nullptr;

	SkillType currentSkilltype = SkillType::EMPTY;

	sf::CircleShape hitRange;
	sf::RectangleShape damageRange;
	
	const sf::Font& font;
	sf::Clock damageTimer;

	//Components
	AnimationComponent animationComponent;
	StatsComponent statsComponent;
	SkillsComponent skillsComponent;

	//Animations
	std::vector<std::pair<sf::Texture, sf::Sprite>> sprites;
	std::vector<AnimationComponent> hitAnimations;


	//Initialisation functios
	void initVariables();
	void createAnimationComponent(sf::Texture& texture_sheet);
	void addAnimations();
	void initComponents(sf::Texture& texture_sheet);
public:
	Player(const float& x, const float& y, sf::Texture& texture_sheet, const sf::Font& font, bool& isBuffed);
	virtual ~Player();

	//Accessors
	const SkillType& getUsingSkilltype();
	const int& getUsingSkilldamage();
	const sf::Font& getFont();
	void setPlayerGUI(PlayerGUI& playerGUI);

	const bool& usingSkill();
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

	void gainCrystals(const int& crystals);
	void loseCrystals(const int& crystals);
	void gainCoins(const int& coins);
	void loseCoins(const int& coins);

	void addItem(const Items& item);

	void addPotions(const Potions& potion_type);
	void usePotions(const Potions& potion_type);

	//Functions
	void updateAttack(const float& dt, sf::Vector2f mouse_pos_view);
	void updateAnimations(const float& dt, sf::Vector2f mouse_pos_view);
	void update(const float& dt, sf::Vector2f mouse_pos_view) override;
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL) override;
};

