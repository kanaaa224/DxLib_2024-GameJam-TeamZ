#include"Object/Bullet.h"
#include"DxLib.h"

Bullet::Bullet() :bullet_size(5), bullet_speed(2)
{

}

Bullet::~Bullet()
{
	
}

void Bullet::Update()
{
	bullet_speed++;
}

void Bullet::Draw(const Vector2D& location) const
{
	DrawCircle(location.x + bullet_speed, location.y, bullet_size, 0xFFFFFF, TRUE);
}

bool Bullet::IsFinished(Vector2D& pos)
{
	return ((pos.x + bullet_speed >= 1000.0f - 180.0f) || (pos.y + bullet_speed < bullet_size * 2) || (pos.y + bullet_speed >= 600.0f - bullet_size * 2));
}