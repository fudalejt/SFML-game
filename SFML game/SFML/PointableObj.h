#include <SFML/Graphics.hpp>

#pragma once
class PointableObj :
	//virtual sf::Sprite
	virtual public sf::Drawable, virtual public sf::Transformable
{
public:
	bool isPointed;

	PointableObj();
	virtual ~PointableObj();
	virtual bool isContaining(const sf::Vector2f& point) = 0;
	virtual void update(sf::Vector2f& mousePos) = 0;
	virtual void setPointed(bool isPointed);	
	
protected:
	virtual void refreshHitbox() = 0;
};

