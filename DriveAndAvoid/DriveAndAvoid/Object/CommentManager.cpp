#include "CommentManager.h"
#include "DxLib.h"
#include<math.h>

#define FONT_SIZE 25.0f

CommentManager::CommentManager()
{
	SetFontSize(FONT_SIZE);
	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		comment[i] = { FALSE,0,0xffffff,0,0,Vector2D(0.0f,0.0f),Vector2D(0.0f,0.0f) };
	}
}

CommentManager::~CommentManager()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CommentManager::Initialize()
{
}

void CommentManager::Update(Player* player)
{
	CommentGenerate();

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (comment[i].can_draw)
		{
			comment[i].color = 0xffffff;
			if ((comment[i].location.x -= comment[i].speed) < -500)comment[i].can_draw = false;
			if (player->HitPlayer(comment[i].location, comment[i].box_size))comment[i].can_draw = false;
			if (player->HitBullet(comment[i].location, comment[i].box_size))
			{
				comment[i].color = 0xff0000;
				if(--comment[i].hp <= 0)comment[i].can_draw = false;
			}
		}
	}
}

void CommentManager::Draw() const
{
	SetFontSize(FONT_SIZE);

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (comment[i].can_draw)
		{
			DrawFormatString(comment[i].location.x, comment[i].location.y, comment[i].color, comments[comment[i].type]);
			DrawBox(comment[i].location.x, comment[i].location.y, comment[i].location.x + comment[i].box_size.x, comment[i].location.y + comment[i].box_size.y, 0xffffff, false);
		}

	}
}

void CommentManager::Fialize()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CommentManager::CommentGenerate()
{
	if (GetRand(20) == 0)
	{
		SetFontSize(FONT_SIZE);

		for (int i = 0; i < MAX_COMMENT_NUM; i++)
		{
			if (!comment[i].can_draw)
			{
				comment[i].can_draw = true;
				comment[i].hp = 5;
				comment[i].color = 0xffffff;
				comment[i].type = GetRand(COMMENT_TYPE - 1);
				comment[i].speed = (float)(GetDrawFormatStringWidth(comments[comment[i].type]) / 80) + 1;
				comment[i].location = Vector2D(1500.0f + GetRand(500), GetRand(19) * FONT_SIZE + 3);
				comment[i].box_size = Vector2D(GetDrawFormatStringWidth(comments[comment[i].type]), FONT_SIZE);
				break;
			}
		}
	}
}