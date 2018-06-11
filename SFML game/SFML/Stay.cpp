#include "Stay.h"
#include <iostream>

Stay::Stay(int lifeTime):
	Order(lifeTime)
{
}

Stay::~Stay()
{
	//std::cout << "~STAY." << std::endl;
}

OrderType Stay::getType() {
	return STAY;
}

