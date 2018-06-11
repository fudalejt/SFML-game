#include "PointableObj.h"


PointableObj::PointableObj():
	isPointed(false)
{
}


PointableObj::~PointableObj()
{
}

void PointableObj::setPointed(bool isPointed)
{
	this->isPointed = isPointed;
}
