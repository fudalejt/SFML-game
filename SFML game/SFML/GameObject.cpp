#include "GameObject.h"


Game* GameObject::game = nullptr;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::setGame(Game* game) {
	GameObject::game = game;
}
