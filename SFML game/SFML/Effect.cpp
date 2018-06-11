#include "Effect.h"

Effect::Effect(int lifeTime, Unit* owner) :
	owner(owner),
	lifeTime(lifeTime)
{
}

Effect::~Effect()
{
}
