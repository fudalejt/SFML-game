#pragma once
#include "TempGameObj.h"
class BlockTempObj :
	public TempGameObj
{
public:
	BlockTempObj(sf::Vector2f& position);
	BlockTempObj(const sf::Vector2f& position);
	BlockTempObj(int lifeTime, const sf::Vector2f& position);
	virtual ~BlockTempObj();
	void setPosition(const sf::Vector2f &position);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};

