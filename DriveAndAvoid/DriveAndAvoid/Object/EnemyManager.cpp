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

	LoadDivGraph("Resource/images/enemy.png", ENEMY_TYPE, ENEMY_TYPE, 1, 300, 350, enemy_image);
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;
}

void EnemyManager::Update(Player* player)
{
	//�G�l�~�[�̍X�V
	bool can_spawn = false;//�V�����G�l�~�[�������\��
	if (GetRand(50) == 0)can_spawn = true;

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->Update())
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
			else if (player->HitBullet(enemy[i]))
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
		else if (can_spawn)
		{
			enemy[i] = new Enemy(enemy_image[GetRand(2)]);
			can_spawn = false;
		}
	}
}

void EnemyManager::Draw() const
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
}

bool EnemyManager::HitEnemy(Collider* collider, bool can_delete)
{
	bool is_hit = false;
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)//���ʃT�C�Y�̃R�����g�ɓ���������
		{
			if ((enemy[i]->Hit(collider)) && (enemy[i] != collider))
			{
				is_hit = true;
				if (can_delete)
				{
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}
		}
	}
	return is_hit;
}