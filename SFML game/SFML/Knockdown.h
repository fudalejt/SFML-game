#pragma once
#include "Order.h"


class Knockdown :
	public Order
{
public:
	Knockdown(int lifeTime, float strength, sf::Vector2f deltaPos);
	virtual ~Knockdown();
	virtual OrderType getType() override;
	sf::Vector2f getOffset(int time);

	float strength;

protected:	
	float sin;
	float cos;
	float distance;

};
