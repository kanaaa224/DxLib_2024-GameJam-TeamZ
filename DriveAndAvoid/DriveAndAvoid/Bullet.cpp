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
	float sx1 = this->location.x - this->size;
	float sx2 = this->location.x + this->size;
	float sy1 = this->location.y - this->size;
	float sy2 = this->location.y + this->size;

	float dx1 = location.x;
	float dx2 = location.x + size.x;
	float dy1 = location.y;
	float dy2 = location.y + size.y;

	//‹éŒ`‚ªd‚È‚Á‚Ä‚¢‚ê‚Î“–‚½‚è
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;

	return FALSE;
}