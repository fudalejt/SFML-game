#include "Hitbox.h"

#pragma once
class CircleHitbox : public Hitbox
{
public:
	CircleHitbox(float radius);
	virtual ~CircleHitbox();

	virtual bool isContaining(const sf::Vector2f& point);
	virtual void refresh();
	void setRadius(float radius);
	float getRadius();
	void setScale(float newScale);

protected:
	float 
		radius,
		scale;
};

