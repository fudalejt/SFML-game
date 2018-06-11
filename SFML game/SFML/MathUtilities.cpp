#include "MathUtilities.h"

sf::Vector2f math::rotateVector(const sf::Vector2f v, float angle)
{
	float sinA = static_cast<float>(sin(-angle * PI / 180));
	float cosA = static_cast<float>(cos(-angle * PI / 180));
	sf::Vector2f v2 = sf::Vector2f((v.x * cosA - v.y * sinA), (v.x * sinA + v.y * cosA));
	return v2;
}

float math::getRotation(sf::Vector2f vector)
{
	float angle = atan2(vector.y, vector.x);
	angle *= RAD_TO_ANGL;
	return angle;
}

float math::getDistanceBetween(sf::Vector2f v1, sf::Vector2f v2)
{
	return (sqrt( pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2)));
}

bool math::getRandom(int successTresholdPrc)
{
	int res = rand() % 100;
	if (res < successTresholdPrc)
		return true;
	else
		return false;
}

int math::sign(float arg)
{
	if (arg < 0)
		return -1;
	else
		return 1;
}

math::LinearFuncParams::LinearFuncParams(float a, float b) :
	a(a),
	b(b)
{

}
