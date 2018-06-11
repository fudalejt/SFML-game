#include "TempGameObj.h"

TempGameObj::TempGameObj(int lifeTime):
	lifeTime(lifeTime)
{
}


TempGameObj::~TempGameObj()
{
}

void TempGameObj::update(int time) {
	//std::cout << "lifeTime : " << lifeTime << std::endl;
	lifeTime -= time;
	if (lifeTime <= 0)
		GameObject::game->deleteTempObj(this);
}