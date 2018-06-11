#include "StatsBonusEffect.h"
#include "Unit.h"
#include <iostream>

StatsBonusEffect::StatsBonusEffect(int lifeTime, Unit* owner):
	Effect(lifeTime, owner),
	healthBonus(0),
	attackBonus(0),
	defenseBonus(0),
	speedBonus(0.f)
{	
}

StatsBonusEffect::~StatsBonusEffect()
{
	//owner->attack -= attackBonus;
	//owner->defense -= defenseBonus;
	//owner->speed -= speedBonus;
	//owner->health -= healthBonus;
}

bool StatsBonusEffect::update(int time) {
	lifeTime -= time;
	if (lifeTime <= 0)
		return true;
	else
		return false;
}

void StatsBonusEffect::setHealthBonus(int value) {
	healthBonus = value;
}

void StatsBonusEffect::setAttacKBonus(int value) {
	attackBonus = value;
}

void StatsBonusEffect::setDefenseBonus(int value) {
	defenseBonus = value;
}

void StatsBonusEffect::setSpeedBonus(float value) {
	speedBonus = value;
}

void StatsBonusEffect::start() {
	//owner->attack += attackBonus;
	//owner->defense += defenseBonus;
	//owner->speed += speedBonus;
	//owner->health += healthBonus;
}