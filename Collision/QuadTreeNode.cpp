#include "QuadtreeNode.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Util/Util.h"

QuadtreeNode::QuadtreeNode(int nx, int ny, int w, int h) : x(nx), y(ny), width(w), height(h), subNodes(nullptr)
{
}

void QuadtreeNode::subDivide()
{
	if (subNodes == nullptr)
	{
		subNodes = new QuadtreeNode*[4];
		subNodes[0] = new QuadtreeNode(x, y, width / 2, height / 2);
		subNodes[1] = new QuadtreeNode(x + width / 2, y, width / 2, height / 2);
		subNodes[2] = new QuadtreeNode(x, y + height / 2, width / 2, height / 2);
		subNodes[3] = new QuadtreeNode(x + width / 2, y + height / 2, width / 2, height / 2);
	}
	else
	{
		for (int i = 0; i < 4; i++)
			subNodes[i]->subDivide();
	}
}

bool QuadtreeNode::contains(Sprite* spr)
{
	auto nodeRect = sf::FloatRect(x, y, width, height);
	auto spriteRect = spr->getGlobalBounds();
	if (nodeRect.contains(spriteRect.left, spriteRect.top) && 
		nodeRect.contains(spriteRect.left + spriteRect.width, spriteRect.top + spriteRect.height))
		return true;
	else
		return false;
}

void QuadtreeNode::add(Sprite* spr)
{
	if (subNodes != nullptr)
	{
		for (int i = 0; i < 4; i++)
		if (subNodes[i]->contains(spr))
		{
			subNodes[i]->add(spr);
			return;
		}
	}

	objects.push_back(spr);

	if (subNodes == nullptr && objects.size() > NODE_CAPACITY && (unsigned int)std::min(width / 2, height / 2) >= MIN_SIZE)
	{
		subDivide();
		for (unsigned int j = 0; j < objects.size(); j++)
		for (int i = 0; i < 4; i++)
		if (subNodes[i]->contains(objects[j]))
		{
			subNodes[i]->add(objects[j]);
			objects.erase(objects.begin() + j);
			j--;
			break;
		}
	}
}

void QuadtreeNode::collide(Sprite* spr, std::vector<Sprite*>& results)
{
	for (auto i : objects)
	if (i != spr && collision(spr, i))
		results.push_back(i);

	if (subNodes != nullptr)
	for (int i = 0; i < 4; i++)
		subNodes[i]->collide(spr, results);
}

bool QuadtreeNode::collision(Sprite* spr1, Sprite* spr2)
{
	Sprite::CollisionMask mask1 = spr1->getCollisionMask();
	Sprite::CollisionMask mask2 = spr2->getCollisionMask();
	if (mask1 == Sprite::BOX && mask2 == Sprite::BOX)
	{
		auto rect1 = spr1->getGlobalBounds();
		auto rect2 = spr2->getGlobalBounds();
		if (rect1.intersects(rect2))
			return true;
		else
			return false;
	}
	else if (mask1 == Sprite::CIRCLE && mask2 == Sprite::CIRCLE)
	{
		float x1 = spr1->getCollisionMaskX() + spr1->getGlobalBounds().left + spr1->getOrigin().x;
		float y1 = spr1->getCollisionMaskY() + spr1->getGlobalBounds().top + spr1->getOrigin().y;
		float r1 = spr1->getCollisionMaskR();
		float x2 = spr2->getCollisionMaskX() + spr2->getGlobalBounds().left + spr2->getOrigin().x;
		float y2 = spr2->getCollisionMaskY() + spr2->getGlobalBounds().top + spr2->getOrigin().y;
		float r2 = spr2->getCollisionMaskR();
		if (Util::pointDistance(x1, y1, x2, y2) < (r1 + r2))
			return true;
		else
			return false;
	}
	else if (mask1 == Sprite::PRECISE || mask2 == Sprite::PRECISE)
	{
		return pixelPerfect(spr1, spr2);
	}
	else return false;
}

bool QuadtreeNode::pixelPerfect(Sprite* spr1, Sprite* spr2)
{
	// TODO
	return true;
}

void QuadtreeNode::display(sf::RenderWindow* window, const sf::Color color)
{
	auto rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(color);
	rect.setOutlineThickness(1.0f);
	window->draw(rect);
	if (subNodes != nullptr)
	for (int i = 0; i < 4; i++)
		subNodes[i]->display(window);
}

void QuadtreeNode::clear()
{
	objects.clear();
	if (subNodes != nullptr)
	{
		for (int i = 0; i < 4; i++)
			delete subNodes[i];
		delete[]subNodes;
		subNodes = nullptr;
	}
}

QuadtreeNode::~QuadtreeNode()
{
	clear();
}
