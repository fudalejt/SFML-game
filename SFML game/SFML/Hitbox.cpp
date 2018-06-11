#include "Hitbox.h"
#include <iostream>

Hitbox::Hitbox()
{
}


Hitbox::~Hitbox()
{
}

void Hitbox::setOrigin(float x, float y)
{
	sf::Transformable::setOrigin(x, y);
	refresh();
}

void Hitbox::setOrigin(sf::Vector2f newOrigin)
{
	sf::Transformable::setOrigin(newOrigin);
	refresh();
}

void Hitbox::setPosition(sf::Vector2f newPos)
{
	sf::Transformable::setPosition(newPos);
}

void Hitbox::move(const sf::Vector2f & offset)
{
	sf::Transformable::move(offset);
}
