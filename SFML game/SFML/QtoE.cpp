#include "QtoE.h"

QtoE::QtoE(Unit& unit):
	unit(unit)
{
}


QtoE::~QtoE()
{
}

State QtoE::getType()
{
	return Q_TO_E;
}

void QtoE::update(int time)
{
}

void QtoE::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void QtoE::execute(Game * game)
{
	Unit* u = game->getPointedUnit();
	if (u != nullptr && unit.army != u->army) {
		u->changeAttitude('W');
	}
}
