#include"Comment.h"
#include"DxLib.h"

Comment::Comment(const char* comment, int font_size) : Collider(Vector2D(0.0f, 0.0f), Vector2D(0.0f, 0.0f)), comment(comment), speed(0.0f), hp(5), color(0xffffff)
{
	location = Vector2D(1500.0f + GetRand(500), GetRand(20) * (font_size + 3));
	size = Vector2D(GetDrawFormatStringWidth(comment), font_size);
	//if (GetRand(10) == 0)color = 0xff0000;//1���̊m���ŃR�����g�̐F��ԐF�ɂ���
}

//�X�V����
bool Comment::Update()
{
	color = 0xffffff;
	location.x -= speed;


	if ((comment[i].location.x -= comment[i].speed) < -500)comment[i].can_draw = false;
	if (player->HitPlayer(comment[i].location, comment[i].box_size))comment[i].can_draw = false;
	if (player->HitBullet(comment[i].location, comment[i].box_size))
	{
		comment[i].color = 0xff0000;
		if (--comment[i].hp <= 0)comment[i].can_draw = false;
	}
}

//�`�揈��
void Comment::Draw()
{
	//�v���C���[�摜�̕`��
	DrawFormatString(location.x, location.y, color, comment);
	DrawBox(location.x, location.y, location.x + size.x, location.y + size.y, color, FALSE);
}

int Comment::GetHp()const
{
	return hp;
}