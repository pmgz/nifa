#pragma once
#include <vector>
#include <queue>
#include "../Gfx/Sprite.h"
#include "../Gfx/ObjectPool.h"
#include "../Collision/QuadTreeNode.h"
#include "luabind/luabind.hpp"

class CompareSprite
{
public:
	bool operator()(Sprite* obj1, Sprite* obj2)
	{
		if (obj1->getDepth() < obj2->getDepth()) return true;
		else return false;
	}
};

class State
{
protected:
	std::priority_queue<Sprite*, std::vector<Sprite*>, CompareSprite> renderQueue;
	std::vector<Sprite*> spriteList;
	QuadtreeNode* collisionQuadtree;

public:
	State();

	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void cleanUp();

	void add(Sprite* sprite);
	void add(ObjectPool<Sprite>* spritePool);
};

class State_wrapper : public State, public luabind::wrap_base
{
public:
	virtual void update()
	{
		call<void>("update");
	}

	virtual void draw()
	{
		call<void>("draw");
	}

	static void default_update(State* ptr)
	{
		return ptr->State::update();
	}

	static void default_draw(State* ptr)
	{
		return ptr->State::draw();
	}
};