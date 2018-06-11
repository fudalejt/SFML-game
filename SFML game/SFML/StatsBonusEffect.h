#pragma once
#include "Effect.h"
class StatsBonusEffect :
	public Effect
{
public:
	StatsBonusEffect(int lifeTime, Unit* owner);
	virtual ~StatsBonusEffect();
	virtual bool update(int time) override;
	virtual void start() override;

	void setHealthBonus(int value);
	void setAttacKBonus(int value);
	void setDefenseBonus(int value);
	void setSpeedBonus(float value);
	
	int healthBonus;
	int attackBonus;
	int defenseBonus;
	float speedBonus;	
};

