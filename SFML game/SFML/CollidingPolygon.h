/*
CollidingPolygon is a sprite with a multi vertex hitbox. It can perform a test whether a point is contained by the hitbox. 
Class may by used as a base for elements of GUI that can be pointed by the mouse cursor.
Can be transfom.
*/

#include <SFML/Graphics.hpp>
#include <vector>
#include "PointableObj.h"
#include "VertexHitbox.h"

#pragma once

class LinFuncParam;

class CollidingPolygon : public PointableObj
{
public:
	CollidingPolygon( sf::VertexArray& vertexAr);
	virtual ~CollidingPolygon();	
	
	virtual bool isContaining(const sf::Vector2f& point) override;
	virtual void update(sf::Vector2f& mousePos) override;
	void move(const  sf::Vector2f &offset);
	void setPosition(const sf::Vector2f &position);
	void rotate(float angle);	
	void setOrigin(const sf::Vector2f &newOrigin);
	void setOrigin(float x, float y);
	void setVertex(unsigned int index, sf::Vertex vertex);
	void setTexture(const sf::Texture& texture);
	void setTextures(const sf::Texture& regularTxtr, const sf::Texture& pointedTxtr);
	sf::Vertex getVertex(unsigned int index);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void refreshHitbox() override;

	VertexHitbox hitbox;
	sf::VertexArray& vertexAr;
	sf::Texture 
		*currtexture,
		*regularTexture,
		*pointedTexture;

};

