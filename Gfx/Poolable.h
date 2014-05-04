#pragma once
class Poolable
{
protected:
	bool inUse;

public:
	bool isInUse();
	virtual void init() = 0;
	virtual void kill() = 0;
};

