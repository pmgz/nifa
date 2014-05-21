#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "luabind/luabind.hpp"

class Sprite : public sf::Sprite
{
public:
	enum CollisionMask { BOX, CIRCLE, PRECISE };

protected:
	int depth;
	std::string type;
	CollisionMask collisionMask;
	float collisionMaskX;
	float collisionMaskY;
	float collisionMaskR;
	float collisionMaskW;
	float collisionMaskH;

public:
	typedef sf::Sprite super;
	Sprite();
	~Sprite();

	virtual void update();
	virtual void collide(Sprite* spr);
	virtual void draw();

	int getDepth();
	void setDepth(int depth);
	void move(float x, float y);
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	void setTexture(const std::string &filename);
	void setType(std::string type);
	std::string getType();
	void setCollisionBox(float x, float y, float w, float h);
	void setCollisionCircle(float x, float y, float r);
	void setCollisionPrecise();
	void setCollisionMask(CollisionMask mask);
	CollisionMask getCollisionMask();
	float getCollisionMaskX();
	float getCollisionMaskY();
	float getCollisionMaskR();
	float getCollisionMaskW();
	float getCollisionMaskH();
};

class Sprite_wrapper : public Sprite, public luabind::wrap_base
{
public:
	virtual void update()
	{
		call<void>("update");
	}

	virtual void collide(Sprite* spr)
	{
		call<void>("collide", spr);
	}

	virtual void draw()
	{
		call<void>("draw");
	}

	static void default_update(Sprite* ptr)
	{
		return ptr->Sprite::update();
	}

	static void default_collide(Sprite* ptr, Sprite* spr)
	{
		return ptr->Sprite::collide(spr);
	}

	static void default_draw(Sprite* ptr)
	{
		return ptr->Sprite::draw();
	}
};

