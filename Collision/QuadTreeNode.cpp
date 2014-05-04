#include "QuadtreeNode.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

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
	auto rect1 = spr1->getGlobalBounds();
	auto rect2 = spr2->getGlobalBounds();
	if (rect1.intersects(rect2))
		return true;
	else
		return false;
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
