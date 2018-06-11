#pragma once
#include "SFML/Graphics.hpp"

class Game;

enum State {
	DEFAULT = 0,
	POINTED_UNIT = 1,
	Q_TO_W = 2,
	Q_TO_E = 3,
	W_TO_Q = 4,
	W_TO_E = 5,
	E_TO_Q = 6,
	E_TO_W = 7
};

class GameMode :
	public sf::Drawable
{
public:
	GameMode();
	virtual ~GameMode();	
	virtual State getType() = 0;
	virtual void update(int time) = 0;

	static Game* game;
};

