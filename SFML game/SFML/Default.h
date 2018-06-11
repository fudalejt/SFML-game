#pragma once
#include "GameMode.h"
class Default :
	public GameMode
{
public:
	Default();
	virtual ~Default();
	virtual State getType() override;
	virtual void update(int time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};

