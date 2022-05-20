#include "stdafx.h"
#include "DropComponent.h"

DropComponent::DropComponent()
{
	this->dropItems.resize(10);

	this->dropItems[0].first = Items::SWORD;
	this->dropItems[1].first = Items::DAGGER;
	this->dropItems[2].first = Items::MAGIK_SWORD;
	this->dropItems[3].first = Items::STAFF;
	this->dropItems[4].first = Items::RING;
	this->dropItems[5].first = Items::NECKLASE;
	this->dropItems[6].first = Items::HELMET;
	this->dropItems[7].first = Items::ARMOR;
	this->dropItems[8].first = Items::GLOVES;
	this->dropItems[9].first = Items::BOOTS;
}

Items DropComponent::dropItem()
{
	int rnd = std::rand() % 9 + 1;

	if (this->dropItems[rnd].second != true)
	{
		this->dropItems[rnd].second = true;
		return this->dropItems[rnd].first;
	}
	return Items::EMPTY_ITEM;
}
