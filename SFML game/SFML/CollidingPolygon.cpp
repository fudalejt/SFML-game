#include "CollidingPolygon.h"
#include <iostream>
#include <limits>   
#include <math.h>

#include "LinFuncParam.h"

using namespace std;

CollidingPolygon::CollidingPolygon(sf::VertexArray& vertexAr):
	hitbox(vertexAr),
	vertexAr(vertexAr)
{
	setOrigin(vertexAr[0].position.x, vertexAr[0].position.y);
	hitbox.setPosition(this->getPosition());
}

CollidingPolygon::~CollidingPolygon()
{
}

void CollidingPolygon::setVertex(unsigned int index, sf::Vertex vertex)
{
	if (index < vertexAr.getVertexCount()) {
		vertexAr[index] = vertex;
	}
}

void CollidingPolygon::setTexture(const sf::Texture& texture)
{
	currtexture = const_cast<sf::Texture*>(&texture);
}

void CollidingPolygon::setTextures(const sf::Texture& regularTxtr, const sf::Texture& pointedTxtr)
{
	regularTexture = const_cast<sf::Texture*>(&regularTxtr);
	pointedTexture = const_cast<sf::Texture*>(&pointedTxtr);
}

sf::Vertex CollidingPolygon::getVertex(unsigned int index)
{
	return vertexAr[index];
}

bool CollidingPolygon::isContaining(const sf::Vector2f& point)
{
	bool isContaining = hitbox.isContaining(point);
	if (isContaining) {
		isPointed = true;
		setTexture(*pointedTexture);
	}
	else {
		isPointed = false;
		setTexture(*regularTexture);
	}
	return isContaining;
}

void CollidingPolygon::update(sf::Vector2f& mousePos)
{
}

void CollidingPolygon::move(const sf::Vector2f & offset)
{
	sf::Transformable::move(offset);
	hitbox.move(offset);
}

void CollidingPolygon::rotate(float angle)
{
	sf::Transformable::rotate(angle);
	hitbox.rotate(angle);
}

void CollidingPolygon::setPosition(const sf::Vector2f & position)
{
	sf::Transformable::setPosition(position);
	hitbox.setPosition(position);
}

void CollidingPolygon::setOrigin(const sf::Vector2f& newOrigin)
{
	sf::Transformable::setOrigin(newOrigin);
	hitbox.setOrigin(newOrigin);
}

void CollidingPolygon::setOrigin(float x, float y)
{
	sf::Transformable::setOrigin(x, y);
	hitbox.setOrigin(sf::Vector2f(x, y));
}

void CollidingPolygon::refreshHitbox()
{
	hitbox.refresh();
}

void CollidingPolygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	states.texture = currtexture;
	target.draw(vertexAr, states);
}


