#include "JumpAway.h"
#include "Unit.h"
#include "Stay.h"

#include <iostream>

const float JumpAway::jumpDist = 25.f;

JumpAway::JumpAway(int lifeTime, Unit& enemy, int damage) :
	Order(lifeTime),
	enemy(enemy),
	damage(damage)
{
}

JumpAway::~JumpAway()
{
	//std::cout << "~JUMP_AWAY." << std::endl;
}

OrderType JumpAway::getType() {
	return JUMP_AWAY;
}

JumpResult JumpAway::jumpAway(Unit* owner, int time)
{
	std::cout << "jumpAway()" << std::endl;
	float speedBust = 4;
	float dx = owner->getPosition().x - enemy.getPosition().x;
	float dy = owner->getPosition().y - enemy.getPosition().y;
	float z = sqrt(pow(dx, 2) + pow(dy, 2));

	float sin = dy / z;
	float cos = dx / z;
	
	if (z >= jumpDist + 2 * owner->getRadius()) {
		return ENDED;
	}
	else {
		sf::Vector2f offset(cos * owner->moveSpeed * speedBust * time, sin * owner->moveSpeed * speedBust* time);
		owner->move(offset);
		std::list<Unit*> col = game->checkCollision(*owner);
		if (col.size() > 0) {
			owner->move(-offset);
			owner->setHealth(owner->health - damage);
			return INTERRUPTED;
		}
	}
	return EXECUTE;
}