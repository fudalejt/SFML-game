#pragma once
#include "Unit.h"
class Effect
{
public:
	Effect(int lifeTime, Unit* owner);
	virtual ~Effect();
	virtual bool update(int time) = 0; //return true if the effect must be delete
	virtual void start() = 0;

	Unit* const owner;
	int lifeTime;
};
