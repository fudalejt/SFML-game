#pragma once
#include "SFML\Graphics.hpp"
#include "Game.h"

class Game;

class GameObject : 
	virtual public sf::Drawable, virtual public sf::Transformable
{
public:
	GameObject();
	virtual ~GameObject();
	static void setGame(Game* game);

	static Game* game;


};

