#include"Enemy.h"
#include"DxLib.h"

#define PI 3.14159	// ‰~ü—¦

Enemy::Enemy(int image_handle, int type) : image_handle(image_handle), type(type), speed(0.0f),location(Vector2D(0.0f,0.0f)), box_size(Vector2D(40.0f, 40.0f)),angle(0)
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
	if ((angle -= 5) < -360)angle = 0;
}

//•`‰æˆ—
void Enemy::Draw()
{
	DrawRotaGraph(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 0.2, PI / 180 * angle, image_handle, true);
	//DrawBox(location.x, location.y, location.x + box_size.x, location.y + box_size.y, 0xffffff, false);
}

Vector2D Enemy::GetLocation() const
{
	return location;
}
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}