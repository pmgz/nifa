#include "Poolable.h"

bool Poolable::isInUse()
{
	return inUse;
}

void Poolable::init()
{
	inUse = 1;
}

void Poolable::kill()
{
	inUse = 0;
}