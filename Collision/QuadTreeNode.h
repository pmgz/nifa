#pragma once
#include <vector>
#include <string>
#include "../Gfx/Sprite.h"

class QuadtreeNode
{
private:
	int x;
	int y;
	int width;
	int height;
	static const unsigned int NODE_CAPACITY = 3; // maksymalna liczba obiektow w jednej komorce przed podzialem
	static const unsigned int MIN_SIZE = 32; // minimalna dlugosc krawedzi komorki podzialu
	QuadtreeNode** subNodes;
	std::vector<Sprite*> objects;
public:
	QuadtreeNode(int, int, int, int);
	~QuadtreeNode();
	void subDivide();
	void add(Sprite*);
	bool contains(Sprite*);
	void collide(Sprite*, std::vector<Sprite*>&);
	void clear();
	void display(sf::RenderWindow*, const sf::Color = sf::Color(255, 0, 255, 255));
	static bool collision(Sprite*, Sprite*);
	static bool pixelPerfect(Sprite*, Sprite*);
};
