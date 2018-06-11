#include "BlockTempObj.h"


BlockTempObj::BlockTempObj(sf::Vector2f& position) :
	TempGameObj(500),
	sprite(game->textureMan.blockIcon)
{
	sprite.setOrigin(game->textureMan.blockIcon.getSize().x / 2, game->textureMan.blockIcon.getSize().y / 2);
	setPosition(position);
}

BlockTempObj::BlockTempObj(const sf::Vector2f& position) :
	TempGameObj(500),
	sprite(game->textureMan.blockIcon)
{
	sprite.setOrigin(game->textureMan.blockIcon.getSize().x / 2, game->textureMan.blockIcon.getSize().y / 2);
	setPosition(position);
}

BlockTempObj::BlockTempObj(int lifeTime, const sf::Vector2f& position) :
	TempGameObj(lifeTime),
	sprite(game->textureMan.blockIcon)
{
	sprite.setOrigin(game->textureMan.blockIcon.getSize().x / 2, game->textureMan.blockIcon.getSize().y / 2);
	setPosition(position);
}

BlockTempObj::~BlockTempObj()
{
}

void BlockTempObj::setPosition(const sf::Vector2f &position) {
	sprite.setPosition(position);
}

void BlockTempObj::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}