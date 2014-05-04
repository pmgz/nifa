#pragma once
#include <vector>
#include "Poolable.h"
#include "Sprite.h"

template <class T>
class ObjectPool
{
private:
	int poolSize;
	std::vector<T*> objects;

public:
	ObjectPool();
	ObjectPool(int poolSize);
	~ObjectPool();
	T* recycle();
	std::vector<T*>& getObjects();
};

template <class T>
ObjectPool<T>::ObjectPool(int poolSize) : poolSize(poolSize)
{
	for (int i = 0; i < poolSize; i++)
	{
		auto obj = new T();
		objects.push_back(obj);
		obj->init();
	}
}

template <class T>
T* ObjectPool<T>::recycle()
{
	for (auto i : objects)
	{
		if (!i->isInUse())
		{
			i->init();
			return i;
		}
	}
	return nullptr;
}

template <class T>
ObjectPool<T>::~ObjectPool()
{
}

template <class T>
std::vector<T*>& ObjectPool<T>::getObjects()
{
	return objects;
}

