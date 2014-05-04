#pragma once

template <class T>
class Singleton
{
protected:
	static T* INSTANCE;
public:
	static T* getInstance();
};

template <class T>
T* Singleton<T>::INSTANCE = NULL;

template <class T>
T* Singleton<T>::getInstance()
{
	if (INSTANCE == NULL)
		INSTANCE = new T();
	return INSTANCE;
}

