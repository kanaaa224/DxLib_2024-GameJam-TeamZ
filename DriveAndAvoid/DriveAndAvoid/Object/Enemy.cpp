#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(int type, int font_size, int font_color, const char* string) : type(type), font_size(font_size), font_color(font_color), comment(string), speed(0.0f), location(0.0f), box_size(0.0f)
{
	
}

Enemy::~Enemy()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Enemy::Initialize()
{
	// 速さの設定
	speed = (float)(this->type * 2);

	// 生成位置の設定
	location = Vector2D(890.0f, ((float)(GetRand(4) * 105 + 40)));

	// 当たり判定の大きさ設定
	box_size = Vector2D(31.0f, 60.0f);
}

void Enemy::Update(float speed)
{
	location -= Vector2D(this->speed + speed, 0.0f); // 位置情報に移動量を加算
}

void Enemy::Draw() const
{
	SetFontSize(font_size);
	DrawFormatString(location.x, location.y, font_color, comment);
}

void Enemy::Fialize()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

int Enemy::GetType() const
{
	return type;
}

Vector2D Enemy::GetLocation() const
{
	return location;
}

Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

char Enemy::GetComment() const
{
	char com = *comment;
	return com;
}