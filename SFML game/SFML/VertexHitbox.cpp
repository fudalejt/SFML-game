#include "VertexHitbox.h"
#include "MathUtilities.h"

#include <iostream>


VertexHitbox::VertexHitbox(sf::VertexArray& vertexAr):
	vertexAr(vertexAr),
	linPar(std::vector<LinFuncParam>(vertexAr.getVertexCount()))
{
}

VertexHitbox::~VertexHitbox()
{
}

bool VertexHitbox::isContaining(const sf::Vector2f& point)
{
	sf::Vector2f relPoint = point;
	relPoint = relPoint - getPosition();
	relPoint = math::rotateVector(relPoint, getRotation());
	relPoint += getOrigin();

	for (unsigned int i = 1; i < vertexAr.getVertexCount() - 1; i++)
	{
		LinFuncParam &fx = linPar[i];

		if (fx.a == std::numeric_limits<float>::max()) //if f(x) function is a vertical positive funct &&...
		{
			if (relPoint.x > vertexAr[i].position.x)
				return false;
			else
				continue;
		}
		else if (fx.a == std::numeric_limits<float>::min()) 	//if f(x) function is a vertical negative funct &&...
		{
			if (relPoint.x < vertexAr[i].position.x)
				return false;
			else
				continue;
		}
		else {
			if (fx.o == 1) {
				if ((fx.a * relPoint.x + fx.b) > relPoint.y) {
					return false;
				}
			}
			else if (fx.o == -1) {
				if ((fx.a * relPoint.x + fx.b) < relPoint.y)
					return false;
			}
			else {
				throw "class [COLLIDE_POLYGON], method [CONTAIN()]: ERROR, fx.o ";
			}
		}
	}
	return true;
}

void VertexHitbox::refresh()
{
	for (unsigned int i = 1; i < linPar.size() - 1; i++) {
		LinFuncParam &fx = linPar[i];
		if ((vertexAr[i + 1].position.x - vertexAr[i].position.x) != 0) {
			fx.setA((vertexAr[i + 1].position.y - vertexAr[i].position.y) / (vertexAr[i + 1].position.x - vertexAr[i].position.x));
			fx.setB((vertexAr[i].position.y) - fx.a * (vertexAr[i].position.x));
			fx.setO((vertexAr[i + 1].position.x - vertexAr[i].position.x > 0) ? 1 : -1);
		}
		else {
			if ((vertexAr[i + 1].position.y - vertexAr[i].position.y) > 0)
				fx.setA(std::numeric_limits<float>::max()); //max float value
			else
				fx.setA(std::numeric_limits<float>::min()); //min float value
		}
	}
}
