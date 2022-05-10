#pragma once

enum SkillType {RED_BLADES = 0};

class SkillsComponent
{
private:
	//Variables

public:
	SkillsComponent();
	~SkillsComponent();

	//Functions
	const short activated();
	void useSkill();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

