#pragma once
#include "Hitbox.h"
#include "LinFuncParam.h"

class VertexHitbox :
	public Hitbox
{
public:
	sf::VertexArray vertexAr;

	VertexHitbox(sf::VertexArray& vertexAr);
	virtual ~VertexHitbox();
	virtual bool isContaining(const sf::Vector2f& point) override;
	virtual void refresh() override;

private:
	std::vector<LinFuncParam> linPar;

};

