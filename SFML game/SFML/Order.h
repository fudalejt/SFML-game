#pragma once
#include "OrderType.h"
#include "Game.h"

class Order
{
public:
	Order(int lifeTime);
	virtual ~Order();
	virtual OrderType getType() = 0;
	bool update(int deltaTime);
	void setLifeTime(int lifeTime);

	static void setGame(Game* game);

	int lifeTime;
protected:
	static Game* game;
};
