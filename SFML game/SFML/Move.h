#pragma once
#include "Order.h"
#include <SFML\Graphics.hpp>
#include "OrderType.h"

class Move :
	public Order
{
public:
	Move(int lifeTime, sf::Vector2f targetPos);
	virtual ~Move();	
	virtual OrderType getType() override;

	sf::Vector2f targetPos;
};

