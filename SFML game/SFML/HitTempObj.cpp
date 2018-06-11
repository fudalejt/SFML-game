#include "HitTempObj.h"

HitTempObj::HitTempObj(sf::Vector2f& position) :
	TempGameObj(500),
	sprite(TextureManager::hitIcon)
{
	sprite.setOrigin(TextureManager::hitIcon.getSize().x / 2, TextureManager::hitIcon.getSize().y / 2);
	setPosition(position);
}

HitTempObj::HitTempObj(const sf::Vector2f& position) :
	TempGameObj(500),
	sprite(TextureManager::hitIcon)
{
	sprite.setOrigin(TextureManager::hitIcon.getSize().x / 2, TextureManager::hitIcon.getSize().y / 2);
	setPosition(position);
}

HitTempObj::HitTempObj(int lifeTime, const sf::Vector2f& position):
	TempGameObj(lifeTime),
	sprite(TextureManager::hitIcon)
{
	sprite.setOrigin(TextureManager::hitIcon.getSize().x / 2, TextureManager::hitIcon.getSize().y / 2);
	setPosition(position);
}

HitTempObj::~HitTempObj()
{
}

void HitTempObj::setPosition(const sf::Vector2f &position) {
	sprite.setPosition(position);
}

void HitTempObj::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}