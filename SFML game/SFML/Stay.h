#pragma once
#include "Order.h"
#include "OrderType.h"

class Stay: public Order
{
public:
	Stay(int lifeTime);
	virtual ~Stay();
	virtual OrderType getType() override;
};

