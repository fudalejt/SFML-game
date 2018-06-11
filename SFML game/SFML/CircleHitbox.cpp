#include "CircleHitbox.h"
#include <math.h>

#include <iostream>


CircleHitbox::CircleHitbox(float radius):
	radius(radius),
	scale(1.f)
{
}


CircleHitbox::~CircleHitbox()
{
}

bool CircleHitbox::isContaining(const sf::Vector2f& point)
{
	sf::Vector2f newPoint = point - getPosition();
	float dist = sqrt(pow(newPoint.x, 2.f) + pow(newPoint.y, 2.f));
	if (dist > radius * scale)
		return false;
	else
		return true;
}

void CircleHitbox::refresh()
{
}

void CircleHitbox::setRadius(float radius)
{
	this->radius = radius;
}

float CircleHitbox::getRadius()
{
	return radius;
}

void CircleHitbox::setScale(float newScale)
{
	scale = newScale;
}