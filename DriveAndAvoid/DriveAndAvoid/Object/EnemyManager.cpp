#include "EnemyManager.h"
#include "DxLib.h"

#define MAX_ENEMY_NUM 50//�G�̍ő�\����


EnemyManager::EnemyManager()
{
	enemy = new Enemy * [MAX_ENEMY_NUM];

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		enemy[i] = nullptr;
	}
}

CommentManager::~CommentManager()
{
	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (normal_comment[i] != nullptr)
		{
			delete normal_comment[i];
			normal_comment[i] = nullptr;
		}
		if (big_comment[i] != nullptr)
		{
			delete big_comment[i];
			big_comment[i] = nullptr;
		}
	}

	delete[] normal_comment;
	delete[] big_comment;
}

void CommentManager::Update(Player* player)
{
	CommentGenerate();

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		if (normal_comment[i] != nullptr)//���ʃT�C�Y�̃R�����g�̍X�V
		{
			if (normal_comment[i]->Update())
			{
				delete normal_comment[i];
				normal_comment[i] = nullptr;
			}
			else if (player->HitBullet(normal_comment[i]))
			{
				if (normal_comment[i]->HitBullet() <= 0)
				{
					delete normal_comment[i];
					normal_comment[i] = nullptr;
				}
			}
		}

		if (big_comment[i] != nullptr)//�傫���T�C�Y�̃R�����g�̍X�V
		{
			if (big_comment[i]->Update())
			{
				delete big_comment[i];
				big_comment[i] = nullptr;
			}
			else if (player->HitBullet(big_comment[i]))
			{
				if (big_comment[i]->HitBullet() <= 0)
				{
					delete big_comment[i];
					big_comment[i] = nullptr;
				}
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
	if (GetRand(10) == 0)//���ʃT�C�Y�̃R�����g�̐���
	{
		SetFontSize(NORMAL_FONT_SIZE);

		for (int i = 0; i < MAX_COMMENT_NUM; i++)
		{
			if (normal_comment[i] == nullptr)
			{
				normal_comment[i] = new Comment(comments[GetRand(COMMENT_TYPE - 1)], (float)NORMAL_FONT_SIZE);//�R�����g�̐���
				if (HitNormalComment(normal_comment[i], true))
					break;
			}
		}
	}
	else if (GetRand(20) == 0)//�傫���T�C�Y�̃R�����g�̐���
	{
		SetFontSize(BIG_FONT_SIZE);

		for (int i = 0; i < MAX_COMMENT_NUM; i++)
		{
			if (big_comment[i] == nullptr)
			{
				big_comment[i] = new Comment(comments[GetRand(COMMENT_TYPE - 1)], (float)BIG_FONT_SIZE);//�R�����g�̐���
				if (HitBigComment(big_comment[i], true));//�����̃R�����g�ɂԂ������炻�̃R�����g������
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
		if (normal_comment[i] != nullptr)//���ʃT�C�Y�̃R�����g�ɓ���������
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
		if (big_comment[i] != nullptr)//�傫���T�C�Y�̃R�����g�ɓ���������
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
		if (normal_comment[i] != nullptr)//���ʃT�C�Y�̃R�����g�ɓ���������
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

		if (big_comment[i] != nullptr)//�傫���T�C�Y�̃R�����g�ɓ���������
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