#include "PointableObj.h"
#include "CircleHitbox.h"

#pragma once
class CirclePointObj : virtual public PointableObj
{
public:
	CirclePointObj(float radius);
	virtual ~CirclePointObj();
	virtual bool isContaining(const sf::Vector2f& point) override;
	virtual void update(sf::Vector2f& mousePos) override;
	virtual void setPointed(bool isPointed) override;
	void setFillColor(sf::Color color);
	void setRegColor(sf::Color color);
	void setPointColor(sf::Color color);
	void move(const  sf::Vector2f &offset);
	void setPosition(const sf::Vector2f &position);
	void setRadius(float radius);
	float getRadius();

protected:
	CircleHitbox hitbox;
	sf::CircleShape shape;
	sf::Color
		regularColor,
		pointedColor;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void refreshHitbox() override;

};

