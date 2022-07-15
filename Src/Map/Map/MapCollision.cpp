#include "stdafx.h"
#include "TileMap.h"

void TileMap::updateLevelCollision(Entity* entity, const float& dt)
{
	//Level Bounds Collision
	//X check
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeLevelF.x)
	{
		entity->setPosition(this->maxSizeLevelF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	//Y check
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeLevelF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeLevelF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
}

void TileMap::updateTilesCollision(Entity* entity, const sf::Vector2i& gridPosition, const float& dt)
{
	//Tiles Collision
	this->fromX = gridPosition.x - 20;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeLevelGrid.x)
	{
		this->fromX = this->maxSizeLevelGrid.x;
	}

	this->toX = gridPosition.x + 20;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeLevelGrid.x)
	{
		this->toX = this->maxSizeLevelGrid.x;
	}

	this->fromY = gridPosition.y - 14;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeLevelGrid.y)
	{
		this->fromY = this->maxSizeLevelGrid.y;
	}

	this->toY = gridPosition.y + 15;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeLevelGrid.y)
	{
		this->toY = this->maxSizeLevelGrid.y;
	}

	//Collision
	//Update collision if needed
	if (this->updateCollision)
	{
		for (auto& el_x : this->map)
		{
			for (auto& el_y : el_x)
			{
				this->playerBounds = entity->getGlobalBounds();
				this->wallBounds = el_y.getGlobalBounds();
				this->nextPositionBounds = entity->getNextPosition(dt);

				if (el_y.getX() < toX && el_y.getY() < toY && el_y.getX() > fromX && el_y.getY() > fromY)
				{
					if (el_y.getCollision() && el_y.inersects(nextPositionBounds))
					{
						//Bottom collision
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						}

						//Top collision
						else if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}

						//Right collision
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}

						//Left collision
						else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		}
	}

}
