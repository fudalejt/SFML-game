#include "PointedUnit.h"



PointedUnit::PointedUnit(Unit& unit):
	unit(unit)
{
}


PointedUnit::~PointedUnit()
{
}

State PointedUnit::getType() {
	return POINTED_UNIT;
}

void  PointedUnit::update(int time) {

}

void  PointedUnit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
}