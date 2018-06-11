#include <SFML/Graphics.hpp>

#pragma once
class Hitbox : public sf::Transformable
{
public:
	Hitbox();
	virtual ~Hitbox();

	virtual bool isContaining(const sf::Vector2f& point) = 0;
	virtual void refresh() = 0;
	void move(const sf::Vector2f& offset);
	void setOrigin(float x, float y);
	void setOrigin(sf::Vector2f newOrigin);
	void setPosition(sf::Vector2f newPos);

};

