#pragma once
class LinFuncParam
{
public:
	float a, b; //f(x) = a*x + b
	int o; //o -> left (-1) or right (1) orientation of f(x) function

	LinFuncParam();
	LinFuncParam(float a, float b, int o);
	virtual ~LinFuncParam();
	float getA();
	float getB();
	int getO();
	void setA(float a);
	void setB(float b);
	void setO(int o);
	
};

