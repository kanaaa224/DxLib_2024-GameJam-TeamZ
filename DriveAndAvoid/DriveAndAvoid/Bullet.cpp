#include"Object/Bullet.h"
#include"DxLib.h"
#include"Object/Player.h"

Bullet::Bullet(Vector2D location) :bullet_size(5), bullet_speed(5),bullet_pos(location),bullet_type(0)
{

}

Bullet::~Bullet()
{
	
}

void Bullet::Update()
{
	bullet_pos.x += bullet_speed;
}

void Bullet::Draw() const
{
	DrawCircle(bullet_pos.x, bullet_pos.y, bullet_size, 0xFFFFFF, TRUE);
}

bool Bullet::IsFinished()
{
	return (( bullet_pos.x >= 1000.0f - 180.0f) || ( bullet_pos.y < bullet_size * 2) || (bullet_pos.y  >= 600.0f - bullet_size * 2));
}

Vector2D Bullet::GetLocation() const
{
	return this->bullet_pos;
}

bool Bullet::Hit(Vector2D location, Vector2D size)
{
	float sx1 = this->bullet_pos.x - this->bullet_size;
	float sx2 = this->bullet_pos.x + this->bullet_size;
	float sy1 = this->bullet_pos.y - this->bullet_size;
	float sy2 = this->bullet_pos.y + this->bullet_size;
	float dx1 = location.x;
	float dx2 = location.x + size.x;
	float dy1 = location.y;
	float dy2 = location.y + size.y;
	//‹éŒ`‚ªd‚È‚Á‚Ä‚¢‚ê‚Î“–‚½‚è
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;
	return FALSE;
}