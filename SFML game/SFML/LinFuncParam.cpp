#include "LinFuncParam.h"



LinFuncParam::LinFuncParam()
{
}

LinFuncParam::LinFuncParam(float a, float b, int o):
	a(a),
	b(b),
	o(o)
{
}


LinFuncParam::~LinFuncParam()
{
}

float LinFuncParam::getA()
{
	return a;
}

float LinFuncParam::getB()
{
	return b;
}

int LinFuncParam::getO()
{
	return o;
}

void LinFuncParam::setA(float a)
{
	this->a = a;
}

void LinFuncParam::setB(float b)
{
	this->b = b;
}

void LinFuncParam::setO(int o)
{
	if (o == 1 || o == -1)
		this->o = o;
	else {
		o = 1;
		throw "Bad argument value. 'o' can take only -1 or 1 value.";
	}
		
}
