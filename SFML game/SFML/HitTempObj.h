#pragma once
#include "TempGameObj.h"

class HitTempObj :
	virtual public TempGameObj	
{
public:
	HitTempObj(sf::Vector2f& position);
	HitTempObj(const sf::Vector2f& position);
	HitTempObj(int lifeTime, const sf::Vector2f& position);
	virtual ~HitTempObj();
	void setPosition(const sf::Vector2f &position);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};

