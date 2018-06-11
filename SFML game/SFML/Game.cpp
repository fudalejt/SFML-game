#include "Game.h"
#include "Unit.h"
#include "Attack.h"
#include "Stay.h"
#include "Move.h"
#include "MoveTo.h"
#include "TempGameObj.h"
#include "GameObject.h"
#include "GameMode.h"
#include "Default.h"
#include "PointedUnit.h"
#include "QtoW.h"
#include "QtoE.h"
#include "WtoE.h"

Game::Game()
{
	gameMode = new Default();
	GameMode::game = this;
}

Game::~Game()
{
	for (Unit* u : army0) {
		delete u;
	}
	for (Unit* u : army1) {
		delete u;
	}
}

void Game::updateAll() {
	int deltaTime = mainClock.getElapsedTime().asMilliseconds();
	mainClock.restart();
	for (Unit* u : army0) {
		u->update(deltaTime);
	}

	for (Unit* u : army1) {
		u->update(deltaTime);
	}

	for (TempGameObj* t : tempObjects)
		t->update(deltaTime);

	gameMode->update(deltaTime);
}

void Game::lmbPressed() {
	switch (gameMode->getType()) {
	case DEFAULT:
		for (Unit* u : army0) {
			if (u->isContaining(localPosition)) {
				pointedObj = u;
				u->setPointed(true);
				delete gameMode;
				gameMode = new PointedUnit(*u);
				break;
			}
		}

		for (Unit* u : army1) {
			if (u->isContaining(localPosition)) {
				pointedObj = u;
				u->setPointed(true);
				delete gameMode;
				gameMode = new PointedUnit(*u);
				break;
			}
		}
		break;
	case POINTED_UNIT:
	{
		bool pointedSomething = false;
		//check whole army 0
		for (Unit* u : army0) {
			if (u->isContaining(localPosition)) {
				pointedObj->setPointed(false);
				pointedObj = u;
				u->setPointed(true);
				pointedSomething = true;
				break;
			}
		}

		//check whole army 1
		for (Unit* u : army1) {
			if (u->isContaining(localPosition)) {
				pointedObj->setPointed(false);
				pointedObj = u;
				u->setPointed(true);
				pointedSomething = true;
				break;
			}
		}
		if (!pointedSomething) {
			pointedObj->setPointed(false);
			pointedObj = nullptr;
			delete gameMode;
			gameMode = new Default();
		}
		break;
	}		

	case Q_TO_W:
	{
		QtoW* mode = dynamic_cast<QtoW*> (gameMode);
		mode->execute(this);
		delete gameMode;
		gameMode = new PointedUnit(mode->unit);
		break;		
	}
		
	case Q_TO_E: 
	{
		QtoE * mode = dynamic_cast<QtoE*> (gameMode);
		mode->execute(this);
		delete gameMode;
		gameMode = new PointedUnit(mode->unit);
		break;
	}	

	case W_TO_E:
	{
		WtoE * mode = dynamic_cast<WtoE*> (gameMode);
		mode->execute(this);
		delete gameMode;
		gameMode = new PointedUnit(mode->unit);
		break;
	}
		
	}
}

void Game::rmbPressed() {
	switch (gameMode->getType()) {
	case DEFAULT:
		break;
	case POINTED_UNIT:	
		Unit * u = dynamic_cast<Unit*>(pointedObj);
		if (u != nullptr) {
			Unit* obj = dynamic_cast<Unit*>(getPointed());
			if (obj == nullptr)
				u->createNewMove(localPosition);
			else {
				if (u->army == obj->army)
					u->createNewMoveTo(*obj);
				else
					u->createNewAttack(*obj);
			}
		}		
		break;
	}
}

void Game::draw(sf::RenderWindow& window) {
	window.clear();
	for (Unit* u : army0)
		window.draw(dynamic_cast<sf::Drawable&>(*u));

	for (Unit* u : army1)
		window.draw(dynamic_cast<sf::Drawable&>(*u));

	for (TempGameObj* t : tempObjects) {
		window.draw(dynamic_cast<sf::Drawable&>(*t));
	}

	window.draw(dynamic_cast<sf::Drawable&>(*gameMode));

	window.display();
}

void Game::performEvent(sf::Event& event) {
	if (event.type == sf::Event::Closed)
		window->close();
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			STOP = STOP ? false : true;
		}
		else if (event.key.code == sf::Keyboard::Q) {
			if (pointedObj != nullptr) {
				Unit* u = dynamic_cast<Unit*>(pointedObj);
				u->changeAttitude('Q');
			}
		}
		else if (event.key.code == sf::Keyboard::W) {
			if (pointedObj != nullptr) {
				Unit* u = dynamic_cast<Unit*>(pointedObj);	

				char oldAtt = u->attitude;
				u->changeAttitude('W');
				if (oldAtt == 'Q' && u->attitude == 'W') {
					delete gameMode;
					gameMode = new QtoW(*u);
				}		   
			}
		}
		else if (event.key.code == sf::Keyboard::E) {
			if (pointedObj != nullptr) {
				Unit* u = dynamic_cast<Unit*>(pointedObj);

				char oldAtt = u->attitude;
				u->changeAttitude('E');
				if (oldAtt == 'Q' && u->attitude == 'E') {
					delete gameMode;
					gameMode = new QtoE(*u);
				}
				else if (oldAtt == 'W' && u->attitude == 'E') {
					delete gameMode;
					gameMode = new WtoE(*u);
				}
			}
		}
		else if (event.key.code == sf::Keyboard::R) {
			if (pointedObj != nullptr) {
				Unit* u = dynamic_cast<Unit*>(pointedObj);
				u->changeAttitude('R');
			}
		}
		else if (event.key.code == sf::Keyboard::S) {
			if (pointedObj != nullptr) {
				Unit* u = dynamic_cast<Unit*>(pointedObj);
				u->createNewStay();
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f localPosition = (sf::Vector2f)sf::Mouse::getPosition(*window);
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			lmbPressed();
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			rmbPressed();
		}
	}

	else if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
		}
	}
}

void Game::deleteAll() {
	while (objectsToDelete.size() > 0) {
		GameObject* ob = objectsToDelete.front();
		objectsToDelete.pop_front();

		Unit* unit = dynamic_cast<Unit*>(ob);
		if (unit != nullptr) {
			std::list<Unit*>::iterator it;
			if (unit->army == 0) {
				for (it = army0.begin(); it != army0.end(); ++it) {
					if (*it == unit) {
						if (*it == pointedObj) {
							pointedObj = nullptr;
							delete gameMode;
							gameMode = new Default();
						}
						delete *it;
						army0.erase(it);						
						break;
					}
				}
			}
			else if (unit->army == 1) {
				for (it = army1.begin(); it != army1.end(); ++it) {
					if (*it == unit) {
						if (*it == pointedObj) {
							pointedObj = nullptr;
							delete gameMode;
							gameMode = new Default();
						}
						delete *it;
						army1.erase(it);						
						break;
					}
				}
			}
		}	
		else {
			TempGameObj* temp = dynamic_cast<TempGameObj*>(ob);
			if (temp != nullptr) {
				std::list<TempGameObj*>::iterator it;
				for (it = tempObjects.begin(); it != tempObjects.end(); ++it) {
					if (*it == temp) {
						delete *it;
						tempObjects.erase(it);						
						break;
					}
				}
			}
		}
	}
}

GameObject* Game::getPointed() {
	for (Unit* u : army0) {
		if (u->isContaining(localPosition))
			return u;
	}

	for (Unit* u : army1) {
		if (u->isContaining(localPosition))
			return u;
	}

	return nullptr;
}

Unit* Game::getPointedUnit()
{
	for (Unit* u : army0) {
		if (u->isContaining(localPosition))
			return u;
	}

	for (Unit* u : army1) {
		if (u->isContaining(localPosition))
			return u;
	}

	return nullptr;
}

std::list<Unit*> Game::checkCollision(Unit& testedUnit) {
	std::list<Unit*> result;

	if (testedUnit.army == 0) {
		for (Unit* u : army0) {
			if (u != &testedUnit) {
				if (testedUnit.checkCollision(*u) == true)
					result.push_back(u);
			}
		}

		for (Unit* u : army1) {			
			if (testedUnit.checkCollision(*u) == true)
				result.push_back(u);			
		}
	}
	else if(testedUnit.army == 1){
		for (Unit* u : army0) {
			if (testedUnit.checkCollision(*u) == true)
				result.push_back(u);
		}

		for (Unit* u : army1) {
			if (u != &testedUnit) {
				if (testedUnit.checkCollision(*u) == true)
					result.push_back(u);
			}
		}		
	}
	return result;
}

void Game::addTempObj(TempGameObj* tempObj) {
	tempObjects.push_back(tempObj);
}

void Game::deleteUnit(Unit* unit) {
	objectsToDelete.push_back(unit);
}

void Game::deleteTempObj(TempGameObj* temp) {
	objectsToDelete.push_back(temp);
}

int Game::play() {
	GameObject::setGame(this);
	Order::setGame(this);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	window = new sf::RenderWindow(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Default, settings);

	Unit* unit;
	unit = new Unit(0);
	unit->setPosition(sf::Vector2f(150, 150));
	army0.push_back(unit);

	unit = new Unit(0);
	unit->setPosition(sf::Vector2f(250, 300));
	army0.push_back(unit);

	unit = new Unit(0);
	unit->setPosition(sf::Vector2f(200, 400));
	army0.push_back(unit);

	unit = new Unit(0);
	unit->setPosition(sf::Vector2f(200, 600));
	army0.push_back(unit);


	unit = new Unit(1);
	unit->setPosition(sf::Vector2f(350, 200));
	army1.push_back(unit);
	unit->ai = true;

	unit = new Unit(1);
	unit->setPosition(sf::Vector2f(400, 400));
	army1.push_back(unit);
	unit->ai = true;

	unit = new Unit(1);
	unit->setPosition(sf::Vector2f(400, 500));
	army1.push_back(unit);
	unit->ai = true;

	unit = new Unit(1);
	unit->setPosition(sf::Vector2f(450, 600));
	army1.push_back(unit);
	unit->ai = true;
	
	mainClock.restart();

	while (window->isOpen())
	{
		if (mainClock.getElapsedTime() > sf::milliseconds(16))
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				performEvent(event);
			}

			localPosition = (sf::Vector2f)sf::Mouse::getPosition(*window);

			if (STOP == false)
				updateAll();
			else
				mainClock.restart();

			draw(*window);

			deleteAll();
		}
	}

	return 0;
}