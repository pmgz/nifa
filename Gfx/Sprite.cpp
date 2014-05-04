#include "Sprite.h"
#include "TextureManager.h"
#include "../System/Game.h"

Sprite::Sprite()
{
	depth = 0;
	type = "";
}

Sprite::~Sprite()
{
}

void Sprite::update()
{

}

void Sprite::collide(Sprite* spr)
{

}

void Sprite::draw()
{
	Game::getInstance()->getWindow()->draw(*this);
}

int Sprite::getDepth()
{
	return depth;
}

void Sprite::setDepth(int depth)
{
	this->depth = depth;
}

void Sprite::move(float x, float y)
{
	super::move(x*Game::deltaTime, y*Game::deltaTime);
}

float Sprite::getX()
{
	return getPosition().x;
}

void Sprite::setX(float x)
{
	setPosition(x, getY());
}

float Sprite::getY()
{
	return getPosition().y;
}

void Sprite::setY(float y)
{
	setPosition(getX(), y);
}

void Sprite::setTexture(const std::string &filename)
{
	super::setTexture(TextureManager::getInstance()->loadTexture(filename));
}

void Sprite::setType(std::string type)
{
	this->type = type;
}

std::string Sprite::getType()
{
	return type;
}