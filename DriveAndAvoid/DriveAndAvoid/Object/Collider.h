#pragma once
#include"../Utility/Vector2D.h"

class Collider
{
protected:
	Vector2D location;
	Vector2D size;

public:
	Collider(Vector2D location, Vector2D size);
	~Collider() {};
	bool Hit(Collider* collider)const;
	Vector2D GetLocation()const;
	Vector2D GetSize()const;
};