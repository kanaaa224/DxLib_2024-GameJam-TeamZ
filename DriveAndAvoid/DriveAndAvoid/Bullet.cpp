#include"Object/Bullet.h"
#include"DxLib.h"

#define SPEED 10.0f

Bullet::Bullet(Vector2D location) : location(location), size(5)
{

}

Bullet::~Bullet()
{
	
}

void Bullet::Update()
{
	location.x += SPEED;
}

void Bullet::Draw() const
{
	DrawCircle(location.x, location.y, size, 0xFFFFFF, TRUE);
}

Vector2D Bullet::Bullet::GetLocation()
{
	return location;
}

bool Bullet::Hit(Vector2D location, Vector2D size)
{
	
}