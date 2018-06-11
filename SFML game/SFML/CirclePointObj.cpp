#include "CirclePointObj.h"
#include <iostream>


CirclePointObj::CirclePointObj(float radius):
	hitbox(radius),
	shape(radius),
	regularColor(0, 100, 100, 200),
	pointedColor(regularColor.r, regularColor.g, regularColor.b, regularColor.a * 0.75)
{
	setOrigin(radius, radius);
	shape.setFillColor(regularColor);
}

CirclePointObj::~CirclePointObj(){
}

bool CirclePointObj::isContaining(const sf::Vector2f & point)
{
	bool isContaining = hitbox.isContaining(point);
	//setPointed(isContaining);
	return isContaining;
}

void CirclePointObj::update(sf::Vector2f& mousePos)
{
	if (isPointed) {
		setPosition(mousePos);
	}
}

void CirclePointObj::setPointed(bool isPointed) {
	this->isPointed = isPointed;
	if (isPointed) {
		shape.setFillColor(this->pointedColor);
	}
	else {
		shape.setFillColor(this->regularColor);
	}
}

void CirclePointObj::setFillColor(sf::Color color)
{
	shape.setFillColor(color);
}

void CirclePointObj::setRegColor(sf::Color color)
{
	regularColor = color;
	pointedColor = sf::Color(regularColor.r, regularColor.g, regularColor.b, regularColor.a * 0.5);
	if (isPointed == false)
		shape.setFillColor(regularColor);
}

void CirclePointObj::setPointColor(sf::Color color)
{
	pointedColor = color;
	if (isPointed)
		shape.setFillColor(pointedColor);
}

void CirclePointObj::move(const sf::Vector2f & offset)
{
	sf::Transformable::move(offset);
	hitbox.move(offset);
}

void CirclePointObj::setPosition(const sf::Vector2f & position)
{
	sf::Transformable::setPosition(position);
	hitbox.setPosition(position);
}

void CirclePointObj::setRadius(float radius)
{
	shape.setRadius(radius);
	setOrigin(radius, radius);
	hitbox.setRadius(radius);	
}

float CirclePointObj::getRadius() {
	return hitbox.getRadius();
}

void CirclePointObj::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	target.draw(shape, states);	
}

void CirclePointObj::refreshHitbox()
{
	//TODO
}
