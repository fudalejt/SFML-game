#include "TextureManager.h"
#include <iostream>


bool TextureManager::instanceExist = false;
sf::Texture TextureManager::attitudeIcons;
sf::Texture TextureManager::hitIcon;
sf::Texture TextureManager::blockIcon;
sf::Texture TextureManager::template1;
sf::Texture TextureManager::unit0;
sf::Texture TextureManager::unit1;

TextureManager::TextureManager()
{
	if (instanceExist == false) {
		initiate();
		instanceExist = true;
	}
}

TextureManager::~TextureManager()
{
}

void TextureManager::initiate() {
	if (!attitudeIcons.loadFromFile("icons/icons.png")) {
		std::cout << "Wrong load a texture: [attitudeIcons]" << std::endl;
	}

	if (!hitIcon.loadFromFile("icons/hit.png")) {
		std::cout << "Wrong load a texture: [hitIcon]" << std::endl;
	}

	if (!blockIcon.loadFromFile("icons/block.png")) {
		std::cout << "Wrong load a texture: [blockIcon]" << std::endl;
	}

	if (!template1.loadFromFile("templates/template1.png")) {
		std::cout << "Wrong load a texture: [template1]" << std::endl;
	}

	if (!unit0.loadFromFile("units/unit0Blur.png")) {
		std::cout << "Wrong load a texture: [unit0]" << std::endl;
	}

	if (!unit1.loadFromFile("units/unit1Blur.png")) {
		std::cout << "Wrong load a texture: [unit1]" << std::endl;
	}
}
