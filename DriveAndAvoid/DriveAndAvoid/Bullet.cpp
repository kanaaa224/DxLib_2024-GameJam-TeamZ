#include"Object/Bullet.h"
#include"DxLib.h"

Bullet::Bullet() :bullet_size(5), bullet_speed(2)
{

}

Bullet::~Bullet()
{
	
}

void Bullet::Draw(const Vector2D& location)
{
	DrawCircle(location.x + bullet_speed, location.y, bullet_size, 0xFFFFFF, TRUE);
}

