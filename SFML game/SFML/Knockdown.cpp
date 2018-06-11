#include "Knockdown.h"

Knockdown::Knockdown(int lifeTime, float strength, sf::Vector2f deltaPos) :
	Order(lifeTime),
	strength(strength),
	distance(strength)
{
	float z = sqrt(pow(deltaPos.x, 2) + pow(deltaPos.y, 2));
	sin = deltaPos.y / z;
	cos = deltaPos.x / z;
}


Knockdown::~Knockdown()
{
}

OrderType Knockdown::getType() {
	return KNOCKDOWN;
}

sf::Vector2f Knockdown::getOffset(int time) {
	sf::Vector2f offset(strength * cos * time / 400, strength * sin * time / 400);	
	if (distance > 0) {		
		distance -= sqrt(pow(offset.x, 2) + pow(offset.y, 2));
		return offset;
	}
	else {
		return sf::Vector2f(0, 0);
	}
}

