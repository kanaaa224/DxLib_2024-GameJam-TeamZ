#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int image_handle, int type) : image_handle(image_handle), type(type), hp(3), speed(0.0f),location(Vector2D(0.0f,0.0f)), box_size(Vector2D(40.0f, 40.0f))
{
	speed = GetRand(3) + 1;
	location = Vector2D(1000 + GetRand(200), GetRand(480));
}

Enemy::~Enemy()
{
}

//XVˆ—
void Enemy::Update()
{
	location.x -= speed;
}

//•`‰æˆ—
void Enemy::Draw()
{
	//DrawGraph(location.x, location.y, image_handle, true);
	DrawBox(location.x, location.y, location.x + box_size.x, location.y + box_size.y, 0xffffff, false);
	DrawString(location.x, location.y, "“G", 0xffffff);
}

Vector2D Enemy::GetLocation() const
{
	return location;
}
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}
int Enemy::GetHp() const
{
	return hp;
}

void Enemy::SetHp(int hp)
{
	this->hp = hp;
}