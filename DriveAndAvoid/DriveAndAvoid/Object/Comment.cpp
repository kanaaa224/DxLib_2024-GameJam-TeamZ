#include"Comment.h"
#include"DxLib.h"

#define NORMAL_FONT_SIZE 35

Comment::Comment(const char* comment, float font_size) : Collider(Vector2D(0.0f, 0.0f), Vector2D(0.0f, 0.0f)), comment(comment), speed(0.0f), hp(5), color(0xffffff)
{
	location = Vector2D(1000.0f, GetRand(20) * (font_size + 3));

	size = Vector2D(GetDrawFormatStringWidth(comment), font_size);
	speed = GetRand(2) + 1;
	if (GetRand(10) == 0)color = 0xff0000;//1���̊m���ŃR�����g�̐F��ԐF�ɂ���
}

//�X�V����
bool Comment::Update()
{
	//color = 0xffffff;
	location.x -= speed;

	return (location.x < -200);
}

//�`�揈��
void Comment::Draw()const
{
	DrawFormatString(location.x, location.y, color, comment);
	//DrawBox(location.x, location.y, location.x + size.x, location.y + size.y, color, FALSE);
}

int Comment::HitBullet()
{
	color = 0xff0000;
	return --hp;
}