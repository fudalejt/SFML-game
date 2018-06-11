#include "Unit.h"
#include "Attack.h"
#include "Stay.h"
#include "Move.h"
#include "MoveTo.h"
#include "JumpAway.h"
#include "Knockdown.h"
#include "TextureManager.h"
#include "ArmyColors.h"
#include "Game.h"
#include "HitTempObj.h"
#include "BlockTempObj.h"
#include "StatsBonusEffect.h"
#include "MathUtilities.h"

#include <math.h>
#include <cstdlib>
#include <time.h>

#include <iostream>

//#define ATTACKS_PER_TURN 1.f;

extern sf::Color armyColor[2][2];

const int Unit::ATTITUDE_CHANGE_TIME = 2000;
const int Unit::AI_ATTITUDE_CHANGE_TIME = 5000;


Unit::Unit(int army, float radius) :
	CirclePointObj(radius),
	morale(2),
	health(50),
	army(army),
	attackCld(0),
	attitudeChangeCld(0),
	aiAttitudeChangeCld(0),
	moveSpeed(0.03f),
	moveLine(sf::Vector2f(1, 2)),
	statsEffect(nullptr),

	displayInterface(true),
	ai(false),
	animationCounter(0),
	animationTimeCounter(0)

{
	constructor();
}

Unit::Unit(int army) :
	CirclePointObj(50.f),
	morale(2),
	health(50),
	army(army),
	attackCld(0),
	attitudeChangeCld(0),
	aiAttitudeChangeCld(0),
	moveSpeed(0.03f),
	moveLine(sf::Vector2f(1, 2)),
	statsEffect (nullptr),

	displayInterface(true),
	ai(false),
	animationCounter(0),
	animationTimeCounter(0)
{	
	constructor();
}

void Unit::constructor() {
	unitSprite.setOrigin(50, 50);
	unitSprite.setPosition(this->getOrigin());
	if (army == 0) {
		regularColor = armyColor[0][0];
		pointedColor = armyColor[0][1];
		unitSprite.setTexture(TextureManager::unit0);
	}
	else if (army == 1) {
		regularColor = armyColor[1][0];
		regularColor = armyColor[1][0];
		pointedColor = armyColor[1][1];
		unitSprite.setTexture(TextureManager::unit1);
	}
	unitSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

	orders.push_front(new Stay(-1));
	setPointed(false);
	moveLine.setPosition(getOrigin());

	attitudeIcon.setTexture(TextureManager::attitudeIcons);
	changeAttitude('Q');

	if (!font.loadFromFile("arial.ttf"))
	{
		throw "Wrong load of a resource [Unit.font]";
	}
	//texts
	healthTxt.setFont(font);
	healthTxt.setString(std::to_string(health));
	healthTxt.setPosition(getOrigin() + sf::Vector2f(20, -50));
	healthTxt.setCharacterSize(24);
	healthTxt.setFillColor(sf::Color::Red);

}
Unit::~Unit()
{
	clearOrders();
	while (fightList.size() > 0) {
		fightList.front()->createNewStay();
	}
}

void Unit::update(int time) {
	//cooldown refresh
	if (attackCld > 0)
		attackCld -= time;
	else
		attackCld = 0;

	if (attitudeChangeCld > 0)
		attitudeChangeCld -= time;
	else 
		attitudeChangeCld = 0;
		
	//effect
	if (statsEffect != nullptr) {
		if (statsEffect->update(time) == true) {
			delete statsEffect;
			statsEffect = nullptr;
		}
	}		
		
	//an order execution
	if (orders.front()->getType() == MOVE) {	
		//refresh move line
		Move* move = dynamic_cast<Move*>(orders.front());
		float angle = atan2((move->targetPos.y - getPosition().y), (move->targetPos.x - getPosition().x));
		angle = angle * math::RAD_TO_ANGL;
		moveLine.setRotation(angle);
		unitSprite.setRotation(angle);
		float length = sqrt(pow(move->targetPos.y - getPosition().y, 2) + pow(move->targetPos.x - getPosition().x, 2));
		moveLine.setScale(length, 1);

		executeMove(time);
	
	}
	else if (orders.front()->getType() == MOVE_TO) {
		//refresh move line
		MoveTo* move = dynamic_cast<MoveTo*>(orders.front());
		float angle = atan2((move->target.getPosition().y - getPosition().y), (move->target.getPosition().x - getPosition().x));
		angle = angle * math::RAD_TO_ANGL;		
		moveLine.setRotation(angle);
		unitSprite.setRotation(angle);
		float length = sqrt(pow(move->target.getPosition().y - getPosition().y, 2) + pow(move->target.getPosition().x - getPosition().x, 2));
		moveLine.setScale(length, 1);

		executeMoveTo(time);
	}
	else if (orders.front()->getType() == ATTACK) {
		//refresh move line
		Attack* attack = dynamic_cast<Attack*>(orders.front());
		float angle = atan2((attack->target.getPosition().y - getPosition().y), (attack->target.getPosition().x - getPosition().x));
		angle = angle * math::RAD_TO_ANGL;
		moveLine.setRotation(angle);
		unitSprite.setRotation(angle);
		float length = sqrt(pow(attack->target.getPosition().y - getPosition().y, 2) + pow(attack->target.getPosition().x - getPosition().x, 2));
		moveLine.setScale(length, 1);

		executeAttack(time);
		if (attack->update(time) == true)
			deleteCurrOrder();
		
	}
	else if (orders.front()->getType() == JUMP_AWAY) {
		executeJumpAway(time);
	}
	else if (orders.front()->getType() == KNOCKDOWN) {
		executeKnockdown(time);
	}

	//refresh orders for AI
	if (ai == true) {
		if (orders.size() > 0 && orders.front()->getType() == STAY) {
			if (army == 0) {
				Unit* nearest = game->army1.front();
				float distance = math::getDistanceBetween( this->getPosition(), nearest->getPosition() );
				std::list<Unit*>::iterator it = game->army1.begin();
				++it;
				while (it != game->army1.end()) {
					float newDistance = math::getDistanceBetween(this->getPosition(), (*it)->getPosition());
					if (distance > newDistance) {
						distance = newDistance;
						nearest = *it;
					}
					++it;
				}

				if (nearest != nullptr) {
					this->createNewAttack(*nearest);
				}
			}
			else if (army == 1) {
				Unit* nearest = game->army0.front();
				float distance = math::getDistanceBetween(this->getPosition(), nearest->getPosition());
				std::list<Unit*>::iterator it = game->army0.begin();
				++it;
				while (it != game->army0.end()) {
					float newDistance = math::getDistanceBetween(this->getPosition(), (*it)->getPosition());
					if (distance > newDistance) {
						distance = newDistance;
						nearest = *it;
					}
					++it;
				}

				if (nearest != nullptr) {
					this->createNewAttack(*nearest);
				}
			}

		}
	}

	//random attitudes change
	if (ai == true) {
		if (aiAttitudeChangeCld > 0) {
			aiAttitudeChangeCld -= time;
		}
		else if (attitudeChangeCld == 0) {
			int whichAtt = rand() % 3;
			switch (whichAtt) {
			case 0:
				changeAttitude('Q');
				break;
			case 1:
				changeAttitude('W');
				break;
			case 2:
				changeAttitude('E');
				break;
			}
			aiAttitudeChangeCld = rand() % AI_ATTITUDE_CHANGE_TIME;
		}
	}
	
}

void Unit::executeKnockdown(int time) {
	Knockdown* order = dynamic_cast<Knockdown*>(orders.front());
	sf::Vector2f& offset = order->getOffset(time);
	if (offset.x == 0 && offset.y == 0) {
		createNewStay();
	}
	else {
		move(offset);
		std::list<Unit*> col = game->checkCollision(*this);
		if (col.size() > 0) {
			for (Unit* u : col) {
				createNewKnockdown(*u);
			}
			move(-offset);
			createNewStay();
		}
	}

}

void Unit::executeJumpAway(int time) {
	JumpAway* jump = dynamic_cast<JumpAway*>(orders.front());
	JumpResult result = jump->jumpAway(this, time);
	if (result == ENDED || result ==  INTERRUPTED) {
		std::cout <<"JUMP AWAY ENDED";
		if (attitude == 'E') {
			createNewAttack(jump->enemy);
		}
		else {
			createNewStay();
		}
	}		
}



void Unit::executeMove(int time) {
	Move *m = dynamic_cast<Move*>(orders.front());
	sf::Vector2f pos = getPosition();
	sf::Vector2f delta = m->targetPos - pos;

	float z = sqrt(pow(delta.x, 2) + pow(delta.y, 2));

	if (moveSpeed * time >= z) {
		setPosition(m->targetPos);
		createNewStay();
	}
	else {
		sf::Vector2f offset = sf::Vector2f(delta.x / z * moveSpeed * time, delta.y / z * moveSpeed * time);
		move(offset);
		std::list<Unit*> col = game->checkCollision(*this);
		if (col.size() > 0) {
			setPosition(pos);
			if (col.size() == 1)
			{
				moveAroundObstacle(col.front()->getPosition(), m->targetPos, time);				
			}
		}	

		moveAnimationUpdate(time);
	}
}

void Unit::executeMoveTo(int time) {
	MoveTo *m = dynamic_cast<MoveTo*>(orders.front());
	sf::Vector2f pos = getPosition();
	sf::Vector2f delta = m->target.getPosition() - pos;

	float z = sqrt(pow(delta.x, 2) + pow(delta.y, 2));

	if (moveSpeed * time >= z) {
		setPosition(m->target.getPosition());
		createNewStay();
	}
	else {
		sf::Vector2f offset = sf::Vector2f(delta.x / z * moveSpeed * time, delta.y / z * moveSpeed * time);
		move(offset);
		std::list<Unit*> col = game->checkCollision(*this);
		if (col.size() > 0) {
			setPosition(pos);
			if (col.size() == 1)
			{
				moveAroundObstacle(col.front()->getPosition(), m->target.getPosition(), time);
			}
		}

		moveAnimationUpdate(time);
	}
}

void Unit::executeAttack(int time){		
	Attack *a = dynamic_cast<Attack*>(orders.front());
	Unit* attackTarget = dynamic_cast<Unit*>(&(a->target));
	sf::Vector2f pos = getPosition();
	sf::Vector2f delta = attackTarget->getPosition() - pos;

	float z = sqrt(pow(delta.x, 2) + pow(delta.y, 2));

	if (moveSpeed * time >= z) {
		setPosition(attackTarget->getPosition());
		deleteCurrOrder();
	}
	else {
		sf::Vector2f offset = sf::Vector2f(delta.x / z * moveSpeed * time, delta.y / z * moveSpeed * time);
		move(offset);
		std::list<Unit*> col = game->checkCollision(*this);
		Unit* target = nullptr;
		for (Unit* u : col) {
			if (u == attackTarget)
				target = u;
		}
				
		if (target != nullptr) {
			setPosition(pos);
			if (attackCld == 0) {
				attackCld = attackSpeed + defense / attack;		
				game->addTempObj(new HitTempObj((int)(attackCld * 0.7), getPosition()));

				if (math::getRandom( 50 + (attack - target->defense)*10 )) {
					target->takeDamage(10, this);
				}				
			}
			return;
		}
		else{
			if (col.size() == 1) {
				setPosition(pos);
				if (col.front()->army == this->army) { 					
					moveAroundObstacle(col.front()->getPosition(), attackTarget->getPosition(), time);
					
				}
				else{
					createNewAttack(*col.front());
				}
			}
			else if (col.size() > 1) {
				setPosition(pos);
				return;
			}
		}
		moveAnimationUpdate(time);

	}
}

void Unit::moveAnimationUpdate(int time) {
	animationTimeCounter += time;
	if (animationCounter == 0) {
		animationCounter = 1;
		setAnimationFrame(1);
	}
	else if (animationCounter == 1 && animationTimeCounter > 500) {
		animationCounter = 2;
		setAnimationFrame(2);
	}
	else if (animationCounter == 2 && animationTimeCounter > 1000) {
		animationCounter = 1;
		setAnimationFrame(1);
		animationTimeCounter = 0;
	}
}

void Unit::createNewJumpAway(Unit* enemy, int damage) {
	clearOrders();
	orders.push_front(new JumpAway(-1, *enemy, damage));
	
}

void Unit::deleteCurrOrder() {
	Attack* attackOrd = dynamic_cast<Attack*>(*orders.begin());
	if (attackOrd != nullptr) {
		attackOrd->target.removeFromFightList(this);
	}

	delete *orders.begin();
	orders.erase(orders.begin());
	if (orders.size() == 0)
		orders.push_front(new Stay(-1));
}

void Unit::moveAroundObstacle(const sf::Vector2f& obstPos, const sf::Vector2f& targetPos, int time) {
	sf::Vector2f deltaMove;
	sf::Vector2f deltaColPos = obstPos - getPosition();
	sf::Vector2f deltaTarPos = targetPos - getPosition();

	float a1 = deltaColPos.y / deltaColPos.x;
	float a2 = -deltaColPos.x / deltaColPos.y;
	float aPow2 = a2*a2;
	float d = moveSpeed * time;

	if (deltaColPos.y >= 0) {
		if (deltaColPos.x > 0) {
			if (deltaTarPos.y > a1 * deltaTarPos.x) {
				deltaMove.x = -(d) / (sqrt(aPow2 + 1));
				deltaMove.y = -(a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);
			}
			else {
				deltaMove.x = (d) / (sqrt(aPow2 + 1));
				deltaMove.y = (a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);
			}
		}
		else {
			if (deltaTarPos.y > a1 * deltaTarPos.x) {
				deltaMove.x = (d) / (sqrt(aPow2 + 1));
				deltaMove.y = (a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);

			}
			else {
				deltaMove.x = -(d) / (sqrt(aPow2 + 1));
				deltaMove.y = -(a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);
			}
		}
	}
	else {
		if (deltaColPos.x <= 0) {
			if (deltaTarPos.y < a1 * deltaTarPos.x) {
				deltaMove.x = (d) / (sqrt(aPow2 + 1));
				deltaMove.y = (a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);
			}
			else {

				deltaMove.x = -(d) / (sqrt(aPow2 + 1));
				deltaMove.y = -(a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);

			}
		}
		else {
			if (deltaTarPos.y < a1 * deltaTarPos.x) {
				deltaMove.x = -(d) / (sqrt(aPow2 + 1));
				deltaMove.y = -(a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);
			}
			else {
				deltaMove.x = (d) / (sqrt(aPow2 + 1));
				deltaMove.y = (a2 * d) / (sqrt(aPow2 + 1));
				move(deltaMove);
			}
		}
	}
}

void Unit::setAnimationFrame(int frameNr)
{
	unitSprite.setTextureRect(sf::IntRect(frameNr * 100, 0, 100, 100));
}

void Unit::changeAttitude(char newAttitude) 
{
	if (attitudeChangeCld <= 0) {
		if (newAttitude == 'Q') {
			attitudeIcon.setTextureRect(sf::IntRect(0, 0, 29, 29));
			attitude = newAttitude;			
			attitudeChangeCld = ATTITUDE_CHANGE_TIME;

		}
		else if (newAttitude == 'W') {
			attitudeIcon.setTextureRect(sf::IntRect(29, 0, 29, 29));
			attitude = newAttitude;			
			attitudeChangeCld = ATTITUDE_CHANGE_TIME;
			
		}
		else if (newAttitude == 'E') {
			attitudeIcon.setTextureRect(sf::IntRect(59, 0, 29, 29));
			attitude = newAttitude;				
			attitudeChangeCld = ATTITUDE_CHANGE_TIME;
			
		}
		BaseStats::setParams(this, attitude);

	}	
}

void Unit::takeDamage(int damage, Unit* enemy) {
	if (math::getRandom(dodges * 10)) {
		std::cout << "JUMP AWAY" << std::endl;
		createNewJumpAway(enemy, damage);
		game->addTempObj(new BlockTempObj(1000, getPosition()));
	}
	else {
		enemy->setHealth(enemy->health - damage);

		Attack* attOrder = dynamic_cast<Attack*>(orders.front());
		if (attOrder == nullptr || dynamic_cast<Unit*>(&(attOrder->target)) != enemy)
			createNewAttack(*enemy);
	}

	
}

void Unit::setHealth(int newHealthVal) {
	health = newHealthVal;
	if (health <= 0)
		game->deleteUnit(this);
	healthTxt.setString(std::to_string(health));
}

void Unit::createNewMove(sf::Vector2f mousePos) {
	clearOrders();
	this->orders.push_front(new Move(-1, mousePos));
	moveLine.setFillColor(sf::Color::Green);
	animationCounter = 0;
}

void Unit::createNewMoveTo(Unit& target) {
	clearOrders();
	this->orders.push_front(new MoveTo(-1, target));
	moveLine.setFillColor(sf::Color::Blue);
}

void Unit::createNewAttack(Unit& target) {
	clearOrders();
	this->orders.push_front(new Attack(-1, target, *this));
	moveLine.setFillColor(sf::Color::Red);
}

void Unit::createNewStay(){
	clearOrders();
	this->orders.push_front(new Stay(-1));
	animationTimeCounter = 0;
	setAnimationFrame(0);
}

void Unit::createNewKnockdown(Unit& target) {
	target.clearOrders();
	target.orders.push_front(new Knockdown(-1, 25, target.getPosition() - this->getPosition()));
}

void  Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {	
	CirclePointObj::draw(target, states);
	states.transform *= getTransform();
	if (orders.front() != nullptr && orders.front()->getType() == MOVE || orders.front()->getType() == MOVE_TO || orders.front()->getType() == ATTACK)
		target.draw(moveLine, states.transform);

	target.draw(unitSprite, states.transform);	

	if (displayInterface) {
		target.draw(attitudeIcon, states.transform);
		target.draw(healthTxt, states.transform);
	}
}

bool Unit::checkCollision(Unit& other) {
	sf::Vector2f pos = getPosition();
	sf::Vector2f otherPos = other.getPosition();

	float dist = sqrt( pow(otherPos.x - pos.x, 2) + pow(otherPos.y - pos.y, 2));
	if (dist <= getRadius() + other.getRadius())
		return true;
	else
		return false;
}

void  Unit::addToFightList(Unit* enemy) {
	fightList.push_back(enemy);
}

void  Unit::removeFromFightList(Unit* enemy) {
	std::list<Unit*>::iterator it;
	for (it = fightList.begin(); it != fightList.end(); it++) {
		if (*it == enemy) {
			fightList.erase(it);
			break;
		}
	}
}

void Unit::clearOrders() {
	while (orders.size() > 0) {
		delete orders.front();
		orders.pop_front();
	}
}
