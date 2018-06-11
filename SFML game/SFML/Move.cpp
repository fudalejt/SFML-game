#include "Move.h"
#include <iostream>

Move::Move(int lifeTime, sf::Vector2f targetPos):
	Order(lifeTime),
	targetPos(targetPos)
{
}

Move::~Move()
{
	//std::cout << "~MOVE." << std::endl;
}

OrderType Move::getType() {
	return MOVE;
}
