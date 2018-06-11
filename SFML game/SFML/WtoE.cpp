#include "WtoE.h"



WtoE::WtoE(Unit& unit):
	unit(unit)
{
}


WtoE::~WtoE()
{
}

State WtoE::getType()
{
	return W_TO_E;
}

void WtoE::update(int time)
{
}

void WtoE::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void WtoE::execute(Game * game)
{
	Unit* u = game->getPointedUnit();
	if (u != nullptr && unit.army != u->army) {
		u->changeAttitude('E');
	}
}
