#include "Attack.h"
#include "Unit.h"

Attack::Attack(int lifeTime, Unit& target, Unit& owner):
	Order(lifeTime),
	target(target),
	owner(owner)
{
	target.addToFightList(&owner);
}

Attack::~Attack()
{
	target.removeFromFightList(&owner);
	//std::cout << "~ATTACK." << std::endl;
}

OrderType Attack::getType() {
	return ATTACK;
}