#pragma once
#include "GameMode.h"
#include "Unit.h"
#include "TextureManager.h"
#include "MathUtilities.h"

class QtoW :
	public GameMode
{
public:
	QtoW(Unit& unit);
	virtual ~QtoW();
	virtual State getType() override;
	virtual void update(int time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void execute(Game* game);

	Unit& unit;
	float angle;
	float radius;

protected :
	sf::Sprite actionTempl;	
	math::LinearFuncParams 
		left,
		right;


};

