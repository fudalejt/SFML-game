#pragma once
#include "GameMode.h"

class Unit;

class PointedUnit :
	public GameMode
{
public:
	PointedUnit(Unit&  unit);
	virtual ~PointedUnit();
	virtual State getType() override;
	virtual void update(int time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Unit& unit;
};

