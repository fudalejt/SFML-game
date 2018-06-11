#include "Order.h"

#include <iostream>

Game* Order::game = nullptr;

Order::Order(int lifeTime):
	lifeTime(lifeTime)
{
}

Order::~Order()
{
}

bool Order::update(int deltaTime) {
	if (lifeTime < 0)
		return false;

	lifeTime -= deltaTime;
	if (lifeTime <= 0)
		return true;
	else
		return false;
}

void Order::setLifeTime(int lifeTime) {
	this->lifeTime = lifeTime;
}

void Order::setGame(Game* game) {
	Order::game = game;
}