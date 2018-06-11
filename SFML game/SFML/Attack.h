#pragma once
#include "Order.h"
#include "OrderType.h"
#include "GameObject.h"

class Attack : public Order
{
public:
	Attack(int lifeTime, Unit& target, Unit& owner);
	~Attack();
	virtual OrderType getType() override;

	Unit& target;
	Unit& owner;
};

