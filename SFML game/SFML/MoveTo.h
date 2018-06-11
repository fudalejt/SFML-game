#pragma once
#include "Order.h"
#include "Unit.h"

class MoveTo : public Order
{
public:
	MoveTo(int lifeTime, GameObject& target);
	virtual ~MoveTo();
	virtual OrderType getType() override;

	GameObject& target;
};

