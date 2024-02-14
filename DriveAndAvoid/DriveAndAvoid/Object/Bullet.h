#pragma once

#include"Collider.h"

class Bullet : public Collider
{
public:
	Bullet(Vector2D location);
	~Bullet();

	void Update();  //XVˆ—
	void Draw() const;  //•`‰æˆ—
};