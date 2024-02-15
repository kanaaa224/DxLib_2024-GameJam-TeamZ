#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

#define MAX_ENEMY_NUM 20

GameMainScene::GameMainScene() : back_ground_image(NULL), player(nullptr), enemy(nullptr), mileage(0)
{
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�摜�̓ǂݍ���
	back_ground_image = LoadGraph("Resource/images/background.png");
	LoadDivGraph("Resource/images/enemy.png", 3, 3, 1, 300, 350, enemy_image);

	player = new Player();

	enemy = new Enemy * [MAX_ENEMY_NUM];

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		enemy[i] = nullptr;
	}
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//�v���C���[�̍X�V
	player->Update();

	//�G�l�~�[�̍X�V
	bool can_spawn = false;//�V�����G�l�~�[�������\��
	if (GetRand(100) == 0)can_spawn = true;

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->Update())
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

	//�R�����g
	comment_manager.Update(player);

	mileage++;

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(-mileage % 1280, 0, back_ground_image, TRUE);
	DrawGraph(-mileage % 1280 + 1280, 0, back_ground_image, TRUE);

	//�v���C���[�̕`��
	player->Draw();

	//�G�l�~�[�̕`��
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//�R�����g�`��i�_�����ǉ����܂����j
	comment_manager.Draw();

}

//�I��������
void GameMainScene::Finalize()
{
	//���I�m�ۂ����I�u�W�F�N�g���폜����
	delete player;

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

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}