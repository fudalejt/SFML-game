#pragma once
#include "GameMode.h"
#include "Unit.h"

class QtoE :
	public GameMode
{
public:
	QtoE(Unit& unit);
	virtual ~QtoE();
	virtual State getType() override;
	virtual void update(int time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void execute(Game* game);

	Unit& unit;
};

