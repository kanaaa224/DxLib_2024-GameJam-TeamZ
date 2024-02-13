#include"Object/Bullet.h"
#include"DxLib.h"

Bullet::Bullet(int type) :bullet_size(5), bullet_speed(5),bullet_pos(0),bullet_type(0)
{

}

Bullet::~Bullet()
{
	
}

void Bullet::Update()
{
	bullet_pos += bullet_speed;
}

void Bullet::Draw(const Vector2D& location) const
{
	DrawCircle(location.x + bullet_pos, location.y, bullet_size, 0xFFFFFF, TRUE);
}

bool Bullet::IsFinished(Vector2D& pos)
{
	return ((pos.x + bullet_pos >= 1000.0f - 180.0f) || (pos.y  < bullet_size * 2) || (pos.y  >= 600.0f - bullet_size * 2));
}