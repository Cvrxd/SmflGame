#pragma once
#include"StatsComponent.h" 

class DropComponent
{
private:
	std::vector<std::pair<Items, bool>> dropItems;
public:
	DropComponent();
	~DropComponent() {};

	Items dropItem();
};

