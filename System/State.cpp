#include "State.h"
#include "Game.h"

State::State()
{
	collisionQuadtree = new QuadtreeNode(0, 0, 640, 480);
}

void State::add(Sprite* sprite)
{
	if (sprite == nullptr) return;
	for (auto i : spriteList)
		if (i == sprite)
			return;
	spriteList.push_back(sprite);
}

void State::add(ObjectPool<Sprite>* spritePool)
{
	for (auto i : spritePool->getObjects())
		add(i);
}

void State::init()
{

}

void State::update()
{
	collisionQuadtree->clear();
	for (auto i : spriteList)
		collisionQuadtree->add(i);
	for (auto i : spriteList)
		i->update();
	for (auto i : spriteList)
	{
		std::vector<Sprite*> results;
		collisionQuadtree->collide(i, results);
		for (auto j : results)
			i->collide(j);
	}
}

void State::draw()
{
	collisionQuadtree->display(Game::getInstance()->getWindow());
	for (auto i : spriteList)
		renderQueue.push(i);

	while (!renderQueue.empty())
	{
		renderQueue.top()->draw();
		renderQueue.pop();
	}
}

void State::cleanUp()
{

}