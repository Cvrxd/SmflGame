#include "stdafx.h"
#include "DropComponent.h"

DropComponent::DropComponent()
{
	this->dropItems.resize(10);

	this->dropItems[0].first = SWORD;
	this->dropItems[1].first = DAGGER;
	this->dropItems[2].first = MAGIK_SWORD;
	this->dropItems[3].first = STAFF;
	this->dropItems[4].first = RING;
	this->dropItems[5].first = NECKLASE;
	this->dropItems[6].first = HELMET;
	this->dropItems[7].first = ARMOR;
	this->dropItems[8].first = GLOVES;
	this->dropItems[9].first = BOOTS;
}

Items DropComponent::dropItem()
{
	int rnd = std::rand() % 9 + 1;

	if (this->dropItems[rnd].second != true)
	{
		this->dropItems[rnd].second = true;
		return this->dropItems[rnd].first;
	}
	return EMPTY_ITEM;
}
