#pragma once
#include "Order.h"
#include <SFML/System.hpp>

class Unit;

enum JumpResult {
	EXECUTE = 0,
	ENDED = 1,
	INTERRUPTED = 2
};

class JumpAway :
	public Order
{
public:
	JumpAway(int lifeTime, Unit& enemy, int damage);
	virtual ~JumpAway();
	virtual OrderType getType() override;
	JumpResult jumpAway(Unit* owner, int time);

	Unit& enemy;

protected:
	
	int damage;

	static const float jumpDist;
};
