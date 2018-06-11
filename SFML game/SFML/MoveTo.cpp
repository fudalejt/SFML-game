#include "MoveTo.h"

MoveTo::MoveTo(int lifeTime, GameObject& target):
	Order(lifeTime),
	target(target)
{
}

MoveTo::~MoveTo()
{
	//std::cout << "~MOVE_TO." << std::endl;
}

OrderType MoveTo::getType() {
	return MOVE_TO;
}
