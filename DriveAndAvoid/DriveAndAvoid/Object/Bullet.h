#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	float bullet_size;  //’e‚ÌƒTƒCƒY
	float bullet_speed;  //’e‚Ì‘¬‚³

public:
	Bullet();
	~Bullet();

	void Draw(const Vector2D& location);  //•`‰æˆ—
};