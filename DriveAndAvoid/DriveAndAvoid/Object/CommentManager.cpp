#include "CommentManager.h"
#include "DxLib.h"
#include<math.h>

#define NORMAL_FONT_SIZE 30
#define BIG_FONT_SIZE 45

#define MAX_COMMENT_NUM 50//コメントの最大表示数


CommentManager::CommentManager()
{
	normal_comment = new Comment * [MAX_COMMENT_NUM];
	big_comment = new Comment * [MAX_COMMENT_NUM];

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		normal_comment[i] = nullptr;
		big_comment[i] = nullptr;
	}

	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/comment.csv", "r");

	if (result != 0)
	{
		throw("Resource/dat/comment.csvが読み込めません\n");
	}

	//対象ファイルから読み込む
	for (int i = 0; i < COMMENT_TYPE; i++)
	{
		fscanf_s(fp, "%50s", comments[i], 50);
	}

	//ファイルクローズ
	fclose(fp);
}

CommentManager::~CommentManager()
{

}

void CommentManager::Update(Player* player)
{
	CommentGenerate();

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (normal_comment[i] != nullptr)//普通サイズのコメントの更新
		{
			if (normal_comment[i]->Update())
			{
				delete normal_comment[i];
				normal_comment[i] = nullptr;
			}
		}

		if (big_comment[i] != nullptr)//大きいサイズのコメントの更新
		{
			if (big_comment[i]->Update())
			{
				delete big_comment[i];
				big_comment[i] = nullptr;
			}
		}
	}
}

void CommentManager::Draw() const
{
	SetFontSize(NORMAL_FONT_SIZE);

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (normal_comment[i] != nullptr)
		{
			normal_comment[i]->Draw();
		}
	}

	SetFontSize(BIG_FONT_SIZE);

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (big_comment[i] != nullptr)
		{
			big_comment[i]->Draw();
		}
	}

	DrawString(0, 0, "CommentManager", 0xffffff);
}

void CommentManager::CommentGenerate()
{
	if (GetRand(5) == 0)//普通サイズのコメントの生成
	{
		SetFontSize(NORMAL_FONT_SIZE);

		for (int i = 0; i < MAX_COMMENT_NUM; i++)
		{
			if (normal_comment[i] == nullptr)
			{
				normal_comment[i] = new Comment(comments[GetRand(COMMENT_TYPE - 1)], (float)NORMAL_FONT_SIZE);//コメントの生成
				if (HitNormalComment(normal_comment[i], true))
				break;
			}
		}
	}
	else if (GetRand(5) == 0)//大きいサイズのコメントの生成
	{
		SetFontSize(BIG_FONT_SIZE);

		for (int i = 0; i < MAX_COMMENT_NUM; i++)
		{
			if (big_comment[i] == nullptr)
			{
				big_comment[i] = new Comment(comments[GetRand(COMMENT_TYPE - 1)], (float)BIG_FONT_SIZE);//コメントの生成
				if (HitBigComment(big_comment[i], true));//既存のコメントにぶつかったらそのコメントを消す
				break;
			}
		}
	}
}

bool CommentManager::HitNormalComment(Collider* collider, bool can_delete)
{
	bool is_hit = false;
	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (normal_comment[i] != nullptr)//普通サイズのコメントに当たったか
		{
			if ((normal_comment[i]->Hit(collider)) && (normal_comment[i] != collider))
			{
				is_hit = true;
				if (can_delete)
				{
					delete normal_comment[i];
					normal_comment[i] = nullptr;
				}
			}
		}
	}
	return is_hit;
}

bool CommentManager::HitBigComment(Collider* collider, bool can_delete)
{
	bool is_hit = false;

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (big_comment[i] != nullptr)//大きいサイズのコメントに当たったか
		{
			if ((big_comment[i]->Hit(collider)) && ((big_comment[i] != collider)))
			{
				is_hit = true;
				if (can_delete)
				{
					delete big_comment[i];
					big_comment[i] = nullptr;
				}
			}
		}
	}
	return is_hit;
}

bool CommentManager::HitComment(Collider* collider, bool can_delete)
{
	bool is_hit = false;
	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (normal_comment[i] != nullptr)//普通サイズのコメントに当たったか
		{
			if ((normal_comment[i]->Hit(collider)) && (normal_comment[i] != collider))
			{
				is_hit = true;
				if (can_delete)
				{
					delete normal_comment[i];
					normal_comment[i] = nullptr;
				}
			}
		}

		if (big_comment[i] != nullptr)//大きいサイズのコメントに当たったか
		{
			if ((big_comment[i]->Hit(collider)) && ((big_comment[i] != collider)))
			{
				is_hit = true;
				if (can_delete)
				{
					delete big_comment[i];
					big_comment[i] = nullptr;
				}
			}
		}
	}
	return is_hit;
}