#pragma once
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();	

	static sf::Texture attitudeIcons;
	static sf::Texture hitIcon;
	static sf::Texture blockIcon;
	static sf::Texture template1;
	static sf::Texture unit0;
	static sf::Texture unit1;

protected:
	static void initiate();

	static bool instanceExist;
	
};

