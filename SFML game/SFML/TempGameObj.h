#pragma once
#include "GameObject.h"

class TempGameObj :
	virtual public GameObject
{
public:
	TempGameObj(int lifeTime );
	virtual ~TempGameObj();
	void update(int time);

	int lifeTime;

};

