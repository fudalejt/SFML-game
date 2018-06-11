#pragma once
#include "ActionPool.h"

class QActionPool : public ActionPool
{
public:
	QActionPool();
	virtual ~QActionPool();

	const int stBlockCount; //st: STatic
	const int stAttackCount;
	const int stCounterCount;

};

