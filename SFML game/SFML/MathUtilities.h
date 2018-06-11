#pragma once
#include <SFML/Graphics.hpp>

namespace math {
	const double PI = 3.14159265; 
	const double RAD_TO_ANGL = 57.295779513096787811;

	///functions
	int sign(float arg);	

	sf::Vector2f rotateVector(const sf::Vector2f v, float angle);

	float getRotation(sf::Vector2f vector);

	float getDistanceBetween(sf::Vector2f v1, sf::Vector2f v2);

	bool getRandom(int successTresholdPrc);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///data structures 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class LinearFuncParams {
	public:
		float a, b;

		/*
			Linear function in a form : y = a*x + b 
		*/
		LinearFuncParams::LinearFuncParams(float a, float b);

	};
	
}
