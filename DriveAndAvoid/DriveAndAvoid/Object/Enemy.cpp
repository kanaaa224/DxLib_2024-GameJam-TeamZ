#include "Enemy.h"
#include "DxLib.h"

#define PI 3.14159	// 円周率

Enemy::Enemy(int image_handle) : Collider(Vector2D(1300.0f, 0.0f), Vector2D(77.0f, 77.0f)), speed(5.0f), image_handle(image_handle), angle(0.0f)
{
	location.y = GetRand(700);
}

Enemy::~Enemy()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////


bool Enemy::Update()
{
	location.x -= speed; // 位置情報に移動量を加算
	if ((angle -= 5.0f) < -360.0f)angle = 0.0f;
	return(location.x < -100);
}

void Enemy::Draw() const
{
	DrawRotaGraph(location.x + (size.x / 2), location.y + (size.y / 2), 0.3, PI / 180 * angle, image_handle, TRUE);
	DrawBox(location.x, location.y, location.x + size.x, location.y + size.y, 0xffffff, FALSE);
}