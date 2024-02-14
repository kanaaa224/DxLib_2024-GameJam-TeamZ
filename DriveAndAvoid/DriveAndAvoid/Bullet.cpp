#include"Object/Bullet.h"
#include"DxLib.h"

#define SPEED 10.0f

Bullet::Bullet(Vector2D location) : Collider(location, Vector2D(10.0f, 10.0f))
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
	//DrawCircle(location.x, location.y, size, 0xFFFFFF, TRUE);
	DrawBox(location.x, location.y, location.x + size.x, location.y + size.y, 0xffffff, TRUE);
}