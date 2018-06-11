#include <SFML/Graphics.hpp>

#pragma once
class PhysicalObj : public sf::Drawable, public sf::Transformable
{
public:
	PhysicalObj();
	virtual ~PhysicalObj();

	virtual void refreshHitbox() = 0;
	bool contain(sf::Vector2f point);
};

