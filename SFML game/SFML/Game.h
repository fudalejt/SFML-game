#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CollidingPolygon.h"
#include "CirclePointObj.h"
#include "TextureManager.h"

#include <list>

class Unit;
class TempGameObj;
class GameObject;
class GameMode;

class Game
{
public:
	Game();
	~Game();
	int play();
	std::list<Unit*> checkCollision(Unit& testedUnit);
	void addTempObj(TempGameObj* tempObj);
	void deleteUnit(Unit* unit);
	void deleteTempObj(TempGameObj* temp);
	GameObject* getPointed();
	Unit* getPointedUnit();



	TextureManager textureMan;
	sf::RenderWindow* window;
	std::list<Unit*>
		army0,
		army1;
	sf::Vector2f localPosition;

protected:
	void updateAll();
	void lmbPressed();
	void rmbPressed();
	void draw(sf::RenderWindow& window);
	void performEvent(sf::Event& event);
	void deleteAll();

	sf::Clock mainClock = sf::Clock();
	PointableObj* pointedObj = nullptr;
	bool STOP = false;
	CollidingPolygon *polygon;
	std::list<GameObject*> objectsToDelete;
	std::list<TempGameObj*> tempObjects;
	GameMode* gameMode;	
};

