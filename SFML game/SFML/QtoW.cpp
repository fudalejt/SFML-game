#include "QtoW.h"

#define RAD_TO_ANGL 57.295779513096787811;

QtoW::QtoW(Unit& unit):
	unit(unit),
	radius(50),
	angle(90),
	left(-1, -unit.getRadius()*sqrt(2)),
	right(1, unit.getRadius()*sqrt(2))
{
	actionTempl.setTexture(TextureManager::template1);
}

QtoW::~QtoW()
{
}

State QtoW::getType() {
	return Q_TO_W;
}

void QtoW::update(int time) {
	sf::Vector2f localPosition = (sf::Vector2f)sf::Mouse::getPosition(*(game->window));
	sf::Vector2f deltaPos = localPosition - unit.getPosition();
	float arctan = atan2(deltaPos.y, deltaPos.x);
	float angle = arctan * RAD_TO_ANGL;
	actionTempl.setRotation(angle - 45);
}

void  QtoW::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= unit.getTransform();
	states.transform.translate(unit.getOrigin());

	target.draw(actionTempl, states);
}

void QtoW::execute(Game * game)
{	
	for (Unit* u : game->army1) {
		if (u != &unit) {
			float dist = sqrt(pow(u->getPosition().x - unit.getPosition().x, 2) + pow(u->getPosition().y - unit.getPosition().y, 2));
			if (dist <= radius + u->getRadius() + unit.getRadius())
			{
				sf::Vector2f localUnitPos = u->getPosition() - unit.getPosition();
				localUnitPos = math::rotateVector(localUnitPos, math::getRotation(game->localPosition - unit.getPosition()));

				if (localUnitPos.y > left.a * localUnitPos.x + left.b && localUnitPos.y < right.a * localUnitPos.x + right.b) {
					unit.createNewKnockdown(*u);
					u->changeAttitude('Q');
				}
			}
		}		
	}

	for (Unit* u : game->army0) {
		if (u != &unit) {
			float dist = sqrt(pow(u->getPosition().x - unit.getPosition().x, 2) + pow(u->getPosition().y - unit.getPosition().y, 2));
			if (dist <= radius + u->getRadius() + unit.getRadius())
			{
				sf::Vector2f localUnitPos = u->getPosition() - unit.getPosition();
				localUnitPos = math::rotateVector(localUnitPos, math::getRotation(game->localPosition - unit.getPosition()));

				if (localUnitPos.y > left.a * localUnitPos.x + left.b && localUnitPos.y < right.a * localUnitPos.x + right.b)
					unit.createNewKnockdown(*u);
					u->changeAttitude('Q');
			}
		}	
	}
}

