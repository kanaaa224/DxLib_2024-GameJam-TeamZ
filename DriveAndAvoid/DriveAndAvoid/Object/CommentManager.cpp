#include "CommentManager.h"
#include "DxLib.h"
#include<math.h>

#define NORMAL_FONT_SIZE 30
#define BIG_FONT_SIZE 45

#define MAX_COMMENT_NUM 50//�R�����g�̍ő�\����


CommentManager::CommentManager()
{
	normal_comment = new Comment * [MAX_COMMENT_NUM];
	big_comment = new Comment * [MAX_COMMENT_NUM];

	for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		normal_comment[i] = nullptr;
		big_comment[i] = nullptr;
	}

	//�����L���O�f�[�^�̓ǂݍ���
	FILE* fp = nullptr;

	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/comment.csv", "r");

	if (result != 0)
	{
		throw("Resource/dat/comment.csv���ǂݍ��߂܂���\n");
	}

	//�Ώۃt�@�C������ǂݍ���
	for (int i = 0; i < COMMENT_TYPE; i++)
	{
		fscanf_s(fp, "%50s", comments[i], 50);
	}

	//�t�@�C���N���[�Y
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
		if (normal_comment[i] != nullptr)//���ʃT�C�Y�̃R�����g�̍X�V
		{
			if (normal_comment[i]->Update())
			{
				delete normal_comment[i];
				normal_comment[i] = nullptr;
			}
		}

		if (big_comment[i] != nullptr)//�傫���T�C�Y�̃R�����g�̍X�V
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
	if (GetRand(5) == 0)//���ʃT�C�Y�̃R�����g�̐���
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
	else if (GetRand(5) == 0)//�傫���T�C�Y�̃R�����g�̐���
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